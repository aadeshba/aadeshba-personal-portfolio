# Hashtable Implementation
This project was completed in my CSCI 104 (data structures and object-oriented programming) course at USC. It provides a templeted Hashtable.h class that utilizes the concept of quadratic probing to optimize runtimes for lookup() functions. It also includes two implementation files that test versions of the class ('ruinQP.cpp' anad 'probeRate.cpp').

This can be used in ones on programs as a set ADT with "#include Hashtable.h" and an instantiation with 'Hashtable<T> h(false, 11);' (where T is any primitive or object data type) which will randomly create 5 integer variables of type long to be used in the hashing process. The 11 argument initializes the initial size of the hashtable. Another option for a simpler instantiation is 'Hashtable<T> h;' which will just use the preset long values in the hashing process and the default beginning hash size. Either way will result in proper hashing.

Compile Hashtable.h, ruinQP.cpp, and probeRate.cpp with "make" to test the other two test files. 

## ruinQP.cpp
ruinQP.cpp gives an example where an initialized Hashtable of size 16 (not prime) hangs (infinite loops) with only 7 inserts. It should print out the error message "Try a prime table size..." then exit because it has been probing for so long.
--> execute using ./ruinQP

## probeRate.cpp
probeRate.cpp tests n=30,000 cases of randomly added strings (From function randomstr) and first prints out the number of probes that occurred, followed by 2n/3= 20,000 expected probes.
--> execute using ./probeRate
