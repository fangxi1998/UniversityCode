n = int(input()) - 1                        
lst = ['X'] * (2 * n + 1)                 
for i in range(n):                          
    s = '+' * i + 'X' + '+' * (n - i - 1)   
    s = s + '+' + s[::-1]                   
    lst[i] = lst[-1 - i] = s                
lst[n] = "+" * n + 'X' + '+' * n			
for l in lst:
    print(l)