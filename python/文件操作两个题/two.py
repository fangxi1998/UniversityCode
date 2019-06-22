import re

class student:
    def __init__(self,num,name,d1,d2,d3,aver):
        self.num=num
        self.name=name
        self.d1=d1
        
        self.d2=d2
        self.d3=d3
        
        self.aver=aver
        
    def __lt__(self,other):
        return self.aver>other.aver


    def __str__(self):
        return"%s\t%s\t%s\t%s\t%s\t%s"%(self.num,self.name,self.d1,self.d2,self.d3,self.aver)
    
def writetofile(file,stls):
    with open(file,'w') as fp:
        for st in stls:
            data = [st.num,st.name,st.d1,st.d2,st.d3,st.aver]
            data=','.join(data)
            fp.write(data)
            fp.write('\n')

def readfromfile(file):
    readls =[]
    with open(file,'r') as fp:
        data=fp.readlines()

        for line in data:
            ls1=re.split('[,\s]',line)
            readls.append(student(ls1[0],ls1[1],ls1[2],ls1[3],ls1[4],ls1[5]))
    return readls
        

n=int(input())
stls=[]
for i in range(n):
    ls=input().split()
    aver=int(ls[2])+int(ls[3])+int(ls[4])
    stls.append(student(ls[0],ls[1],ls[2],ls[3],ls[4],str(aver)))
stls.sort()
writetofile(r'E:\student.txt',stls)
stls1=readfromfile(r'E:\student.txt')
for st in stls1:
    print(st)

