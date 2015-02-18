import org.scalatest.FlatSpec
import org.scalatest.Matchers
import org.scalatest.{Matchers, FlatSpec}

/**
 * Created by lind on 10/31/2014.
 */
class CalendarSpec extends FlatSpec with Matchers{
  "Calendar" should "more than one item" in{
    val cal = new CalendarManager()
    val cals = cal.getCalendars
    //cals should be true
  }
}
