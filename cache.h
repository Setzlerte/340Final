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
}


int cacheSize(int attempts){
/* Cache size calls the cacheSizeCalculation to calculate an average of access.  
	 It returns the cache size
	 Paramaters:
	 attempts: total number of times to run cacheSizeCalculation, minimum recommendation of 500  
	*/

}



int blockSize(int attempts){
	/* block size calls the cacheSizeCalculation to calculate an average of access.  
	 It returns the size of the block
	 Paramaters:
	 attempts: total number of times to run cacheSizeCalculation, minimum recommendation of 500 
	*/
}

double mainMemoryCalc (int cache,int block){
/* mainMemoryCalc calucaltes the access time to main memory and returns it
 	Paramaters:
	cache: size of cache
	block: size of block

*/
}

double cacheMemoryCalc (int cache, int block ){
/* this function calculates the access times for the cache memory and returns it
	parameters:
	cache: size of the cache
	block: size of the lock

*/
}

double cacheMemory(int cache, int tryTimes, int block){
/* cacheMemory computes the average cache access time and returns it
	Parameters:
	cache: size of cache
	tryTimes: number of times to attempt and average;
	block: size of block
*/
}

double mainMemory(int cache, int tryTimes, int block){
/* mainMemory computes the average cache access time and returns it
	Parameters:
	cache: size of cache
	tryTimes: number of times to attempt and average;
	block: size of block
*/
}
