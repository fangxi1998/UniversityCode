
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


'''�Ӽ�����������һ������n����̼��㲢���1~n֮�����������֮�͡��ж�������Ƿ��������ú���ʵ�֡�
   ����ԭ�ͣ�int IsPrime(int x);

   �������ܣ��ж�x�Ƿ�������������������0�����ʾ����������������1�������������



����
��������n ��


���
��������ĺ͡�'''