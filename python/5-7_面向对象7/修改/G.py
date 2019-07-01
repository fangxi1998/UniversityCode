class Score:
    def __init__(self,num,na,x,y,z):
        self.num=num
        self.na=na
        self.x=x 
        self.y=y
        self.z=z
        self.aver=(( x+ y+ z)/3)
    

    def __lt__(self,other):
        return self.aver>other.aver

    def show(self):
        print('{} {} {:.2f}'.format(self.num,self.na,self.aver))
n=int(input())
a=[]
for i in range(n):
    c,d,e,f,g=map(str,input().split())
    e=int(e)
    f=int(f)
    g=int(g)
    a.append(Score(c,d,e,f,g))
    
   
a.sort()
a[0].show()