import collections
import re
import string 
reg=r'[a-zA-Z]+'
s=input()
ls1=re.findall(reg,s)
lslen=[len(ch) for ch in ls1]
maxlen=max(lslen)
dic1=collections.OrderedDict()
for ch in ls1:
    ch=ch.upper()
    dic1[ch]=dic1.get(ch,0)+1
    
for key,value in dic1.items():
    n=maxlen-len(key)
    print(' '*n,key,':','*'*value,value,sep='')