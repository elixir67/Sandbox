#!user/bin/python
#coding:utf-8

import urllib2
import re
import ConfigParser
import getopt
import sys
import logging

import fetion
import fetionini

URL_HQ = 'http://bbs.hq1388.com/forum.php?mod=viewthread&tid=15525&extra=page%3D1'
LUMIA_PATTERN = r"Nokia Lumia 800"
PRICE_PATTERN = r'<td><strong>(.+)￥(.*?)<.+'
FINISH_PATTERN = r'点击图片查看详情'

# Python has no build-in enum type.
# It's a simple workaround here.
class ParseState:
	(Start, Find, Finish) = range(0, 3)

def get_lumia_prices():	
	state = ParseState.Start
	prices = {}
	logger = logging.getLogger()
	logFileName = sys.argv[0] + 'log.txt'
	handler = logging.FileHandler(logFileName)
	logger.addHandler(handler)
	logger.setLevel(logging.DEBUG)
	for line in urllib2.urlopen(URL_HQ):
		logger.debug(line)
		# regular expression match can only match the UTF-8 
		# if source code is UTF-8 encoding
		line = line.decode('gbk').encode('utf-8')
		if ParseState.Start == state:
			if re.search(LUMIA_PATTERN, line, re.I):	
				state =  ParseState.Find
		elif ParseState.Find == state:
			m = re.match(PRICE_PATTERN, line, re.I)
			if m:
				key = m.group(1).strip().decode('utf-8')
				value = m.group(2).strip().decode('utf-8')
				prices[key] = value
			elif re.search(FINISH_PATTERN, line):
				state =  ParseState.Finish
				break
				
	msg = u'Nokia Lumia 800当天价格--'	
	for key, value in prices.iteritems():
		logger.debug(key + u":" + value)
		msg += key + u':' + value + u" "
	return msg

def usage():
	print u'python Lumia800.py 输出Lumia800当日价格'
	print u'python Lumia800.py -s 输出Lumia800当日价格并发送短信' 
	print u'python Lumia800.py -h 帮助' 

need_send_message = False	
try:	
	opts, args = getopt.getopt(sys.argv[1:], "sh", ["help"])
except getopt.GetoptError, err:
	# print help information and exit:
	print str(err) # will print something like "option -a not recognized"
	usage()
	sys.exit(2)	
for o,v in opts:
	if o.lower() == '-s':
		need_send_message = True
	if o.lower() in ('-h','--help'):
		usage()
		sys.exit()
		
msg = get_lumia_prices()
print msg
if need_send_message:
	fetionini.fetionINI(msg.encode('gbk'))
