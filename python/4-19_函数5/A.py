def  IsPrime(x):
    
    if x==1:
        return 0
    if x ==2:
        return 1
    
    for i in range(2,x):
        if x%i==0:
            return 0
    return 1

#判断素数函数


def div(num):  
    Snum=str(num)  
    length=len(Snum)  
    num_type=[]  
    for i in range(length):  
        number=int(Snum[i:]+Snum[:i])
        
        
        num_type.append(number)  
    return num_type
#将数循环移位放到一个列表中


n = int(input())
count=0
for i in range(2,n):
    flag=1
    for num in div(i):
        if IsPrime(num)==0:
            flag=0
            break
    if flag:
        count+=1
print(count)
            
    

