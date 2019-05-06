class person:
    
    
    def __init__(self,Name,grade):
        self.Name=Name
        self.grade=grade
       
        
    
   


a=[]
n=int(input())

for i in range(n):
    b,c=map(str,input().split())
    a.append(person(b,c))
    

        
for i in range(0,n):
    
    for j in range(i+1,n):
        if(a[j].grade>a[i].grade):
            s=a[i].grade
            a[i].grade=a[j].grade
            a[j].grade=s

            c=a[i].Name
            a[i].Name=a[j].Name
            a[j].Name=c
        if (a[j].grade==a[i].grade and a[j].Name<a[i].Name):



            s=a[i].grade
            a[i].grade=a[j].grade
            a[j].grade=s

            c=a[i].Name
            a[i].Name=a[j].Name
            a[j].Name=c


            
      


for i in range(n):
    print(a[i].Name,a[i].grade)