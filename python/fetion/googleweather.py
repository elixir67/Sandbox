#coding:utf-8
import urllib2
from xml.dom import minidom
 
 # The google weather api is not official may close in the future but it's simple.
GOOGLE_WEATHER_URL = 'http://www.google.com/ig/api?weather=…œ∫£&hl=zh-cn'
 
proc = lambda tnlist, conds : [
	[temp.getAttribute('data') for temp in conds.getElementsByTagName(tagname)][0]
	for tagname in (tnlist) ]

# Note: the encoding is important to parse correctly
data = urllib2.urlopen(GOOGLE_WEATHER_URL.decode('gbk').encode('utf-8')).read().decode('gbk').encode('utf8')
xmldoc = minidom.parseString(data)
curconds = xmldoc.getElementsByTagName("current_conditions")
(t, h, c, w) = proc(('temp_c', 'humidity', 'condition', 'wind_condition'), curconds[0])
print t
print h
print c
print w
 
for cond in xmldoc.getElementsByTagName("forecast_conditions"):
	(d, l, h, c) = proc(('day_of_week', 'low', 'high', 'condition'), cond)
	print '%s: %s/%s %s' % (d, l, h, c)
