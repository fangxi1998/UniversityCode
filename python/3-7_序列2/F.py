
n,m,k=list(map(int,input().split()))


num=[]
num[0:n]=list(map(int,input().split()))
t=0
y=0

for i in range(m,m+k):
    for j  in range(m,m+k-t-1):
        y=num[j-1]
        num[j-1]=num[j]
        num[j]=y
    t=t+1
print(*num)


#核心方法是 将指定的每一个元素通过与旁边相邻的元素互换 以达到指定长度元素倒置的效果 类似于冒泡


'''有一个长度为n数组，需要将数组中从指定位置m开始的k个元素倒放在原来的数组中。


输入
第一行输入n，m,k (1<=n<=50)。

 第二行输入数组中的n个数。

m代表元素的实际位置而不是在数组中的下标值。


输出
输出倒置后的数组。

'''