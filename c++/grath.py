import csv
from matplotlib import pyplot
from matplotlib.font_manager import FontProperties

#pyplot.plot(x軸, y軸)

xlist = [i for i in range(200)]

with open("sample.csv") as f:
	reader = csv.reader(f)
	header = next(reader)
	for lines in reader:
		ylist = [float(i) for i in lines]
		pyplot.plot(xlist,ylist)

fp = FontProperties(fname='/Library/Fonts/ipag.ttf',size = 14)
pyplot.xlabel(u'世代数',fontproperties=fp)
pyplot.ylabel(u'経路長',fontproperties=fp)
pyplot.show()