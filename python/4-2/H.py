a = list(input())
sum1=0
b=0
for i in range(2000):
    for j in a:
        sum1=sum1+int(j)*int(j)
    if sum1==1:
        print("true")
        b=1
        break
    a=list(str(sum1))
    sum1=0
if b==0:
    print("false")