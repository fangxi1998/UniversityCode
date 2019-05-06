class person1:
    
    
    def __init__(self,Num,Name,a,b,c):
        self.Name=Name
        self.Num=Num
        self.a=a
        self.b=b
        self.c=c
        
        
       
        
    
   


f=[]
n=int(input())

for i in range(n):
    a,b,c,d,e=map(str,input().split())
    c=int(c)
    d=int(d)
    e=int(e)
    
    f.append(person1(a,b,c,d,e))
    

sum1=((f[0].a+f[0].b+f[0].c)/3)
for i in range(0,n):
    if(sum1<((f[i].a+f[i].b+f[i].c)/3)):
        sum1=(f[i].a+f[i].b+f[i].c)/3
  
   

            
      


for i in range(n):
    if(sum1==((f[i].a+f[i].b+f[i].c)/3)):
        print('{} {} {:.2f}'.format(f[i].Num,f[i].Name,sum1))
        break