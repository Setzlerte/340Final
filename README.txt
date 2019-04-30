README


1. How Big Is A Cache Block?
	blah

2. How Big Is The Cache?
	blah

3. How Long Does A Reference To Main Memory Take To Complete?
	Once we know the power of the cache size we can then find how long it takes to access main memory. We do this by running an array larger than the size of the cache and assigning a dummy value at each iteration. Once we know we have gone far enough to reach main memory we clock the end time.

4. How Long Does A Reference Satisfied From Cache Take To Complete?
	Similar to how we find the time for main memory to compplete we clock the time before we iterate through an array and clock the time at the end. The difference here is that we stick to random 
values that we know are smaller than the size of the cache.
