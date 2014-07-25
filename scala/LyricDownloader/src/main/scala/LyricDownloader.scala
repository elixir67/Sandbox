import sys.process._
import java.net.URL
import java.io.File
import java.util.regex.Pattern

import scala.io.Source

/**
 * Created by lind on 7/23/2014.
 */


object LyricDownloader extends App{
  val SongsFolder = "C:\\Users\\lind\\Documents\\百度云同步盘\\兔博士\\儿歌"
  for (file <- new File(SongsFolder).listFiles) { processFile(file.getName()) }
  // test
  // processFile("001小宝贝快快睡.mp3")

  def processFile(filename: String):Unit ={

    val songName = getSongName(filename)
    val url = getLyricURL(songName)
    if(url !="")
      downloadLyric(url, filename)
  }
  def downloadLyric(url: String, filename: String): Unit ={
    val path = "C:\\Test\\" + filename.replace(".mp3", ".lrc")
    new URL(url) #> new File(path) !!
  }
  def getSongName(filename: String): String = {
    // file name is similar patten, like "111亲亲我.mp3"
    val m = Pattern.compile("\\d+(.+).mp3").matcher(filename)
    var songName = ""
    if (m.find)
      songName = m.group(1)
    println(songName)
    return songName
  }

  def getLyricURL(songName: String):String ={
    val url = "http://music.baidu.com/search/lrc?key=" + songName
    val it = Source.fromURL(url).getLines()
    var lyricUrl = ""
    while (it.hasNext)   {
      // <a class="down-lrc-btn { 'href':'/data2/lrc/88576466/88576466.lrc' }" href="#">下载LRC歌词</a>
      val line = it.next()
      val m = Pattern.compile(".+down-lrc-btn \\{ 'href':'(.+)'.+").matcher(line)
      if(null != m && m.find())
      {
        val lyric = m.group(1)
        println(lyric)
        return "http://music.baidu.com" + lyric
      }
    }
    return ""
  }
}

