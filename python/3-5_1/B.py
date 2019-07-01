import math
a,b,c=map(int,input().split())

print(math.sqrt(a*a+b*b-2*a*b*math.cos(c*math.pi/180)))