sr1 = "abcdefghijklmnopqrstuvwxyz"

in_str = input()
out_str = ""
for j in in_str:
    if j == " ":
        out_str = out_str + " "
        continue
    i = sr1.find(j)
    
    out_str = out_str + sr1[(i+3)%26]
print(out_str)
