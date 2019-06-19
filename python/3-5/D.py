import math
a = eval(input())
b = eval(input())
c = eval(input())
d=(a*a+b*b-c*c)/(a*b*2)
print(round(math.acos(d)*180/math.pi,1))