
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "cache.h"


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
	 It returns the cache size
	 Paramaters:
	 attempts: total number of times to run cacheSizeCalculation, minimum recommendation of 500  
	*/
	int stepModifier = 1;// use the base step for cacheSizeCalculator
	int powOf2 = 30; //number of powers of two needed for testing
	int avg;
	int timeVariation = 4; // factor by which times need to vary to be considered significant
	int* count = malloc(sizeof(int));
	int* switchSpot = malloc(sizeof(int));
	for(int i = 0; i < attempts; i++){
	cacheSizeCalculation(powOf2,switchSpot,count,timeVariation, stepModifier);
	}
	

	avg = (*switchSpot) / (*count);

	
	
	free(count);
	free(switchSpot);
	return pow(2,avg);

}// end cacheSize

int blockSize(int attempts){
	/* block size calls the cacheSizeCalculation to calculate an average of access.  
	 It returns the size of the block
	 Paramaters:
	 attempts: total number of times to run cacheSizeCalculation, minimum recommendation of 500 
	*/
	int stepModifier = 2; // use a smaller step for block sizes
	int powOf2 = 14; //powOf2: the number of powers needed for testing the 
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
	return pow(2,avg);
}//end blockSize

double mainMemoryCalc (int cache,int block){
/* mainMemoryCalc calucaltes the access time to main memory and returns it
 	Paramaters:
	cache: size of cache
	block: size of block

*/

	clock_t time;
	double timeTotal;
	int i;
	int size = cache; //set size of array to where cache ended
	int arr[size + block];
	int temp = 0;
	
	time = clock();
	//start timer and run i through most of size
	for (i=0; i < (size); i = i + block){
		temp = arr[i];
	}


	//our time variable
	time = clock() - time;
	timeTotal = ((double)time/CLOCKS_PER_SEC);
	//printf(" \nTime in Main Memory: %f sec\n", timeTotal);

	return timeTotal * 1000000;
	

}//end mainMem

//time to find reference in cache
double cacheMemoryCalc (int cache, int block ){
/* this function calculates the access times for the cache memory and returns it
	parameters:
	cache: size of the cache
	block: size of the lock

*/

	clock_t time;
	double timeTotal;
	int i;
	int size = cache; //set size of array to the power of two where cache ended
	int arrCache[size];
	int temp = 0;

	time = clock();
	for (i = size; i > 0; i = i - block){
		temp = arrCache[i];
	}
	
	time = clock() - time;


	timeTotal = ((double)time/CLOCKS_PER_SEC);
	//printf("\nTotal cache:  %f\nsec", timeTotal);
	return timeTotal * 1000000;
}//end cacheMemory
double cacheMemory(int cache, int tryTimes, int block){
/* cacheMemory computes the average cache access time and returns it
	Parameters:
	cache: size of cache
	tryTimes: number of times to attempt and average;
	block: size of block
*/
	int i = 0;
	double cacheAvg = 0;

	for (i=0; i < tryTimes; i++){
		cacheAvg = cacheAvg + cacheMemoryCalc(cache, block);
	}
	cacheAvg = cacheAvg / (double)tryTimes;
	return cacheAvg;

}//end cacheMemory

double mainMemory(int cache, int tryTimes, int block){
/* mainMemory computes the average cache access time and returns it
	Parameters:
	cache: size of cache
	tryTimes: number of times to attempt and average;
	block: size of block
*/
	int i = 0;
	double mainAvg = 0;
	for (i=0; i < tryTimes; i++){
		mainAvg = mainAvg + mainMemoryCalc(cache,block);
	}
	mainAvg = mainAvg/(double)tryTimes;
	return mainAvg;
}//end main memory

int main(int argc, char** argv){
	int tryNum = 200; // number of times to run the average

	int cache = cacheSize(tryNum);
	printf("Cache Size = 2^%d or %d bits\n",(int)log2(cache),(int)cache);
	int block = blockSize(tryNum);
	printf("Block Size = 2^%d or %d bits\n",(int)log2(block),(int)block);
	double cacheAvg = cacheMemory(cache, tryNum , block);
	printf("Average cache time = %fns\n",cacheAvg);
	double mainAvg = mainMemory(cache,tryNum,block);
	printf("\nTime to Main Memory is: %fns \n", mainAvg);

	//average for cache memory time

	return 0;
}



