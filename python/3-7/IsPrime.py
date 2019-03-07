
def  IsPrime(x):
    
    if x==1:
        return 0
    if x ==2:
        return 1
    
    for i in range(2,x):
        if x%i==0:
            return 0
    return 1

sum=0
a = int(input())
for i in range(1,a+1):
    
    if(IsPrime(i)==1):
        
        sum=(sum+int(i))
print(sum)


'''从键盘任意输入一个整数n，编程计算并输出1~n之间的所有素数之和。判断这个数是否是素数用函数实现。
   函数原型：int IsPrime(int x);

   函数功能：判断x是否是素数，若函数返回0，则表示不是素数，若返回1，则代表是素数



输入
输入整数n 。


输出
输出素数的和。'''