package models


object JsonFormats {
  import play.api.libs.json.Json

  implicit val clubFormat = Json.format[Club]
  implicit val userFormat = Json.format[User]
  implicit val activityFormat = Json.format[Activity]
}

