class Score:
	def __init__(self,id,age):
		self.id=id
		self.age=age            
    
	def __lt__(self,other):
		if self.age>=60 or other.age>=60:
			return self.age>other.age

	def show(self):
		print(self.id)
		
n=int(input())
a=[]

for i in range(n):
    c,d=map(str,input().split())
    a.append(Score(c,int(d)))

a.sort()
for b in a:
    b.show()
