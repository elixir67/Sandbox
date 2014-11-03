println("***Exercise DataTypes***")
val s1 = "Hello"
val s2 = s1 + " World"
val pcName = System.getenv("COMPUTERNAME")
var calendarFolder = pcName.toUpperCase() match  {
	case "SHA575R422" => "C:\\Users\\lind\\SkyDrive\\Private"
	case _ =>
}
println(calendarFolder)

// if("Hello" == s1)
// 	println("Yes")