println("***PatternMatch Exercise***")
val l = List(1,2,3)
//l.map(i => println(i))
//l.map(i => i match {
//	case 1 => println("1") 
//	case 2 => println("2") 
//	case 3 => println("3") 
//}
//)

// map transforms the collection and returns a new collection

l.foreach(i => i match {
	case 1 | 2 | 3 => println(i) 
}
)

val sl = List("name", "summary", "date")
sl.foreach(s => s match {
	case "name" | "summary" => println(s)
	case _ => println("XXX")
	})

val s = new java.lang.String("tes")
s match {
	case "test" =>println("matched")
	case _ => //Requiered even do nothing.
}
