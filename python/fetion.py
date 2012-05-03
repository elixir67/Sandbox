#!/usr/bin/python
#coding:utf-8
"""
	Last Update	: 2011-04-25
	Author		: yqshare
	Site		: http://yqshare.com
	mail		: mail#yqshare.com
	description	: class for fetion
"""
import sys,re,urllib2,urllib,cookielib,os,getpass
import cPickle as p
class fetion(object):
	# '''for users of fetion.

	# send the msg to the users.
	# the member are list:
	# SetInfo 	: 设制发送用户信息
	# LogIn 		：登录飞信
	# SendWithId 	: 根据好友id发送消息
	# GetFriendId 	: 由好友信息读取用户id
	# AddFriend 	： 添加好友
	# LogOut		： 注消飞信
	# '''	
	def __init__ (self):
		self.phone=self.pwd=self.loginstatus=self.t=''
		self.operate=''
		self.origURL='http://f.10086.cn/im/login/login.action'
		self.cj=cookielib.LWPCookieJar()
		if os.path.isfile('fetion.coockie'):
			self.cj.revert('fetion.coockie')
		self.opener=urllib2.build_opener( urllib2.HTTPCookieProcessor(self.cj))
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
		# '''login in the f10086.com
		
		# sucess return 0; fail return -1'''
		params={'m':self.phone,'pass':self.pwd,'loginstatus':self.loginstatus}
		req=urllib2.Request("http://f.10086.cn/im/login/inputpasssubmit1.action",urllib.urlencode(params))
		req.add_header('User-Agent', 'Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) \
						AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16')
		self.operate=self.opener.open(req)
		html=self.operate.read()
		#print html
		reg='ontimer=\".*?\"'
		f=re.search(reg,html)
		if f:
			line_content = f.group()
			reg='\d\d\d\d\d*'
			f=re.search(reg,line_content)
			
			if f:
				self.t = f.group()			
				return 0
			else:
				self.t = -1
				return -1
	
	def SendWithId(self,FriendId,Msg):
		# '''send the message to user ...
		# @FriendId ： 好友id
		# @Msg ： 欲发送的消息
		# '''
		if self.t==-1:
			print '请先登录...'
			return -1
		params={'msg':Msg,'touchTextLength':'','touchTitle':'','backUrl':''}
		url = "http://f.10086.cn/im/chat/sendMsg.action?touserid="+FriendId
		req=urllib2.Request(url,urllib.urlencode(params))
		req.add_header('User-Agent', 'Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) \
						AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16')
		self.operate=self.opener.open(req)
		html=self.operate.read()
		reg='消息成功'
		f=re.search(reg,html)
		if f:
			return 0
		else:
			return -1

	def GetFriendId(self,FriendInfo):
		# '''GetFriendId ...
		# @FriendInfo ： 好友手机or好友昵称
		# '''
		if self.t==-1:
			print '请先登录...'
			return -1
		params={'searchText':FriendInfo}
		url = "http://f.10086.cn/im/index/searchOtherInfoList.action?t="+self.t
		req=urllib2.Request(url,urllib.urlencode(params))
		req.add_header('User-Agent', 'Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) \
						AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16')
		self.operate=self.opener.open(req)
		html=self.operate.read()
		reg='touserid=.*?&'
		f=re.search(reg,html)

		if f:
			line_content = f.group()
			reg='\d\d\d*'
			f=re.search(reg,line_content)
			if f:
				return f.group()		
		return -1


	def AddFriend(self,FriendPhone,NickName):
		# '''添加好友 ...
		# @FriendPhone ： 好友手机or好友飞信号
		# @NickName ： 你的昵称或姓名
		# '''
		if self.t==-1:
			print '请先登录...'
			return -1
		params={'nickname':NickName,'buddylist':0,'localName':'','number':FriendPhone,'type':0}
		url = "http://f.10086.cn/im/user/insertfriendsubmit.action"
		req=urllib2.Request(url,urllib.urlencode(params))
		req.add_header('User-Agent', 'Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) \
						AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16')
		self.operate=self.opener.open(req)
		html=self.operate.read()
		reg='发送成功!待对方同意'
		f=re.search(reg,html)
		if f:
			return 1
		else:
			return -1
	def LogOut(self):
		# '''退出 ...
		# '''
		if self.t==-1:
			print '您没有登录...'
			return -1
		url = "http://f.10086.cn/im/index/logoutsubmit.action?t="+self.t
		req=urllib2.Request(url)
		req.add_header('User-Agent', 'Mozilla/5.0 (iPhone; U; CPU iPhone OS 3_0 like Mac OS X; en-us) \
						AppleWebKit/528.18 (KHTML, like Gecko) Version/4.0 Mobile/7A341 Safari/528.16')
		self.operate=self.opener.open(req)



if __name__ == "__main__":
	fetion=fetion()

	phone='15900477006'#raw_input("输入帐号：")

	password='Furture67'#getpass.getpass("输入密码：")
	#隐身登录 --- 1
	loginstatus=1
	#初始化用户信息
	fetion.SetInfo(phone,password,loginstatus)
	#登录飞信
	print "登录中，请耐心等待..."
	
	if fetion.LogIn()==-1:
		print "对不起,登录失败..."
		sys.exit()
	 
	print "请选择菜单：\n 1.发送消息给好友;\n 2.添加好友;\n 3.退出。"
	# control = raw_input()
	# if control == '1':
		# while True:
			# print "输入你好友的手机号或者飞信昵称："
			# FriendInfo = raw_input()
			# if FriendInfo=='3':
				# break
		 	# FriendId = fetion.GetFriendId(FriendInfo)
			# if FriendId == -1 :
				# print "你输入的信息不正确或该信息不你的好友！"
				# continue
			# print "输入您要发送的信息："
			# Msg = raw_input()		
			# Statu = fetion.SendWithId(FriendId,Msg)
			# if Statu != -1:
				# print "发送成功，若要退出请输入 3 ."
			# else:
				# print "发送失败，请稍候再试..."

	# if control == '2':
		# while True:
			# print "输入你要添加好友的手机号或飞信号："
			# FriendInfo = raw_input()
			# if FriendInfo=='3':
				# exit
			# print "输入你的昵称（该信息将显示到好友的邀请短信上！）："
			# NickName = raw_input()
			# Statu = fetion.AddFriend(FriendInfo,NickName)
			# if Statu != -1 :
				# print "添加好友请求发送成功，若要退出请输入 3 ."
			# else:
				# print "添加好友请求发送失败，请稍候再试..."		

	# if control == '3':
		# exit
	fetion.LogOut()
