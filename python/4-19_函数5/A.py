def  IsPrime(x):
    
    if x==1:
        return 0
    if x ==2:
        return 1
    
    for i in range(2,x):
        if x%i==0:
            return 0
    return 1

def div(num):
    snum=str(num)
    length=len(snum)
    num_type=[]
    for i in range(length):
        number=int(snum[i:]+snum[:i])
        num_type.append(number)
    return num_type

n=int(input())
count=0
for i in range(2,n):
    flag=1
    for num in div(i):
        if not(IsPrime(num)):
            flag=0
            break
    if flag:
        count+=1
print(count)
