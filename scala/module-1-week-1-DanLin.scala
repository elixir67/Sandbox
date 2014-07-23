import java.io.{ByteArrayOutputStream, ByteArrayInputStream}

object ScalaApp {
  def main(args: Array[String]) {
    // Example 1
    (1 to 10) filter (_ % 2 == 1) foreach println

    // Example 2
    val results = for {
      a <- 1 to 9
      b <- 0 to 9
      val c = (10 * a + b) * a
      if ( c % 111 == 0)
    } yield (a, b, c / 111)

    println(results)

    // Example 3
    val greetings = "Hello World"

    val bais = new ByteArrayInputStream(greetings getBytes)
    val baos = new ByteArrayOutputStream

    val buffer = new Array[Byte](10)

    Stream continually(bais read(buffer)) takeWhile(_ != -1) foreach (baos write(buffer, 0, _))
    println(baos)

  }
}
