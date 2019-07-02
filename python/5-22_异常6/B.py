
letter=[chr(x) for x in range(ord('a'), ord('z') + 1)]

while True:
    num=0
   
    b=input().strip()
    if b=='':
       
        break
    else:
        
        b=b.lower()
       
        for i in b:
            if i in letter:
                num=num+(letter.index(i)+1)
    print(num)
    