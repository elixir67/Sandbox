#!user/bin/python
#coding:utf-8

from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
import numpy as np

#============================================# read data
title = ''
dates = []
prices = []
counter = 0;
for line in file("SH600000.TXT"):
    if counter == 0:
        title = line
        continue;
    if counter < 2:
        continue;
    ++counter
    info = line.split()
    dates.append(info[0])
    prices.append(info[4])
#    
#    pops.append(float(info[1]))
#    lat  = float(info[2][:-1])
#    if info[2][-1] == 'S': lat = -lat
#    lats.append(lat)
#    lon  = float(info[3][:-1])
#    if info[3][-1] == 'W': lon = -lon + 360.0
#    lons.append(lon)
#    country = info[4]
#    countries.append(country)


plt.title(title)
plt.show()
print dates
print prices