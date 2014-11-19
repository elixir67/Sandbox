import play.api.libs.json._
import play.api.libs.functional.syntax._
/**
 * Created by lind on 11/18/2014.
 */
object EventUtil {

  def ToJson(e: Event) = {
    implicit val eventWrites = new Writes[Event] {
      def writes(event: Event) = Json.obj(
        "summary" -> event.summary,
        "start" -> event.start,
        "end" -> event.end,
        "description"->event.description
      )
    }
    val json: JsValue = Json.toJson(e)
    json
  }

  def FromJson(j: JsValue): Option[Event] = {

  implicit val eventReads: Reads[Event] = (
    (JsPath \ "summary").read[String] and
      (JsPath \ "start").read[String] and
      (JsPath \ "end").read[String] and
      (JsPath \ "description").read[String]
    )(Event.apply _)

    val eventResult: JsResult[Event] = j.validate[Event]
    val event = eventResult.asOpt
    event
  }
}
