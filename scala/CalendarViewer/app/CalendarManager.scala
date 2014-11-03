import java.io.{FileWriter, FileInputStream}

import scala.collection.JavaConversions._
import net.fortuna.ical4j.data.CalendarBuilder
import net.fortuna.ical4j.model.{Property, Component, Calendar}

import play.api.libs.json._
import play.api.libs.functional.syntax._

import org.joda.time.DateTime

/**
 * Created by lind on 10/31/2014.
 */
class CalendarManager {
  def getCalendars: Boolean = {
//    case class CalendarModel (summary: String, dtStart: String, dtEnd: String, description: String)
//    implicit val calendarWrites: Writes[CalendarModel] = {
//        (JsPath \ "summary").write[String] and
//        (JsPath \ "start").write[String] and
//        (JsPath \ "end").write[String] and
//        (JsPath \ "description").write[String]
//    }(unlift(CalendarModel.unapply))

    val pcName = System.getenv("COMPUTERNAME")
    val calendarFolder = pcName.toUpperCase() match  {
      case "SHA575R422" => "D:\\OneDrive\\Private"
      case "SHACNU332C7QX" => "C:\\Users\\lind\\SkyDrive\\Private"
      case _ => // Require resolve if happened
    }

    val calendarPath = calendarFolder + "\\Calendar_20140824.ics"
    val fin: FileInputStream = new FileInputStream(calendarPath);

    val builder: CalendarBuilder = new CalendarBuilder();

    val calendar: Calendar  = builder.build(fin);

    val fw = new FileWriter("calendar.txt")

    for(cc <- calendar.getComponents()) {
      //println(cal.toString())
      if(cc.isInstanceOf[Component]){
        val component = cc.asInstanceOf[Component];
        for(cp <- component.getProperties()){
          val property = cp.asInstanceOf[Property]
          val name = property.getName()

          name match {
            case "SUMMARY" | "DTSTART" | "DTEND" |"DESCRIPTION"=>  {
              val s = name + ": " + property.getValue()
              println(s)
              fw.write(s + "\n")
            }
//            case "DTSTART" => {
//              val s = property.getValue()
//              val dt = new DateTime(s)
//              println(dt.toString())
//            }
            case _ => //do nothing
          }
        }

      }
      fw.write("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n")

    }
    fw.close()
    true
  }

  def parseCalendar {

  }
}
