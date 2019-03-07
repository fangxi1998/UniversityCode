n=int(input())
num=[]
num[0:n]=list(map(int,input().split()))
num=sorted(num)
num1=[]
num2=[]

for i in range(0,n):
    if num[i]%2==1:
        num1.append(num[i])
    else:
        num2.append(num[i])
num1.extend(num2)



print(*num1)
#先将初始数据排好序  把奇数数据存到num1 偶数数据存到num2 num1 追加num2 输出num1 即可

'''

题目描述
 输入n(<1000)个数，将n个整数按升序排列输出，并且奇数在前，偶数在后。如果输入的n(=10)个数是:10 9 8 7 6 5 4 3 2 1 ，则输出：1 3 5 7 9 2 4 6 8 10。
程序运行结果如下：

10

3 12 7 65 8 4 17 25 36 50

3 7 17 25 65 4 8 12 36 50


输入
输入两行：第一行输入数据的个数n；第二行输入n个数，数之间用空格分隔。 


输出
输出按升序排序后的数据，奇数在前，偶数在后，数之间用空格分隔。


'''