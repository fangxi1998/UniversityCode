import operator
class person3:
    
    
    def __init__(self,Id,age):
        self.Id=Id
        self.age=age
        
       
        
        
       
        
    
   


f=[]
n=int(input())

for i in range(n):
    a,b=map(str,input().split())
   
    
    f.append(person3(a,b))


    

g=[]
h=[]

for i in range(n):
    if(f[i].age>='60'):
        g.append(f[i])
    else:
        h.append(f[i])


g.sort(key=(operator.attrgetter('age')),reverse=True)
#h.sort(key=(operator.attrgetter('age')),reverse=True)
for i in range(len(g)):
    print(g[i].Id)

for i in range(len(h)):
    print(h[i].Id)   