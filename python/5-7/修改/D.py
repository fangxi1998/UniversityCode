class Score:
    
    def __init__(self,Id,grade):
        self.Id=Id
        self.grade=grade


    def __lt__(self,other):
        return self.grade>other.grade if self.grade!= other.grade else self.Id< other.Id

    def show(self):
        print(self.Id,self.grade)

        

        


n,m=map(int,input().split())
f=[]

for i in range(n):
    a,b=map(int,input().split())
   
    
    f.append(Score(a,b))
num=int(m*1.5)

f.sort()
line=f[num-1].grade
g=[]

for i in range(n):
    if(f[i].grade>=line):
        g.append(f[i])

print(line,len(g))
for i in range(len(g)):
    print(g[i].Id,g[i].grade)
