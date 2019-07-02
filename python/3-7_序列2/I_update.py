n=int(input())
num=[]
num[0:n]=list(map(int,input().split()))
grade=[x*0 for x in range(5)]
for i in range(0,n):
    if num[i]>=90:
        grade[0]=grade[0]+1
    elif num[i]>=80:
         grade[1]=grade[1]+1
    elif num[i]>=70:
         grade[2]=grade[2]+1
    elif num[i]>=60:
         grade[3]=grade[3]+1
    
    else:
         grade[4]=grade[4]+1
print(*grade)