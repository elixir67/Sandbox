#coding:utf-8
import urllib2
from xml.dom import minidom
import getopt
import sys
import fetionini

 # The google weather api is not official may close in the future but it's simple.
GOOGLE_WEATHER_URL = 'http://www.google.com/ig/api?weather=Shanghai&hl=zh-cn'
 
def getweather():
	proc = lambda tnlist, conds : [
		[temp.getAttribute('data') for temp in conds.getElementsByTagName(tagname)][0]
		for tagname in (tnlist) ]

	# Note: the encoding is important to parse correctly
	data = urllib2.urlopen(GOOGLE_WEATHER_URL).read().decode('gbk').encode('utf-8')
	xmldoc = minidom.parseString(data)
	
	# so far the current conditions are not expected
	# curconds = xmldoc.getElementsByTagName("current_conditions")
	# (t, h, c, w) = proc(('temp_c', 'humidity', 'condition', 'wind_condition'), curconds[0])
	# print t
	# print h
	# print c
	# print w
	 
	msg = ''
	for cond in xmldoc.getElementsByTagName("forecast_conditions"):
		(d, l, h, c) = proc(('day_of_week', 'low', 'high', 'condition'), cond)
		# print '%s: %s/%s %s' % (d, l, h, c)
		msg += '%s: %s/%s %s' % (d, l, h, c) + '\n'
	return msg

def usage():
	file = sys.argv[0]
	print 'python ' + file + u' 输出结果到当前屏幕' 
	print 'python ' + file + u' -s 输出结果到当前屏幕并发送短信' 
	print 'python ' + file + u' -h 帮助'

def run():
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
	msg = getweather().encode('gbk')
	print msg
	if need_send_message:
		fetionini.fetionINI(msg)
	
if __name__ == '__main__':
	run()
