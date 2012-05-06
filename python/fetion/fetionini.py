#!/usr/bin/python
#coding:utf-8

#Author: Dan Lin
#Date: 	 2012/5/6
import ConfigParser
import fetion

cfg = ConfigParser.ConfigParser()
cfg.read("fetion.ini")
user = cfg.get("Source", "user")
pwd = cfg.get("Source", "pwd")
sendto = cfg.get("Target", "sendto")
msg = cfg.get("Target", "message")	

fetion.SendMessage(user, pwd, sendto, msg)


