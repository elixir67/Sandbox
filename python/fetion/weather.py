#coding:utf-8
import urllib
from xml.dom import minidom
 
proc = lambda tnlist, conds : [
	[temp.getAttribute('data') for temp in conds.getElementsByTagName(tagname)][0]
	for tagname in (tnlist) ]
 
data = urllib.urlopen('http://www.google.com/ig/api?weather=…œ∫£&hl=zh-cn').read().decode('gbk').encode('utf8')
xmldoc = minidom.parseString(data)
curconds = xmldoc.getElementsByTagName("current_conditions")
print str(curconds)
(t, h, c, w) = proc(('temp_c', 'humidity', 'condition', 'wind_condition'), curconds[0])
print t
print h
print c
print w
 
# for cond in xmldoc.getElementsByTagName("forecast_conditions"):
	# (d, l, h, c) = proc(('day_of_week', 'low', 'high', 'condition'), cond)
	# print '%s: %s/%s %s' % (d, l, h, c)
