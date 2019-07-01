class Score:
    def __init__(self,name,d1,d2,d3):
        self.name=name
        self.d1=d1
        self.d2=d2
        self.d3=d3
        self.aver=d1+d2+d3
		
    
    def __lt__(self,other):
        if self.aver==other.aver:
            return self.d1>other.d1 if self.d1!=other.d1 else self.d2>other.d2
        else:
            return self.aver>other.aver
    def show(self):
        print(self.name,self.d1,self.d2,self.d3)
		

e=[]

while True:
    n=input()
    b=n.strip()
    if b=='':
        break
    else:
        a,b,c,d=map(str,n.split())
        e.append(Score(a,int(b),int(c),int(d)))
    

e.sort()
for b in e:
    b.show()
