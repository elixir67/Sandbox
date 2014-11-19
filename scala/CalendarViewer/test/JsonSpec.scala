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
   }

   it should "use the writer of play.api.libs.json" in {
     // Convert model to Json
     val e = Event("TestSummary", "TestStart", "TestEnd", "")
     val json: JsValue = EventUtil.ToJson(e)
     val readableString = Json.prettyPrint(json)
     println(readableString)

     // Convert Json to model
     //TODO: use json.Parse to create JsValue
     val event = EventUtil.FromJson(json).get

     event.summary should equal("TestSummary")
     event.start should equal("TestStart")
     event.end should equal("TestEnd")
     event.description should equal("")
   }
}
