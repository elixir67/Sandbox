import groovy.io.FileType

/**
 * Created by dlin on 9/20/15.
 */

// Groovy RenameFiles.groovy
// Remove useless words in batch for my downloaded movies

// TODO: accept input parameter
// TODO: handle chinese characters in IntelliJ
// TODO: String match and replace by regular expressions

//def dirPath = "/Users/dlin/Downloads/movies/test" // for short test
//def RemoveWorlds = ['.BD', '.720p'] // for short test

def dirPath = "/Users/dlin/Downloads/movies"
def RemoveWorlds = ['[阳光电影www.ygdy8.com].',
                    '[电影天堂www.dygod.com].',
                    '[电影天堂www.dy2018.net]',
                    '[电影天堂-www.dy2018.net].',
                    '[电影天堂-www.dy2018.net]',
                    '[电影天堂www.dygod.cn]',
                    '.[中英双字.1024分辨率]',
                    'BD中英双字',
                    '.BD','.HD','.720p','.国语中字','.中英双字幕','.中英双字', '.国粤双语中字']
def dir = new File(dirPath)
dir.eachFileRecurse (FileType.FILES) { file ->
    def s = file.path;
    println 'original file path: ' + s
    RemoveWorlds.each { RemoveWorld ->
        s = s.minus(RemoveWorld);
    }
    println 'new file path: ' + s
    file.renameTo(s)
}
