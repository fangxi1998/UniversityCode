n=int(input())
st1=[]
for k in range(n):
    st1.append(int(input()))




sum1=0
sum2=0
sum3=0
sum4=0
t=0

for v in range(n):
    t=0
    st=list(str(st1[v]))
    while True:
    
        for j in range(4):
            sum4=sum4+int(st[j])*10**(3-j)
        b=sorted(st)
        
        c=list(reversed(b))
          
        for i in range(4):
            sum1=sum1+int(b[i])*10**(3-i)
    
            sum2=sum2+int(c[i])*10**(3-i)
            sum3=sum2-sum1
        
    
        t=t+1
        if sum4==sum3:
           
            break
        sum1=0
        sum2=0
    
        sum4=0
        st=list(str(sum3))
    sum3=0
    print(t)
