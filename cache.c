#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


void cacheSizeCalculation(int powOf2, int* switchSpot,int* count, int timeVariation,int stepModifer){
	/*cacheSize is a function used to expirementally obtain an estimate of the size of the cache.  
	Parameters:
	powOf2: number of powers of 2 to test; wil varry depending on the program
	switchSpot: pointer to a sum of locations in which their is a significant switch in times
	count: pointer to a count of the number of significant switches
	timeVariation: factor by which times need to vary to be considered significant 
	stepModifer: modifies the step based on what values are trying to be accessed.

	*/
	//forward declaration of variables
	int i = 0; // for iteration
	int j = 0;
	struct timespec startTime, endTime; //time structs for start & end times
	int* pow2; // pointer to array of powers of 2
	int* array = 0; // array for accessing cache
	int arraySize = 1000000; // size of array
	long* differences =0; // array of difference values
	int temporary = 0;
	int step = 1024/stepModifer; // values for stepping through array.

	//create and populate an array of powers of 2
	pow2 = (int*)(calloc(powOf2,sizeof(int)));
	for (i = 0; i < powOf2; i++){
		pow2[i] = pow(2,i);	
	}//end for

	//allocate array in memory
	array = (int*)(malloc(arraySize * sizeof(int)));
	//allocate differences in memory
	differences = (long*)(calloc(arraySize, sizeof(long)));
	
	
	for(i = 0; i < powOf2; i++){
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

	//the loop adds the location of major time switches to the switchspot pointer and incriments count by 1
	// for this, a major time switch is defined as a power of 8, or 2^3
	for( i=1; i < powOf2; i ++){
		if( (float)i > ((float)powOf2 * .1) && (float)i < ((float)powOf2 *.9)){
			if((differences[i] - differences[i-1]) > (timeVariation* differences[i-1] - differences[i-2])){
			*switchSpot = *switchSpot + i;
			*count = *count + 1;
			}
		}
	}	
		

	
	//free any allocated memory
	free(pow2);
	free(array);
	free(differences);

	
}//end cacheSizeCalculation

int cacheSize(int attempts){
	/* Cache size calls the cacheSizeCalculation to calculate an average of access.  
	 It returns the exponent to raise 2 to in order to get the cache size
	 Paramaters:
	 attempts: total number of times to run cacheSizeCalculation, minimum recommendation of 500  
	*/
	int stepModifier = 1;// use the base step for cacheSizeCalculator
	int powOf2 = 30; //number of powers of two needed for testing
	int avg;
	int timeVariation = 8; // factor by which times need to vary to be considered significant
	int* count = malloc(sizeof(int));
	int* switchSpot = malloc(sizeof(int));
	for(int i = 0; i < attempts; i++){
	cacheSizeCalculation(powOf2,switchSpot,count,timeVariation, stepModifier);
	}
	

	avg = (*switchSpot) / (*count);

	
	
	free(count);
	free(switchSpot);
	return avg;

}// end cacheSize

int blockSize(int attempts){
	/* block size calls the cacheSizeCalculation to calculate an average of access.  
	 It returns the exponent to raise 2 to in order to get the cache size
	 Paramaters:
	 attempts: total number of times to run cacheSizeCalculation, minimum recommendation of 500 
	*/
	int stepModifier = 2; // use a smaller step for block sizes
	int powOf2 = 10; //powOf2: the number of powers needed for testing the 
	int timeVariation = 2;// factor by which times need to be varried to be considered significant; use a smaller for blocks
	int avg;
	int* count = malloc(sizeof(int));
	int* switchSpot = malloc(sizeof(int));
	for(int i = 0; i < attempts; i++){
	cacheSizeCalculation(powOf2,switchSpot,count, timeVariation,stepModifier);
	}
	

	avg = (*switchSpot) / (*count);

	
	
	free(count);
	free(switchSpot);
	return avg;
}//end blockSize
/*
int main(int argc, char** argv){
	int numTests = 1000;
	int cache = cacheSize(numTests);
	printf("Cache size = 2^%d or %d bits\n",cache,(int)pow(2,cache));
	int block = blockSize(numTests);
	printf("Block size = 2^%d or %d bits\n",block,(int)pow(2,block));

}
*/


int mainMemory (int cachePower,int block){
	struct timespec startTime, endTime;
	int i;
	int diff = 0;
	int size = pow(2,cachePower); //set size of array to the power of two where cache ended
	int arr[size + block];
	int temp = 0;
	
	//start timer and run i through most of size
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	for (i=0; i < (size); i = i + block){
		temp = arr[i];
	}
	clock_gettime(CLOCK_MONOTONIC,&endTime);

	//our time variable
	diff = endTime.tv_nsec - startTime.tv_nsec;
	//printf(" \nTime in Main Memory: %d nanosec\n", diff);

	return diff;
	

}//end mainMem

int main(int argc, char** argv){
	int i;
	int mainAvg = 0 ;
	int tryNum = 500; //try this power of two
	int cache = cacheSize(tryNum);
	printf("Cache Size = 2^%d or %d bytes\n",cache,(int)pow(2,cache));
	int block = blockSize(tryNum);
	printf("Block Size = 2^4%d or %d bits\n",block,(int)pow(2,block));

	//average for main mem time
	for (i=0; i < tryNum; i++){
		mainAvg = mainAvg + mainMemory(cache,pow(2,block));
	}
	mainAvg = mainAvg / tryNum;
	printf("\nTime to Main Memory is: %d \n", mainAvg);
	return 0;
}



