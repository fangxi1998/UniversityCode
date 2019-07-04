a=[]
for i in range(5):
    a.append(input())
flag=0

for i in a:
    leng=len(i)
    maxg=int(max(i))
    if leng==maxg:
        for j in range(1,maxg+1):
            if str(j) not in i:
                break
        else:
            flag=1
            print(i)

if not flag:
    print("not found")