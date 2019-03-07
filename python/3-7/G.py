n=int(input())
num=[]
num[0:n]=input().split()



print(*(sorted(num)))
#调用python提供的sorted()函数实现对数组的排序 默认为升序
'''

题目描述
对包含n 个整数的数组由小到大排序输出

输入
输入数组个数n

输入n个整数


输出
排序后的n个整数
'''