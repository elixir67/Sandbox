#!/usr/bin/python
#coding:utf-8

import cookielib
import urllib
import urllib2
import re

url_login = 'http://f.10086.cn/im/login/inputpasssubmit1.action'
url_logout = 'http://f.10086.cn//im/index/logoutsubmit.action?t='
url_msg = 'http://f.10086.cn/im/user/sendMsgToMyselfs.action'
user = '15900477006'
password = 'Furture67'
loginstatus = '4' #ÒþÉíÄ£Ê½
arg_t = ''

def fetion(msg):
    cj = cookielib.LWPCookieJar()
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    urllib2.install_opener(opener)
    args = {'pass':password, 'm':user,'loginstatus':loginstatus}
    print 'Logining...'
    req = urllib2.Request(url_login, urllib.urlencode(args))
    jump = opener.open(req)
    page = jump.read();
    url = re.compile(r'<card id="start".*?ontimer="(.*?);').findall(page)[0]             
    arg_t = re.compile(r't=(\d*)').findall(page)[0]
    if url == '/im/login/login.action':                                                   
        print 'Login Failed!'
        raw_input('Press any key to exit.')
        return
    else:
        print 'Login Successfully!'
    sendmsg = urllib2.Request(url_msg, urllib.urlencode({'msg':msg.decode('gbk').encode('utf-8')}))
    finish = urllib2.urlopen(sendmsg)

    if finish.geturl == 'http://f.10086.cn/im/user/sendMsgToMyself.action' :
        print 'Send Failed!'
    else:
        print 'Send Successfully'
    logout = urllib2.Request(url_logout + arg_t)
    response = urllib2.urlopen(logout)                                                    
    print 'Logout Successfully!'
	#print response.read().decode('utf-8').encode('gbk')

msg = raw_input('what do you want to say:')
fetion(msg)
