# Written by Vamei

from datetime import datetime, timedelta
import re
import numpy as np

import matplotlib
matplotlib.rcParams['text.color'] = 'white'
matplotlib.rcParams['xtick.color'] = 'white'
matplotlib.rcParams['ytick.color'] = 'white'

from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt

font = 'monospace'

# This function is to plot the base map
def plotBase(fig, dt=None):
    m = Basemap(projection='merc',
                lon_0=0,lat_0=0,lat_ts=0,
                llcrnrlat=0,urcrnrlat=50,
                llcrnrlon=-100,urcrnrlon=-50,
                resolution='l')
    m.drawcountries(linewidth=1, color='k')
    m.drawmapscale(-90, 5, -90, 5, 1000, barstyle='fancy')
    m.bluemarble(scale=1)

    # Get Position of NYC, longitude -74.0064, latitude 40.7142
    x,y    = m(-74.0064, 40.7142)
    # Plot NYC
    m.scatter(x, y, s=100,  marker='*', color='0.5', alpha=1)
    plt.text(x,y,'NYC', fontsize='15')

    if dt is not None: m.nightshade(dt, alpha = 0.3)
    return m

# Hurricane category colors
color_dict = {'TROPICAL DEPRESSION':'#AEF100', 'TROPICAL STORM':'#FFD600', 'HURRICANE-1':'#FF6440', 'HURRICANE-2':'#8506A9'}

# Read data file, unzip from track.zip to get track.dat
fn  = 'track.dat'
rec = {'lat':[],'lon':[],'wind':[],'press':[],'dt':[],'cat':[]}
for i,line in enumerate(file(fn)):
    if i == 0: continue  # Jump over the first line
    # replace multiple whitespaces with a single whitespace
    line   = re.sub(r"\s+", ' ', line)
    pieces = line.split(" ")
    # retrieve information
    rec['lat'].append(float(pieces[0]))
    rec['lon'].append(float(pieces[1]))
    rec['wind'].append(float(pieces[3]))
    rec['press'].append(float(pieces[4]))
    rec['cat'].append((" ".join(pieces[5:])).strip())
    time   = pieces[2]
    time   = "2012/" + time
    rec['dt'].append(datetime.strptime(time,"%Y/%m/%d/%HZ"))

# Plot the track and the else
N = len(rec['lat'])
for idx in range(N):
    dt     = rec['dt'][idx]
    # Adjust time zone according to NYC
    lt     = dt - timedelta(hours=5)
    lon    = rec['lon'][idx]
    lat    = rec['lat'][idx]
    wind   = rec['wind'][idx]
    press  = rec['press'][idx]
    cat    = rec['cat'][idx]
    fig    = plt.figure()
    m      = plotBase(fig, dt)
    # From lon,lat to pixels
    x,y    = m(lon, lat)
    # Plot track
    for i in range(idx):
        a0,b0 = m(rec['lon'][i], rec['lat'][i])
        a1,b1 = m(rec['lon'][i+1], rec['lat'][i+1])
        m.plot((a0,a1),(b0,b1), linewidth=2.5,
                  color=color_dict[rec['cat'][i+1]])
    # Plot Sandy's current position
    m.scatter(x, y, s=100, c=color_dict[cat], alpha=0.8)
    # Annotate current position
    plt.annotate(
        cat, 
        xy = (x, y), xytext = (-5, -30),
        textcoords = 'offset points', ha = 'right', va = 'bottom',
        bbox = dict(boxstyle = 'round,pad=0.5', fc=color_dict[cat], alpha = 0.8),
        arrowprops = dict(arrowstyle = '->', connectionstyle = 'arc3,rad=0'))

    tx, ty = m(-98, 40)
    plt.text(tx,ty, 
            lt.strftime("Hurricane Sandy\n\nNYC LT:\n%Y-%m-%d %H:00:00\nData Source: NOAA\nBy Vamei"), 
            family=font,ha='left')
    # add a small axes to show pressure
    a = fig.add_axes([0.6,0.2,.15,.1])
    a.set_ylim((950,1000))
    a.set_xlim((-10,70))
    a.set_yticks([900,1050])
    a.set_xticks([0,60])
    a.set_title("Center Pressure (mb)", fontsize=10)
    a.plot(rec['press'])
    a.axvline(x=idx, color='r')
    # add a small axes to show wind
    a = fig.add_axes([0.6,0.4,.15,.1])
    a.set_ylim((0,100))
    a.set_xlim((-10,70))
    a.set_yticks([0,100])
    a.set_xticks([0,60])
    a.set_title("Max Wind (knots)", fontsize=10)
    a.plot(rec['wind'])
    a.axvline(x=idx, color='r')

    fig.savefig(('%04d.png' % idx))
    plt.close()