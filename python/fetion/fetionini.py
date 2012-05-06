#!/usr/bin/python
#coding:utf-8

#Author: Dan Lin
#Date: 	 2012/5/6
import ConfigParser
import fetion

DEFAULT_INI = "c:/tools/fetion.ini"

def fetionINI(msg = None, ini = DEFAULT_INI):
	# Open the INI file to read
	cfg = ConfigParser.ConfigParser()
	cfg.read(ini)

	# read user and pwd option from Source section
	user = cfg.get("Source", "user")
	pwd = cfg.get("Source", "pwd")
	
	if msg is None:
		msg = cfg.get("Target", "message")	

	sendtos = cfg.get("Target", "sendto").split(',')
	for sendto in sendtos:
		fetion.SendMessage(user, pwd, sendto, msg)

if __name__ == '__main__':		
	fetionINI()
