name := """CalendarViewer"""

version := "1.0-SNAPSHOT"

lazy val root = (project in file(".")).enablePlugins(PlayScala)

scalaVersion := "2.11.1"

libraryDependencies ++= Seq(
  jdbc,
  anorm,
  cache,
  ws
)

libraryDependencies += "org.mnode.ical4j" % "ical4j" % "1.0.2"

libraryDependencies += "org.scalatest" % "scalatest_2.11" % "2.2.1" % "test"

