#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


void cacheSize(int numOfTrys, int* switchSpot,int* count){
	//forward declaration of variables
	int i = 0; // for iteration
	int j = 0;
	struct timespec startTime, endTime; //time structs for start & end times
	int* pow2; // pointer to array of powers of 2
	int pow2Elements = 25; // elements in power of 2 array
	int* array = 0; // array for accessing cache
	int arraySize = 1000000; // size of array
	long* differences =0; // array of difference values
	int temporary = 0;
	int step = 1024; // values for stepping through array.

	//create and populate an array of powers of 2
	pow2 = (int*)(calloc(pow2Elements,sizeof(int)));
	for (i = 0; i < pow2Elements; i++){
		pow2[i] = pow(2,i);	
	}//end for

	//allocate array in memory
	array = (int*)(malloc(arraySize * sizeof(int)));
	//allocate differences in memory
	differences = (long*)(calloc(arraySize, sizeof(long)));
	
	
	for(i = 0; i < pow2Elements; i++){
		clock_gettime(CLOCK_MONOTONIC,&startTime); //get the starting time
		for (j = 0; j < arraySize; j++){
			temporary = array[i*step % pow2[i]];
		
		}//end for
		clock_gettime(CLOCK_MONOTONIC,&endTime); //get the ending time 
		//obtain the difference and store it in an array
		differences[i] = endTime.tv_nsec - startTime.tv_nsec; 
		//printf("Time is: %ld at 2^%d = %d\n",differences[i],i, pow2[i]);
		//printf("Time is: %ld at 2^%d\n",differences[i],i);
	}//end for 
	for( i=1; i < pow2Elements; i ++){
		if( (float)i > ((float)pow2Elements * .1) && (float)i < ((float)pow2Elements *.9)){
			if((differences[i] - differences[i-1]) > (8* differences[i-1] - differences[i-2])){
			*switchSpot = *switchSpot + i;
			*count = *count + 1;
			}
		}
	}	
		

	
	//free any allocated memory
	free(pow2);
	free(array);
	free(differences);

	
}//end cacheSize

int main(int argc, char** argv){
	int avg = 0;
	int* count = malloc(sizeof(int));
	int* switchSpot = malloc(sizeof(int));
	for(int i = 0; i < 1000; i++){
	cacheSize(30,switchSpot,count);
	}
	

	avg = (*switchSpot) / (*count);
	printf("Cache Size = 2^%d or %d bytes\n",avg,(int)pow(2,avg));
	
	free(count);
	free(switchSpot);
	return 0;

}




