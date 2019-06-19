nu=[x-64 for x in range(ord('A'), ord('Z') + 1)]
letter=[chr(x) for x in range(ord('a'), ord('z') + 1)]

while True:
    num=0
    n=input()
    b=n.strip()
    if b=='':
        break
    else:
        
        b=b.lower()
       
        for i in b:
            if i in letter:
                num=num+nu[letter.index(i)]
    print(num)
    num=0
    