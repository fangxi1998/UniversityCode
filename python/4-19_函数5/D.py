def fac(n):
    num=[]
    for a in range(2,n):
        b=0
        for i in range(1,a):
            if a%i==0:
                b+=i
        r=0
        for j in range(1,b):
            if b%j==0:
                r+=j

        if r==a and a<b:
            num.append(str(a)+'-'+str(b))
    return num
n=int(input())
for i in fac(n):
    print(i)