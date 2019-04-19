def fib(n):
    sum=0
    a,b=1,1
    while a<=n:
        if a%2==0:
            sum+=a
        a,b=b,a+b
        
    return sum

n=int(input())
print(fib(n))