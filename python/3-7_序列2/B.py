alist=list(map(int,input().split()))



a={'1':alist[:len(alist)//2],'2':alist[len(alist)//2:]}
print(a)
