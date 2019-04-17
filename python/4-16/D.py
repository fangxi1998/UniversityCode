import collections
n=input().split('.' )
a=[]
mydict={} 
b=[0,0,0,0,0]
s=' '.join(n)
s=s.split(',')
s=' '.join(s)
s=s.split()
s=' '.join(s)

s=s.upper()


s1=s.split()


c=collections.Counter(s1)

for i in s1:
    if i not in a:
        a.append(i)



for j in a:
    print('{0:}:{1:}'.format(j,c[j]))
