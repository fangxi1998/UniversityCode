class Score:
    def __init__(self,na,x,num):
        self.na=na
        self.x=x             
        self.num=num

    def __lt__(self,other):
        return self.x<other.x
    def show(self):
        print(self.na,self.x,self.num)
n=int(input())
a=[]
for i in range(n):
    c,d,e=map(str,input().split())

    a.append(Score(c,d,e))
    
   
a.sort()
for y in a:
    y.show()