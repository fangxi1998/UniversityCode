st=[]
a=int(input())
st.append(a)
e=0
for i in range(4):
    
    a=int(input())
    st.append(a)

for j in st:
    b=str(j)
    max1=int(max(b))
    if len(b)==max1:
        for c in range(1,max1+1):
            d=str(c)
            if d in b:
                continue
            else:
                break
    
        
        else:
            e=e+1
            print(b)
if e==0:
    print("not found")