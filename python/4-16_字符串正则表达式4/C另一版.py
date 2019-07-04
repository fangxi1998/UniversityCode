import collections
n=input()
a=''
b=[]
for i in n:
    
    if i.isalpha():
        #i=i.upper()
        a=a+i.upper()
    if i.isspace():
        a=a+i

print(a)
s1=a.split()
maxlen=max([len(ch) for ch in s1])
print(maxlen)

for i in s1:
    if i not in b:
        b.append(i)
    
c=collections.Counter(s1)

for j in b:
    n=maxlen-len(j)
    print(' '*n,j,':','*'*c[j],c[j],sep='')


