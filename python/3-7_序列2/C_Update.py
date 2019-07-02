alist=list(map(int,input().split()))

print(*sorted(alist,key=lambda x:-x if x<0 else x),sep=',')