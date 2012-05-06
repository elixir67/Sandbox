#!user/bin/python
#coding:utf-8

import urllib2
import re
import fetion
import ConfigParser
import getopt
import sys

URL_HQ = 'http://bbs.hq1388.com/forum.php?mod=viewthread&tid=15525&extra=page%3D1'
LUMIA_PATTERN = r"Nokia Lumia 800"
PRICE_PATTERN = '<td><strong>(.+)￥(.*?)<.+'
FINISH_PATTERN = r'点击图片查看详情'

# Python has no build-in enum type.
# It's a simple workaround here.
class ParseState:
	(Start, Find, Finish) = range(0, 3)

def get_lumia_prices():	
	state = ParseState.Start
	prices = {}
	for line in urllib2.urlopen(URL_HQ):
		if ParseState.Start == state:
			if re.search(LUMIA_PATTERN, line, re.I):	
				state =  ParseState.Find
		elif ParseState.Find == state:
			m = re.match(PRICE_PATTERN, line, re.I)
			if m:
				prices[m.group(1).strip()] = m.group(2).strip()
			elif re.search(FINISH_PATTERN, line):
				state =  ParseState.Finish
				break
				
	msg = LUMIA_PATTERN	+ '当天价格--'	
	for key, value in prices.iteritems():
		msg += key + ':' + value + " "
	return msg

def usage():
	print 'python Lumia800.py 输出Lumia800当日价格' 
	print 'python Lumia800.py -s 输出Lumia800当日价格并发送短信' 
	print 'python Lumia800.py -h 帮助' 

def send_msg(msg):
	cfg = ConfigParser.ConfigParser()
	cfg.read("fetion.ini")
	user = cfg.get("Source", "user")
	pwd = cfg.get("Source", "pwd")
	fetion.SendMessage(user, pwd, 'XXX', msg)
	fetion.SendMessage(user, pwd, 'XXX', msg)
	
opts, args = getopt.getopt(sys.argv[1:], "sh", ["help"])
need_send_message = False
for o,v in opts:
	if o.lower() == '-s':
		need_send_message = True
	if o.lower() in ('-h','--help'):
		usage()
		sys.exit()
		
msg = get_lumia_prices()
print msg
if need_send_message:
	send_msg(msg)
