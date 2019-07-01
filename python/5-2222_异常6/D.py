def countchar(n):
    ini=[i*0 for i in range(26)]
    letter=[chr(x) for x in range(ord('a'), ord('z') + 1)]
    n=n.lower()
    for i in n:
        if i in letter:
            ini[letter.index(i)]+=1
    return ini


n=input()

for i in countchar(n):
    print(i,end=' ')
