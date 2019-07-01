def  IsPrime(x):
    
    if x==1:
        return 0
    if x ==2:
        return 1
    
    for i in range(2,x):
        if x%i==0:
            return 0
    return 1

def prime(n):
    prime_list=[]
    for i in range(2,n):
        if IsPrime(i):
            prime_list.append(i)
    prime_list.sort()
    return prime_list

def bi_search(prime_list,num_tofind):
    index=[]
    n=len(prime_list)
    for i in num_tofind:
        if i in prime_list:
            index.append(prime_list.index(i))
        else:
            index.append(-1)
    return index


num_tofind=[]
max=int(input())
while True:
    try:
        s=int(input())
        
    except Exception:
        break
    else:
        num_tofind.append(s)
prime_list=prime(max)
index=bi_search(prime_list,num_tofind)
for i in index:
    print(i)