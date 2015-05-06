import java.io.{FileWriter, FileInputStream}

import scala.collection.JavaConversions._
import net.fortuna.ical4j.data.CalendarBuilder
import net.fortuna.ical4j.model.{Property, Component, Calendar}
import play.api.libs.json._

import scala.collection.mutable.ListBuffer

/**
 * Created by lind on 10/31/2014.
 */
class CalendarManager {
  def getCalendars: Boolean = {
    val pcName = System.getenv("COMPUTERNAME")
    val calendarFolder = pcName.toUpperCase() match  {
      case "SHA575R422" => "D:\\OneDrive\\Private\\Calendar\\"
      case "SHACNU332C7QX" => "C:\\Users\\lind\\SkyDrive\\Private\\Calendar\\"
      case _ => // Require resolve if happened
    }

    val calendarFile = "Calendar_20150506.ics"
    val calendarPath = calendarFolder + calendarFile
    val fin: FileInputStream = new FileInputStream(calendarPath);

    val builder: CalendarBuilder = new CalendarBuilder();

    val calendar: Calendar  = builder.build(fin);
    val outputFile = calendarFile.replace(".ics", ".txt")
    val fw = new FileWriter(outputFile)

    var events: ListBuffer[Event] = ListBuffer()

    for(cc <- calendar.getComponents()) {
      var (summary, start, end, description) = ("", "", "", "")
      var hasValue = false;
      if (cc.isInstanceOf[Component]) {
        val component = cc.asInstanceOf[Component];
        for (cp <- component.getProperties()) {
          val property = cp.asInstanceOf[Property]
          val name = property.getName()

          name match {
            case "SUMMARY" => {
              summary = property.getValue()
              hasValue = true
              output(fw, name, summary)
            }
            case "DTSTART" => {
              start = property.getValue()
              hasValue = true
              output(fw, name, start)
            }
            case "DTEND" => {
              end = property.getValue()
              hasValue = true
              output(fw, name, end)
            }
            case "DESCRIPTION" => {
              description = property.getValue()
              hasValue = true
              output(fw, name, description)
            }
            case _ => //do nothing
          }
        }
      }
      if (hasValue) {
        val event = Event(summary, start, end, description)
        events += event
      }
      fw.write("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n")
    }
    fw.close()

    val json = EventUtil.ConvertEventsToJson(events.toSeq)
    val content = Json.prettyPrint(json)
    println(content)

    val outputJsonFile = calendarFile.replace(".ics", ".json")
    val fwJson = new FileWriter(outputJsonFile)
    fwJson.write(content)
    fwJson.close

    true
  }

  def output(fw: FileWriter, name: String, value: String) {
    val s = name + ": " + value
    println(s)
    fw.write(s + "\n")
  }

  def parseCalendar {

  }
}
