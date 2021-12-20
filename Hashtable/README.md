My Hashtable is pretty straight forward, I don't think there are any bugs. Compile Hashtable.h, ruinQP.cpp, and probeRate.cpp with "make"

ruinQP.cpp gives an example where an initialized Hashtable of size 16 (not prime) hangs with only 7 inserts. It should print out the error message "Try a prime table size..." then exit because it has been probing for so long
--> execute using ./ruinQP


probeRate.cpp tests n=30,000 cases of randomly added strings (From function randomstr) and first prints out the number of probes that occurred, followed by 2n/3= 20,000 expected probes.
--> execute using ./probeRate