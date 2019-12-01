#include <stdio.h>
#include <stdlib.h>

int* LinInt(int, int, int, int);
int mypow(int,int);
int modM(int,int,int);
int modD(int, int, int);
int invMod(int,int);

int main()
{
	int key, pr;
	int *shares = NULL;
	int numShares;
	int thresh;
	int i,j;
	int seed;
	FILE *fptr;

	fptr = fopen("data.txt","w");

	printf("Please enter seed for this encryption: ");
	scanf("%d", &seed);
	srand(seed);
	printf("Please enter the threshhold number of shares required: ");
	scanf("%d", &thresh);
	printf("Please enter the number of shares needed: ");
	scanf("%d", &numShares);
	while(numShares<thresh){
		printf("numShares must be greater than or equal to thresh. Please enter appropriate value for numShares: ");
		scanf("%d",&numShares);
	}

	printf("Please enter your key: ");
	scanf("%d", &key);

	printf("Please enter the prime: ");
	scanf("%d", &pr);

	while(pr <= key)
	{
	printf("Please enter the prime: ");
	scanf("%d", &pr);
	}

	shares = LinInt(key,numShares,thresh, pr);

	for(i=0;i<numShares;i++){
//		printf("\n");
		fprintf(fptr, "(%d, %d)\n", *(shares + 2*i), modM(*(shares + 2*i + 1),1,pr));
	}

	printf("\nFile Written.\n");

	return 0;
}

int* LinInt(int key, int numShares, int thresh, int pr){

	int *coeff = (int*)(calloc(thresh, sizeof(int)));
	int *sp = (int*)(calloc(numShares*2,sizeof(int)));
	int i = 0,j;
	int temp, tempsum = 0;
	int flag = 0;

	//This part selects the required amount of random ints for the x values
	while(i<numShares){
		temp = rand()%1000 + 1;
		for(j=0 ; j<i ; j++){
			if( *(sp + 2*j) == temp){
				flag = 1;
				break;
			}
			else
				continue;
		}
		if (flag){
			flag = 0;
			continue;
		}
		else{
			*(sp + 2*i) = temp;
			i++;
		}
	}


	//This part selects random coefficients for the polynomial
	for(i=0;i<thresh-1;i++){
		*(coeff + i + 1) =mypow(-1,i) * rand()%100;
	}

	*coeff = key;

	for(i=0;i<numShares;i++){
		tempsum = 0;
		for(j=0;j<thresh;j++)
			tempsum += modM(coeff[j],mypow(sp[2*i],j),pr);
		sp[2*i + 1] = tempsum % pr;
	}

	free(coeff);
	return sp;
}

int mypow(int base, int pow){

	int i;
	int prod = 1;

	for(i=0;i<pow;i++)
		prod*=base;

	return prod;
}

int modM(int x, int y, int pr){

	int i = (x*y)%pr;

	while(i<0)
		i+=pr;
	return i;
}

int modD(int x, int y, int pr){
	return (x * invMod(y,pr))%pr;
}

int invMod(int x, int pr){

	int i = 0;

	while(x<0)
		x += pr;

	while(x>pr)
		x -= pr;

	while ((x*i)%pr != 1)
		i++;

	return i;
}
