import operator
class person4:
    
    
    def __init__(self,Id,grade):
        self.Id=Id
        self.grade=grade
        
n,m=map(int,input().split())
f=[]

for i in range(n):
    a,b=map(int,input().split())
   
    
    f.append(person4(a,b))
num=int(m*1.5)
f.sort(key=operator.attrgetter('grade'),reverse=True)
line=f[num-1].grade
g=[]

for i in range(n):
    if(f[i].grade>=line):
        g.append(f[i])


for i in range(len(g)-1):
    if(g[i].grade==g[i+1].grade and g[i].Id>g[i+1].Id):
        g[i],g[i+1]=g[i+1],g[i]
print(line,len(g))
for i in range(len(g)):
    print(g[i].Id,g[i].grade)