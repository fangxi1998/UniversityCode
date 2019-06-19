class point:
    def __init__(self,x,y):
        self.x=x
        self.y=y
    def show(self):
        print(self.x,self.y)
n=int(input())
a=[]
for i in range(n):
    c,d=map(str,input().split())
    a.append(point(c,d))
   
for i in range(n):
    a[i].show()
