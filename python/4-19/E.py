def su(n):
    
    if n==1 or n==2 or n==3:
        return 1
   
    else:
        return su(n-1)+su(n-3)
n=int(input())
print(su(n))
