class Score:
    def __init__(self,na,x):
        self.na=na
        self.x=x             
    

    def __lt__(self,other):
        return self.x>=other.x

    def show(self):
        print('{} {}'.format(self.na,self.x))
n=int(input())
a=[]
for i in range(n):
    c,d=map(str,input().split())
    a.append(Score(c,d))
    
   
a.sort()
for b in a:
    b.show()