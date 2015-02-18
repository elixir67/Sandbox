import play.api.libs.json._
import play.api.libs.functional.syntax._

/**
 * Created by lind on 11/18/2014.
 */
case class Event(summary: String, start: String, end: String, description: String)

object Event {
  implicit object EventFormat extends Format[Event] {
    // convert from Event object to JSON (serializing to JSON)
    def writes(event: Event): JsValue = {
      val eventSeq = Seq(
        "summary" -> JsString(event.summary),
        "start" -> JsString(event.start),
        "end" -> JsString(event.end),
        "description" -> JsString(event.description)
      )
      JsObject(eventSeq)
    }

    // convert from JSON string to Event object (de-serializing from JSON)
    def reads(json: JsValue): JsResult[Event] = {
      JsSuccess(Event(
        (json \ "summary").as[String],
        (json \ "start").as[String],
        (json \ "end").as[String],
        (json \ "description").as[String]
      )
      )
//   JsSuccess(Event("", "", "",""))
    }
  }
}


