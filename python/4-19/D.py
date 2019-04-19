def fac(x):
    for a in range(2,x):
        b = 0
        for i in range(1,a):
            if a % i == 0:
                b += i

                #b是a这个数的因子之和
                #如果b的因子之和等于a
                
                #b跟a就是一个亲密数对
                
                
        r = 0       
        for j in range(1,b):
            if b % j == 0:
                r += j
                '''r是b这个数的因子之和
                如果这两个数相等并且a<b'''
                
        '''设置a<b 防止出现这种情况
            220-284
            284-220

            '''
        if r == a and a<b:
            print("{}-{}".format(a,b))
     
      
           

n = int(input())
fac(n)

