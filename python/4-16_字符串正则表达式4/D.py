import collections
n=input()
a=''
b=[]
for i in n:
    
    if i.isalpha():
        
        a=a+i.upper()
    if i.isspace():
        a=a+i


s1=a.split()
for i in s1:
    if i not in b:
        b.append(i)
    
c=collections.Counter(s1)

for j in b:

    print("{}:{}".format(j,c[j]))