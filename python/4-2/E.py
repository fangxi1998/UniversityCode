s = input()
a = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
n = a.index(s[-1])-a.index('E')

for t in s:
	print(a[(a.index(t) - n)], end='')