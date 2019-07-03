n=int(input())

for i in range(n):
    count1=0
    shu = int(input())

    
    
    while True:
        #print(shu)
        ls1=list(map(int,str(shu)))
        ls1.sort()
        maxshu=ls1[3]*1000+ls1[2]*100+ls1[1]*10+ls1[0]
        minshu=ls1[0]*1000+ls1[1]*100+ls1[2]*10+ls1[3]

        shu1 = maxshu-minshu
        count1+=1
        if shu==shu1:
            break
       

        shu=shu1
    print(count1)

