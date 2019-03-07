
alist=list(map(int,input().split()))
blist=list(map(int,input().split()))
alist.extend(blist)
blist=list(set(alist))
blist.sort()
print(*blist,sep=',')
'''
输入两个列表alist和blist，要求列表中的每个元素都为正整数且不超过10； 
合并alist和blist，并将重复的元素去掉后输出一个新的列表clist。 
可以使用以下实现列表alist的输入： 
alist=list(map(int,input().split())) 
同时为保证输出结果一致，请将集合内元素排序之后再输出。 


输入
共两行，每一行都用来输入列表中的元素值，以空格隔开。

输出
共一行，将合并排序后的列表数据输出。数据之间用逗号分隔。'''