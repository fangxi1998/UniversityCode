n=int(input())
num=[]
num[0:n]=list(map(int,input().split()))
a=0
b=0
c=0
d=0
e=0


for i in range(0,n):
    
    if num[i]>=90:
        a=a+1
    elif num[i]>=80:
        b=b+1
    elif num[i]>=70:
        c=c+1
    elif num[i]>=60:
        d=d+1
    
    else:
        e=e+1
print(a,b,c,d,e)