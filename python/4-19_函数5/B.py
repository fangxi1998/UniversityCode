def leap(n):
    if(n%4==0 and n%100!=0) or n%400==0:
        return True
    else:
        return False

n=int(input())
n1=int(input())
days=0


for i in range(1800,n):
    for month in range(1,13):
        
        if month in [1,3,5,7,8,10,12]:
            days+=31
        elif month in [4,6,9,11]:
            days+=30
        elif month ==2 and leap(i):
            days+=29
        else:
            days+=28
for i in range(1,n1+1):
    if i in [1,3,5,7,8,10,12]:
        days+=31
    elif i in [4,6,9,11]:
        days+=30
    elif i ==2 and leap(n):
        days+=29
    else:
        days+=28
print((days+2)%7)