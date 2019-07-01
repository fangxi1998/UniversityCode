import re  
tmp = input()  
while(tmp != ''):  
    if not re.search(u'^[_a-zA-Z0-9]+$',tmp):  
        print ("False")  
    elif not re.search(u'^[_a-zA-Z]+$',tmp[0]):  
        print ("False")  
    else:  
        print ("True")  
    tmp = input()