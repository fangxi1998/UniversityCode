
alist=list(map(int,input().split()))
blist=list(map(int,input().split()))
alist.extend(blist)
blist=list(set(alist))
blist.sort()
print(*blist,sep=',')
'''
���������б�alist��blist��Ҫ���б��е�ÿ��Ԫ�ض�Ϊ�������Ҳ�����10�� 
�ϲ�alist��blist�������ظ���Ԫ��ȥ�������һ���µ��б�clist�� 
����ʹ������ʵ���б�alist�����룺 
alist=list(map(int,input().split())) 
ͬʱΪ��֤������һ�£��뽫������Ԫ������֮��������� 


����
�����У�ÿһ�ж����������б��е�Ԫ��ֵ���Կո������

���
��һ�У����ϲ��������б��������������֮���ö��ŷָ���'''