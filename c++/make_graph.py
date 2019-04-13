# -*- coding: utf-8 -*-

from matplotlib import pyplot
from matplotlib.font_manager import FontProperties

fp = FontProperties(fname='/Library/Fonts/ipag.ttf',size = 14)

x1 = [i for i in range(31)]
x2 = [i + 0.3 for i in x1]

# 先行研究 PDave
sen = [0,0,0,0,0.22,0,0,0,0.42,0.24,0,0.17,0.11,0,0.81,0.17,0.29,0.01,1.09,0.02,0.24,0.51,0.58,0.96,1.65,0.41,0.69,2.71,3.44,3.70,4.78]
so = [30,30,30,30,6,30,27,30,7,0,30,7,5,30,0,0,0,26,1,19,13,4,0,0,0,0,0,0,0,0,0]
sp = [30,30,30,30,30,30,30,30,28,30,30,30,30,30,20,30,28,30,9,30,28,25,27,15,0,30,22,0,0,0,0]
sti = []

# 提案手法　PDave
tei = [0,0,0,0,0.06,0,0.06,0,0.14,0,0,0,0.00,0.04,0.15,0,0,0,0.13,0,0,0.02,0.11,0.35,0.14,0.01,0.02,0.24,0.38,0.39,0.27]
to = [30,30,30,30,17,30,24,30,15,30,30,30,7,23,12,30,30,30,25,30,30,29,6,3,2,21,16,0,0,0,0]
tp = [30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,29,30,30,30,30,30,30,30]

# Label
label = ["berlin52","st70","pr76","kroA100","eil101","lin105","pr107","pr124","ch130","pr136","pr144","kroA150","kroB150","pr152","rat195","d198","kroB200","ts225","tsp225","pr226","pr264","a280","pr299","lin318","rd400","fl417","pr439","rat575","rat783","pr1002","nrw1379"]
#print(len(label))

#pyplot.plot(label,sen)
pyplot.bar(x1,sen,color='#377eb8',width=0.4,label = u'先行研究',align="center")
pyplot.bar(x2,tei,color='#ff7f00',width=0.4,label = u'提案研究',align="center")

#sss = [[-(so[i]+to[i]),i] for i in range(31)]
#sss = [[tp[i]-sp[i],i] for i in range(31)]
#sss.sort(key=lambda x:x[0])
#co = [sss[i][1] for i in range(31)]
#label = [label[i] for i in co]

#to = [to[i] for i in co]
#so = [so[i] for i in co]
#tp = [tp[i] for i in co]
#sp = [sp[i] for i in co]

#pyplot.plot(sp,label = u'先行研究')
#pyplot.plot(so,label = u'先行研究')
#pyplot.bar(x1,sp,color='#377eb8',width=0.3,label = u'先行研究',align="center")
#pyplot.bar(x1,so,color='#377eb8',width=0.3,label = u'先行研究',align="center")

#pyplot.plot(tp,label = u'提案研究')
#pyplot.plot(to,label = u'提案研究')
#pyplot.bar(x2,tp,color='#ff7f00',width=0.3,label = u'提案手法',align="center")
#pyplot.bar(x2,to,color='#ff7f00',width=0.3,label = u'提案手法',align="center")

pyplot.ylabel("PDave(%)",fontsize=18,fontproperties=fp)
#pyplot.grid(which = "major", axis = "y", color = "blue", alpha = 0.8,linestyle = "--", linewidth = 1)
pyplot.xticks(x2,label,rotation = 90,fontsize = 7)


#pyplot.legend(loc='lower left',prop = fp)
pyplot.legend(prop = fp)
pyplot.show()
#input()
