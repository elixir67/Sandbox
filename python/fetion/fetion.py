#!/usr/bin/python
#coding:utf-8

#Author: Dan Lin
#Date: 	 2012/5/6
#Helper class to send message with WAP fetion 
import os
import sys
import string
import cookielib
import urllib
import urllib2
import re

url_login = 'http://f.10086.cn/im/login/inputpasssubmit1.action'
url_logout = 'http://f.10086.cn//im/index/logoutsubmit.action?t='
url_msg = 'http://f.10086.cn/im/user/sendMsgToMyselfs.action'
loginstatus = '4' #隐身模式
arg_t = ''

class Fetion(object):
	def __init__ (self):
		cj = cookielib.LWPCookieJar()
		self.opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
		urllib2.install_opener(self.opener)

	def SetInfo(self,phone,password,loginstatus):
		"""
		@phone	     :手机号码
		@password    ：飞信密码
		@loginstatus ：登录状态
			      正常	0
			      隐身	1
			      忙碌	2
			      离开	3
		"""
		self.phone=phone
		self.pwd=password
		self.loginstatus=loginstatus
		
	def LogIn(self):
		args = {'pass':self.pwd, 'm':self.phone,'loginstatus':self.loginstatus}
		print '登录中...'
		req = urllib2.Request(url_login, urllib.urlencode(args))
		jump = self.opener.open(req)
		page = jump.read();
		# print "page:" + page
		url = re.compile(r'<card id="start".*?ontimer="(.*?);').findall(page)[0]             
		self.arg_t = re.compile(r't=(\d*)').findall(page)[0]
		if url == '/im/login/login.action':                                                   
			print 'Login Failed!'
			raw_input('Press any key to exit.')
			return False
		else:
			print '登录成果!'
			return True
	
	def SendMe(self, msg):
		if self.arg_t==-1:
			print '请先登录...'
			return False
		sendmsg = urllib2.Request(url_msg, urllib.urlencode({'msg':msg.decode('gbk').encode('utf-8')}))
		finish = urllib2.urlopen(sendmsg)
		if finish.geturl == 'http://f.10086.cn/im/user/sendMsgToMyself.action' :
			print '发送消息给自己失败!'
		else:
			print '发送消息给自己成功'
		
	def GetFriendId(self,FriendInfo):
		# '''GetFriendId ...
		# @FriendInfo ： 好友手机or好友昵称
		# '''
		if self.arg_t==-1:
			print '请先登录...'
			return -1
		params = {'searchText':FriendInfo}
		url = "http://f.10086.cn/im/index/searchOtherInfoList.action?t="+self.arg_t
		req = urllib2.Request(url,urllib.urlencode(params))
		jump = self.opener.open(req)
		page = jump.read()
		f=re.search('touserid=.*?&',page)
		if f:
			line_content = f.group()
			f=re.search('\d\d\d*',line_content)
			if f:
				return f.group()	
		print '未找到该手机号的好友'
		return -1
		
	def SendWithId(self,friendId,msg):
		if self.arg_t==-1:
			print '请先登录...'
			return False
		params={'msg':msg.decode('gbk').encode('utf-8')}
		url = "http://f.10086.cn/im/chat/sendMsg.action?touserid="+friendId
		req = urllib2.Request(url,urllib.urlencode(params))
		jump = self.opener.open(req)
		page = jump.read()
		f = re.search('/im/chat/toinputMsg.action?',page)
		if f:
			print '发送消息给好友成功'
			return True
		else:
			print '发送消息给好友失败'
			return False
			
	def LogOut(self):
		if self.arg_t==-1:
			print '您没有登录...'
			return False
		url = "http://f.10086.cn/im/index/logoutsubmit.action?t="+self.arg_t
		req = urllib2.Request(url)
		response = self.opener.open(req)
		print '注销成功'
		return True
		
def SendMessage(user, pwd, sendto, msg):
	fetion = Fetion()
	#隐身登录 --- 1
	loginstatus=1
	fetion.SetInfo(user, pwd, loginstatus)
	if fetion.LogIn():
		if user == sendto:
			fetion.SendMe(msg)
		else:
			friendId = fetion.GetFriendId(sendto)
			if -1 != friendId:
				fetion.SendWithId(friendId, msg)
	fetion.LogOut()
