README
Thomas Setzler and Morgan Smith

1. How Big Is A Cache Block?
	The cache block size is found by probing access times to memory based on powers of two. The time to perform each access is recorded into an array.  These access times are differenced based on each power of two used to access memory and locations at which the time increases by a power of two are recorded and averaged together to obtain the cache block size.
2. How Big Is The Cache?
	Similar to the cache block, the cache size is obtained through the same process, except on a much larger scale.  Access are based on powers of two and then the time differences between each power of two is recorded.  Here the significant increas is a  larger power of two than the cache block.

3. How Long Does A Reference To Main Memory Take To Complete?
	Once we know the power of the cache size we can then find how long it takes to access main memory. We do this by running an array larger than the size of the cache and assigning a dummy value at each iteration. Once we know we have gone far enough to reach main memory we clock the end time.

4. How Long Does A Reference Satisfied From Cache Take To Complete?
	Similar to how we find the time for main memory to compplete we clock the time before we iterate through an array and clock the time at the end. The difference here is that we stick to random 
values that we know are smaller than the size of the cache.
