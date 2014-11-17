import org.scalatest.{Matchers, FlatSpec}
import play.api.libs.json._
import play.api.libs.functional.syntax._

/**
 * Created by lind on 11/17/2014.
 */
class JsonSpec extends FlatSpec with Matchers {
   "JsonSpec" should "try play json api" in {
        val json = Json.toJson("Five")
        val readableString = Json.prettyPrint(json)
        println(readableString)

        val dummy = 1
        dummy should be > 0
   }

   it should "use the writer of play.api.libs.json" in {
     case class Event(summary: String, dtStart: String)

     implicit val eventWrites = new Writes[Event] {
       def writes(event: Event) = Json.obj(
         "summary" -> event.summary,
         "start" -> event.dtStart
       )
     }

     // Convert model to Json
     val e = Event("TestSummary", "TestStart")
     val json: JsValue = Json.toJson(e)
     val readableString = Json.prettyPrint(json)
     println(readableString)

     // Convert Json to model
     implicit val eventReads: Reads[Event] = (
       (JsPath \ "summary").read[String] and
         (JsPath \ "start").read[String]
       )(Event.apply _)

     //TODO: use json.Parse to create JsValue
     val eventResult: JsResult[Event] = json.validate[Event]
     if (eventResult.isSuccess) {
     val event = eventResult.get
       println(event.summary)
   }
     val dummy = 1
     dummy should be > 0
   }
}
