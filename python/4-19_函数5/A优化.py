def isprime(n):
    if n ==1:
        return 0
    if n==2:
        return 1
    for i in range(2,n):
        if not n%i:
            return 0
    return 1

def div(n):
    snum=str(n)
    leng=len(snum)
    a=[]
    for i in range(leng):
        number=int(snum[i:]+snum[:i])
        a.append(number)
    return a


n=int(input())
count=0
for i in range(2,n):
    
    for j in div(i):
        if not isprime(j):
            break

    else:
        count+=1


print(count)