package com.example
import akka.actor._
import scala.concurrent.duration._

case object Greet
case class WhoToGreet(who: String)
case class Greeting(msg: String)

class Greeter extends Actor{
  var greeting = ""

  def receive = {
    case WhoToGreet(who) => greeting = s"hello, $who"
    case Greet => sender ! Greeting(greeting)
  }
}

class GreetPrinter extends Actor {
  def receive = {
    case Greeting(msg) => println(msg)
  }
}

object Hello{
  def main(args: Array[String]): Unit = {
    val system = ActorSystem("hello-akka") // stystem name can only contacted by - between characters

    val greeter = system.actorOf(Props[Greeter],"greeter")

    val inbox = Inbox.create(system)

    // Tell the 'greeter' to change its 'greeting' message
    greeter.tell(WhoToGreet("akka"), ActorRef.noSender)

    // Ask the 'greeter for the latest 'greeting'
    // Reply should go to the "actor-in-a-box"
    inbox.send(greeter, Greet)

    // Wait 5 seconds for the reply with the 'greeting' message
    val Greeting(message1) = inbox.receive(5.seconds)
    println(s"Greeting: $message1")

    // Change the greeting and ask for it again
    greeter.tell(WhoToGreet("typesafe"), ActorRef.noSender)
    inbox.send(greeter, Greet)
    val Greeting(message2) = inbox.receive(5.seconds)
    println(s"Greeting: $message2")

    val greetPrinter = system.actorOf(Props[GreetPrinter])
    // after zero seconds, send a Greet message every second to the greeter with a sender of the greetPrinter
    system.scheduler.schedule(0.seconds, 1.second, greeter, Greet)(system.dispatcher, greetPrinter)

  }
}
