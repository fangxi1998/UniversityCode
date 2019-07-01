def Pig_Latin(text):
    l=text.lower().split()
    p=[]
    for s in l:
        if s[0] in 'aeiou':
            s=s+'hay'
        elif s[0:2]=='qu':
            s=s[2:]+'quay'
        else:


            
            for n in range(1,len(s)):
                if s[n] in 'aeiouy':
                    s=s[n:]+s[0:n]
                    break
            s=s+'ay'
        p.append(s)
    return ' '.join(p)



n=input()
s=Pig_Latin(n)
print(s)