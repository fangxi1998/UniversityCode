class Score:
    def __init__(self,na,x):
        self.na=na
        self.x=x             
    

    def __lt__(self,other):
        return self.x>other.x
    def show(self):
        print('{:.2f},{}'.format(self.x,self.na))
n=int(input())
a=[]
for i in range(n):
    c=input()
    d=float(input())
    a.append(Score(c,d))
    
   
a.sort()
a[0].show()
a[-1].show()