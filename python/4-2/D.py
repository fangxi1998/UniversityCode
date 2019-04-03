sr1 = "abcdefghijklmnopqrstuvwxyz"
sr=sr1+sr1
in_str = input("")
out_str = ""
for j in in_str:
    if j == " ":
        out_str = out_str + " "
        continue
    i = sr.find(j)
    
    out_str = out_str + sr[i+3]
print(out_str)