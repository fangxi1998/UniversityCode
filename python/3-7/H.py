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
#�Ƚ���ʼ�����ź���  ���������ݴ浽num1 ż�����ݴ浽num2 num1 ׷��num2 ���num1 ����

'''

��Ŀ����
 ����n(<1000)��������n�������������������������������ǰ��ż���ں���������n(=10)������:10 9 8 7 6 5 4 3 2 1 ���������1 3 5 7 9 2 4 6 8 10��
�������н�����£�

10

3 12 7 65 8 4 17 25 36 50

3 7 17 25 65 4 8 12 36 50


����
�������У���һ���������ݵĸ���n���ڶ�������n��������֮���ÿո�ָ��� 


���
������������������ݣ�������ǰ��ż���ں���֮���ÿո�ָ���


'''