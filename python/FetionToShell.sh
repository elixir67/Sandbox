#!/bin/sh
#Convert Python Fetion To Shell @2012


user='xxxxxxxxx' #飞信账号 一般是你的手机号
password='xxxxx' #飞信密码,但愿只有你自己知道.
loginstatus='4' 
url_login='http://f.10086.cn/im/login/inputpasssubmit1.action'
url_logout='http://f.10086.cn//im/index/logoutsubmit.action'
url_msg='http://f.10086.cn/im/user/sendMsgToMyselfs.action'
TempDir='shfethionTmp'


read  -p "please enter :" msg
echo $msg
if [ -d "$TempDir" ]; then
   rm -rf ${TempDir}
   mkdir "$TempDir"
else
   mkdir "$TempDir"
fi
wget  -q -P ${TempDir} --save-cookies=${TempDir}/cookie --keep-session-cookies  --post-data "m=${user}&pass=${password}&loginstatus=${loginstatus}" ${url_login}
url=`grep -Eo '<card id="start".*?(ontimer="(.*?))' ${TempDir}/inputpasssubmit1.action | grep -Eo  '(\/+[^\s]*)n'`
arg_t=`grep -Eo  '<card id="start".*?(ontimer="(.*?))' ${TempDir}/inputpasssubmit1.action | grep -Eo  't=\w+'`
echo $url
if [ "${url}" = '/im/login/login.action' ];then                                                   
    echo 'Login Failed!'
      exit 0
else
    echo 'Login Successfully!'
fi
wget  -q -P ${TempDir} --load-cookies=${TempDir}/cookie --keep-session-cookies --post-data "msg=${msg}" ${url_msg}
echo $arg_t 
wget  -q -P ${TempDir} --load-cookies=${TempDir}/cookie --keep-session-cookies --post-data "${arg_t}" ${url_logout}
echo 'Logout Successfully!'
rm -rf ${TempDir}