import play.api.libs.json._
import play.api.libs.functional.syntax._
/**
 * Created by lind on 11/18/2014.
 */
object EventUtil {

  // deprecated functions
//  def ToJson(e: Event) = {
//    implicit val eventWrites = new Writes[Event] {
//      def writes(event: Event) = Json.obj(
//        "summary" -> event.summary,
//        "start" -> event.start,
//        "end" -> event.end,
//        "description"->event.description
//      )
//    }
//    val json: JsValue = Json.toJson(e)
//    json
//  }
//
//  def FromJson(j: JsValue): Option[Event] = {
//
//  implicit val eventReads: Reads[Event] = (
//    (JsPath \ "summary").read[String] and
//      (JsPath \ "start").read[String] and
//      (JsPath \ "end").read[String] and
//      (JsPath \ "description").read[String]
//    )(Event.apply _)
//
//    val eventResult: JsResult[Event] = j.validate[Event]
//    val event = eventResult.asOpt
//    event
//  }

  def ConvertEventsToJson(events: Seq[Event]): JsValue = {
    // Option 1
    //    Json.toJson(
    //      events.map { t =>
    //        Map("summary" -> t.summary, "start" -> t.start, "end" -> t.end, "description"-> t.description)
    //      }
    //    )

    // Options 2
    Json.toJson(events)
  }

  def ConvertJsonToEvents(json: JsArray): Seq[Event] = {
    json.value.map(_.as[Event]).toSeq
  }
}
