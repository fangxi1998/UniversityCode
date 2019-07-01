n = input().lower()
s = ''
for i in n:
    if i.isdigit() or i.isalpha():
        s =s+i

if s[::-1]==s:
    print("True")
else:
    print("False")