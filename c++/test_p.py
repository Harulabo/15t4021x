# -*- coding: utf-8 -*-

x1 = [i for i in range(31)]
x2 = [i + 0.2 for i in x1]

con = x1[:]
cpn = x1[:]

# 先行研究 PDave
sen = [0,0,0,0,0.22,0,0,0,0.42,0.24,0,0.17,0.11,0,0.81,0.17,0.29,0.01,1.09,0.02,0.24,0.51,0.58,0.96,1.65,0.41,0.69,2.71,3.44,3.70,4.78]
so = [30,30,30,30,6,30,27,30,7,0,30,7,5,30,0,0,0,26,1,19,13,4,0,0,0,0,0,0,0,0,0]
sp = [30,30,30,30,30,30,30,30,28,30,30,30,30,30,20,30,28,30,9,30,28,25,27,15,0,30,22,0,0,0,0]

# 提案手法　PDave
tei = [0,0,0,0,0.06,0,0.06,0,0.14,0,0,0,0.00,0.04,0.15,0,0,0,0.13,0,0,0.02,0.11,0.35,0.14,0.01,0.02,0.24,0.38,0.39,0.27]
to = [30,30,30,30,17,30,24,30,15,30,30,30,7,23,12,30,30,30,25,30,30,29,6,3,2,21,16,0,0,0,0]
tp = [30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,29,30,30,30,30,30,30,30]

sss = [[to[i]-so[i],i] for i in range(31)]
sss.sort(key=lambda x:x[0])
co = [sss[i][1] for i in range(31)]
print(co)
print()