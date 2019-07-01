n = int(input())
 
a1 = 2
b1= 1

s = 0
 
for i in range(1,n+1):
    a = a1
    b = b1
    
    s += (a/b)
   
    
    a1= a+b
    b1 = a
    


print('%.2f'%s)  