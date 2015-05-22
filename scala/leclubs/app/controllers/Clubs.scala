package controllers

import play.modules.reactivemongo.MongoController
import play.modules.reactivemongo.json.collection.JSONCollection
import scala.concurrent.Future
import reactivemongo.api.Cursor
import play.api.libs.concurrent.Execution.Implicits.defaultContext
import org.slf4j.{LoggerFactory, Logger}
import javax.inject.Singleton
import play.api.mvc._
import play.api.libs.json._

/**
 * The Clubs controllers encapsulates the Rest endpoints and the interaction with the MongoDB, via ReactiveMongo
 * play plugin. This provides a non-blocking driver for mongoDB as well as some useful additions for handling JSon.
 * @see https://github.com/ReactiveMongo/Play-ReactiveMongo
 */
@Singleton
class Clubs extends Controller with MongoController {

  private final val logger: Logger = LoggerFactory.getLogger(classOf[Clubs])

  /*
   * Get a JSONCollection (a Collection implementation that is designed to work
   * with JsObject, Reads and Writes.)
   * Note that the `collection` is not a `val`, but a `def`. We do _not_ store
   * the collection reference to avoid potential problems in development with
   * Play hot-reloading.
   */
  def collection: JSONCollection = db.collection[JSONCollection]("clubs")

  // ------------------------------------------ //
  // Using case classes + Json Writes and Reads //
  // ------------------------------------------ //

  import models._
  import models.JsonFormats._

  def createClub = Action.async(parse.json) {
    request =>
    /*
     * request.body is a JsValue.
     * There is an implicit Writes that turns this JsValue as a JsObject,
     * so you can call insert() with this JsValue.
     * (insert() takes a JsObject as parameter, or anything that can be
     * turned into a JsObject using a Writes.)
     */
      request.body.validate[Club].map {
        club =>
        // `club` is an instance of the case class `models.Club`
          collection.insert(club).map {
            lastError =>
              logger.debug(s"Successfully inserted with LastError: $lastError")
              Created(s"Club Created")
          }
      }.getOrElse(Future.successful(BadRequest("invalid json")))
  }

  def findClubs = Action.async {
    // let's do our query
    val cursor: Cursor[Club] = collection.
      // find all
      find(Json.obj("active" -> true)).
      // sort them by creation date
      sort(Json.obj("created" -> -1)).
      // perform the query and get a cursor of JsObject
      cursor[Club]

    // gather all the JsObjects in a list
    val futureClubsList: Future[List[Club]] = cursor.collect[List]()

    // transform the list into a JsArray
    val futureClubsJsonArray: Future[JsArray] = futureClubsList.map { clubs =>
      Json.arr(clubs)
    }
    // everything's ok! Let's reply with the array
    futureClubsJsonArray.map {
      clubs =>
        Ok(clubs(0))
    }
  }

}
