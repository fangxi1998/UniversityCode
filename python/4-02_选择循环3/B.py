TempStr=input()
if TempStr[0] in ['R','r']:
    C=(eval(TempStr[3:]))/6.78
    print("USD{:.2f}".format(C))
elif TempStr[0] in ['U','u']:
     F=eval(TempStr[3:])*6.78
     print("RMB{:.2f}".format(F))