import play.api.libs.json.{JsPath, Reads, Json, Writes}
import play.api.libs.functional.syntax._

/**
 * Created by lind on 11/18/2014.
 */
case class Event(summary: String, start: String, end: String, description: String)


