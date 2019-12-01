#include <stdio.h>
#include <stdlib.h>
//#include "encrypt.c"

long int decoder(long int*, int, long int pr);
long int modM(long int,long int,long int);
long int modD(long int,long int, long int);
long int invMod(long int,long int);
long int mypow(int,int);

int main(){

	long int *myarr = NULL;
	int thresh;
	long int key;
	int i,j;
	long int pr;
	FILE *fptr;

//	printf("int is %lu, long int is %lu\n", sizeof(int), sizeof(long int));

	fptr = fopen("data.txt","r");

	printf("Please enter threshold value: ");
	scanf("%d", &thresh);
	myarr = (long int*)(calloc(2*thresh,sizeof(long int)));

	printf("Please enter the mod prime: ");
	scanf("%ld", &pr);

	for(i=0;i<1;i++){
//		printf("Please enter x of pair %d: ", i+1);
		fscanf(fptr,"(%ld, %ld)\n", myarr+2*i, myarr + 2*i + 1);
//		printf("Please enter y of pair %d: ", i+1);
//		fscanf(fptr,"%ld",myarr+1+2*i);
	}

	//scanf("%d %d", &thresh, &i);
	//printf("%d", modD(thresh,i,pr));

//	key = decoder(myarr,thresh,pr);

	key = invMod(thresh,pr);

	printf("\nDecryption complete!\n");
	printf("Your key is %ld\n", key);

	return 0;
}

long int decoder(long int *sp,int thresh, long int pr){

	long int key = 0;
	int i,j;
	long int temp_prod;

	for(i=0;i<thresh;i++){
		temp_prod = 1;
		for(j=0;j<thresh;j++){
			if(i!=j){
				temp_prod *= modD(*(sp + 2*j),(*(sp + 2*i)-*(sp + 2*j)),pr);
				temp_prod = temp_prod%pr;
			}
			else
				continue;
		}
		key += (temp_prod * (*(sp + 2*i + 1)))*mypow(-1,thresh-1);
		key = key%pr;
	}

	//printf("The key at debug point is %ld\n",key);

	return modM(key,1,pr);
}

long int modM(long int x,long int y ,long int pr)
{
	long int res = x*y;

	while(res<0)
		res += pr;

	return res%pr;
}

long int modD(long int x,long int y, long int pr)
{
	return (x*invMod(y,pr))%pr;
}

long int invMod(long int x, long int pr)
{
	long int u,v,x1,x2,q,r,a;

	u = x;
	v = pr;
	x1 = 1;
	x2 = 0;

	while(u!=1){
		q = v/u;
		r = v-q*u;
		a = x2-q*x1;
		v = u;
		u = r;
		x2 = x1;
		x1 = a;
	}

	printf("I ran\n");

	return (x1%pr);
}
long int mypow(int base, int exp)
{
	int i,prod = 1;

	for(i=0;i<exp;i++)
		prod *= base;

	return (long int)prod;
}
