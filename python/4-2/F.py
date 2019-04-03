n=eval(input())
List=[]
i=input()
while i !='':
    List.append(eval(i))
    i=input()
sum_up=0
for i in List:
    if i>=n:
        sum_up+=1
if len(List)==0:
    print("100.00%")
else:
    x=100*(sum_up/len(List))
    print("{:.2f}%".format(x))