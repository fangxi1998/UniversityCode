import xlwt
class student:
    def __init__(self,num,name,d1,d2,d3):
        self.num=num
        self.name=name
        self.d1=d1
        self.d2=d2
        self.d3=d3




n=int(input())
stls=[]
for i in range(n):
    ls=input().split()
    
    stls.append(student(ls[0],ls[1],int(ls[2]),int(ls[3]),int(ls[4])))

book = xlwt.Workbook()
sheet1=book.add_sheet("我的表单")
a1=xlwt.Alignment()
a1.horz=xlwt.Alignment.HORZ_CENTER
a1.vert=xlwt.Alignment.VERT_CENTER
borders=xlwt.Borders()
borders.bottom=xlwt.Borders.THICK
style=xlwt.XFStyle()
style.alignment=a1
style.borders=borders

st=['no','name','math','english','chinese','sum']

row =sheet1.row(0)
for i in range(len(st)):
    row.write(i,st[i],style=style)
                

s='=SUM(C'
s1=':E'


for j in range(1,n+1):
    row=sheet1.row(j)
    data = [stls[j-1].num,stls[j-1].name,stls[j-1].d1,stls[j-1].d2,stls[j-1].d3]
    for k in range(6):
        if k==5:
            s2=s+str(j+1)+s1+str(j+1)+')'
            row.write(k,s2,style=style)
        else:
            row.write(k,data[k])

    
book.save(r'E:\xlwttest.xls')
 '''从键盘输入n个学生的信息：学号 姓名 数学 英语语文

将这学生信息写入EXEL表中，增加表的标头 

学号 姓名 数学 英语语文总分

再在下一行分别输入相应信息，每行最后单元格用写入公式 =sum(C2:E2),每行的行号随行发生变化

输入 样例：

5

201801 lifang 90 87 98

201802 fang 100 78 89

201803 lili 78 100 89

201804 liuxiao 89 96 67

201805 zhao 78 100 93'''
