import org.joda.time.DateTime
import org.joda.time.format.{DateTimeFormat, DateTimeFormatter}
import org.scalatest.{Matchers, FlatSpec}


/**
 * Created by lind on 11/3/2014.
 */
class DateTimeSpec extends FlatSpec with Matchers{
  "DateTimeSpec" should " parse the datetime successfully" in{
    val sdt = "04/02/2011 20:27:05"
    val df: DateTimeFormatter = DateTimeFormat.forPattern("dd/MM/yyyy HH:mm:ss")
    val dt = df.parseDateTime(sdt)
    //val dt = new Date(UTC_PATTERN.parse(sdt));
    val year = dt.getYear()
    println(year)
    year should be > 0
  }

  it should " parse the datetime successully with UTC format." in {
    val UTC_PATTERN = "yyyyMMdd'T'HHmmss'Z'"
    val sdt = "20140817T053000Z";
    val df: DateTimeFormatter = DateTimeFormat.forPattern(UTC_PATTERN)
    val dt: DateTime = df.parseDateTime(sdt)
    val year = dt.getYear()
    println(year)
    year should be > 0
  }
}
