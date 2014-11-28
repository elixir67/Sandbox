import org.scalatest.{Matchers, FlatSpec}
import play.api.libs.json._
import play.api.libs.functional.syntax._

import scala.collection.mutable.ListBuffer

/**
 * Created by lind on 11/17/2014.
 */
class JsonSpec extends FlatSpec with Matchers {
   "JsonSpec" should "try play json api" in {
        val json = Json.toJson("Five")
        val readableString = Json.prettyPrint(json)
        println(readableString)
   }

  // deprecated test
//   it should "use play.api.libs.json for Event" in {
//     // Convert model to Json
//     val e = Event("TestSummary", "TestStart", "TestEnd", "")
//     val json: JsValue = EventUtil.ToJson(e)
//     val readableString = Json.prettyPrint(json)
//     println(readableString)
//
//     // Convert Json to model
//     //TODO: use json.Parse to create JsValue
//     val event = EventUtil.FromJson(json).get
//
//     event.summary should equal("TestSummary")
//     event.start should equal("TestStart")
//     event.end should equal("TestEnd")
//     event.description should equal("")
//   }

  it should "use play.api.libs.json for Events" in {
    var events = new ListBuffer[Event]
    val e1 = Event("Summary1", "Start1", "", "")
    val e2 = Event("Summary2", "Start2", "", "")
    events += e1
    events += e2
    val eventsSeq = events.toSeq
    val json = EventUtil.ConvertEventsToJson(eventsSeq)
    val readableString = Json.prettyPrint(json)
    println(readableString)

    val jsArray = json.asInstanceOf[JsArray]
    val es = EventUtil.ConvertJsonToEvents(jsArray);
    es(0).summary should equal("Summary1")
    es(1).summary should equal("Summary2")
  }
}
