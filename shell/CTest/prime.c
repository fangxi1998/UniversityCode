#include<stdio.h>
int isprime(int num){
int i;	
if(num==1)
	return 0;
for(i=2;i<num;i++){
	
	if(num%i==0)
		return 0;
}
return 1;



} 
int main(void){
int i ;
for(i=1;i<=100;i++){
if(isprime(i))
	printf(" %d",i);

}
return 0;




}
