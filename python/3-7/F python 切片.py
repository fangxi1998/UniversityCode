n,m,k=map(int,input().split())
a=[]
a[0:n]=map(int,input().split())

a1=a[0:m-1]
a2=a[m-1:m+k-1]
a3=a[m+k-1:]
a4=list(reversed(a2))

a1.extend(a4)
a1.extend(a3)
print(*a1,sep=' ')



#核心方法 python序列的切片操作 以及 reversed 函数的应用


'''有一个长度为n数组，需要将数组中从指定位置m开始的k个元素倒放在原来的数组中。


输入
第一行输入n，m,k (1<=n<=50)。

 第二行输入数组中的n个数。

m代表元素的实际位置而不是在数组中的下标值。


输出
输出倒置后的数组。

'''