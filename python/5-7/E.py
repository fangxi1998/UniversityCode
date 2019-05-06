class person2:
    
    
    def __init__(self,Name,year,phone):
        self.Name=Name
        self.year=year
        self.phone=phone
       
        
        
       
        
    
   


f=[]
n=int(input())

for i in range(n):
    a,b,c=map(str,input().split())
   
    
    f.append(person2(a,b,c))

for i in range(0,n):
    
    for j in range(i+1,n):
        if(f[j].year<f[i].year):
            s=f[i]
            f[i]=f[j]
            f[j]=s
for i in range(n):
    print(f[i].Name,f[i].year,f[i].phone)