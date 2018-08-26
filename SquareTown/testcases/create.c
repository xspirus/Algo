#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	char* filename = "input16.txt"; //file name
	int length = 2000000; //number of houses

	FILE *myFile;
    myFile = fopen(filename, "w+");
    if (myFile == NULL)
	{
    	printf("Error opening file!\n");
    	exit(1);
	}

    fprintf(myFile,"%d\n",length);

    time_t t;
    srand((unsigned) time(&t));

    int temp,i;
	if(RAND_MAX<=32767)
	{
    	//rand returns numbers between [0,32767]
    	//rand * rand returns [0,1073676289]
    	//we want [0,10^7] so rand^2 mod 10^7
    	for (i=0; i<length; i++)
		{
    		temp=(rand()*rand())%10000000;
    		fprintf(myFile,"%d ",temp);

    		temp=(rand()*rand())%10000000;
    		fprintf(myFile,"%d\n",temp);
		}
	}
	else {
		//rand returns numbers between [0,2147483647]
    	//we want [0,10^7] so rand mod 10^7
		for (i=0; i<length; i++)
		{
		    temp=rand()%10000000;
    		fprintf(myFile,"%d ",temp);

    		temp=rand()%10000000;
    		fprintf(myFile,"%d\n",temp);
		}
	}
	fclose(myFile);
	return 0;
}
