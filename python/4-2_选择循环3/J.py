w=int(input())
su=0.00
e=0
st1=[]
stu=[]

for i in range(w):
    
    
    stu.append(list(input().split()))
    
    for j in range(1,4):
        if j==3:
            e=eval(stu[i][3])
            su=su-e
            break
        su=su+eval(stu[i][j])
        
    st1.append(stu[i][0])
    st1.append(float(su))
    su=0.0
    
for c in range(0,w*2,2):
    print(st1[c],end=' ')
    print("{:.2f}".format(st1[c+1]),end='\n')
   