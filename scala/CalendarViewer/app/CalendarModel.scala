import java.io.FileInputStream

import scala.collection.JavaConversions._
import net.fortuna.ical4j.data.CalendarBuilder
import net.fortuna.ical4j.model.{Property, Component, Calendar}
import org.joda.time.DateTime

/**
 * Created by lind on 10/31/2014.
 */
class CalendarModel {
  def getCalendars: Boolean = {

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

    for(cc <- calendar.getComponents()) {
      //println(cal.toString())
      if(cc.isInstanceOf[Component]){
        val component = cc.asInstanceOf[Component];
        for(cp <- component.getProperties()){
          val property = cp.asInstanceOf[Property]
          val name = property.getName()

          name match {
            case "SUMMARY" | "DTSTART" =>  println("Property [" + name + ", " + property.getValue() + "]")
//            case "DTSTART" => {
//              val s = property.getValue()
//              val dt = new DateTime(s)
//              println(dt.toString())
//            }
            case _ => //do nothing
          }
        }

      }

    }
    true
  }

  def parseCalendar {

  }
}
