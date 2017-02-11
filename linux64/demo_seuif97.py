
# -*- coding: utf-8 -*- 

import seuif97
import timeit
import cProfile, pstats
import io

p=16
t=350

#t = timeit.Timer("seuif97.pt2h(p,t)","from __main__ import seuif97,p,t")  
#if97time=t.timeit(1)
#print('Time(s)=',if97time)
#print(h)

pr = cProfile.Profile()
pr.enable()

h=linuxseuif97.pt2h(p,t)
    
pr.disable()
s = io.StringIO()
sortby = 'cumulative'
ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
ps.print_stats()
print (s.getvalue())


print(h)

