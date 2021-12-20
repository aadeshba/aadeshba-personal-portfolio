#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdio>


template<typename T>
class Hashtable {
private:
    void resize();
    int hash(std::string k) const;
    bool debug;
    unsigned int size;
    int nextsize;//nextsize variable used for resizing
    int _allSizes[17]
            = {11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117};//array with all sizes
    unsigned int entries;
    std::pair<std::string, T>* table;
    int r[5];

public:
    Hashtable(bool debug = false, unsigned int size = 11) { //constructor 
        this->debug = debug;
        this->size = size;
        table = new std::pair<std::string, T>[size];//dynamically allocate our hashtable to array of pairs

        for (int i = 0; i < 17; i++) {//find the next value for nextsize in resize()
            if (size < _allSizes[i]) {
                nextsize = i;
                break;
            }
        }
        entries = 0;
        if (debug) {//debug values
            r[0] = 983132572;
            r[1] = 1468777056;
            r[2] = 552714139;
            r[3] = 984953261;
            r[4] = 261934300;
        }
        if (!debug) {//if not debug, randomly generates values
            srand(time(0));
            for (int i = 0; i < 5; i++) {
                r[i] = rand() % (size - 1);
            }
        }
    }
    ~Hashtable();
    int add(std::string k, const T& val);
    const T& lookup(std::string k);
    void reportAll(std::ostream&) const;
};

template <typename T>
Hashtable<T>::~Hashtable() {//destructor
    delete[] table;
}

template <typename T>
int Hashtable<T>::add(std::string k, const T& val) {
    if ((double)(((double)(entries + 1)) / (double)size)
        >= 0.5) {  // load factor checker--> if entries+1/size will exceed 0.5 then call resize function
        resize();
    }
    int probes = 0;
    int index = hash(k);//first hashed point
    int pos = index;


    while (table[pos].first != "") {//while loop checks if not empty (will enter if this index hasn't been taken before. 
        if (table[pos].first == k) {//checks if non empty index is already k-> already in the array, return
            return 0;
        }
        if (probes > 99999) {
            std::cout << "You have probed over " << probes << " times!" << std::endl;
            std::cout << "Try a prime table size..." << std::endl;
            exit(EXIT_FAILURE);
        }
        probes++;
        pos = (index + (probes*probes)) % size; //quadratic probing
    }
    table[pos].first = k;
    
    table[pos].second = val;
    entries++;//total number of entries in the table
    
    return probes;

}


template <typename T>
const T& Hashtable<T>::lookup(std::string k) {
    int hashed = hash(k);//similar to add function quadratic probing to search
    int index = hashed;
    int i = 1;
    while (table[index].first != "") {//checks if there is something in the particular index (if empty, return garbage value)
        if (table[index].first == k) {//if current index is k, return its T value
            return table[index].second;
        }
        index = (hashed + (i * i)) % size;//quadratic probing to keep checking
        i++;
    }
    return table[0].second;  // garbage value
}

template<typename T>
void Hashtable<T>::reportAll(std::ostream& os) const {
    for (int i = 0; i < size; i++) {//iterates through table
        if (table[i].first != "") {//checks if there is a hashed string in this index of the table
            os << table[i].first << " " << table[i].second;//outputs to the ostream
        }
    }
}

template<typename T>
void Hashtable<T>::resize() {

    std::pair<std::string, T> temp[size];
    for (int i = 0; i < size; i++) {
        if (table[i].first != "") {
            temp[i] = table[i];
        }
    }
    int prevSize = size;
    size = _allSizes[nextsize];
    nextsize++;
    delete[] table;
    table = new std::pair<std::string, T>[size];
    //std::cout << "entering the second for loop" << std::endl;
    entries = 0;
    for (int i = 0; i < prevSize ; i++) {
        if (temp[i].first != "") {
            //std::cerr << temp[i].first << std::endl;
            add(temp[i].first, temp[i].second);
            //std::cerr << "adding " << i << " to ht" << std::endl;
        }

    }
    return;
}

template<typename T>
int Hashtable<T>::hash(std::string k) const {
    std::string alphabet = " abcdefghijklmnopqrstuvwyxz";//full alphabet to iterate through
    long long w[5];//all w values
    long long a[6];//all a values to be used for w values
    
    //debug: cout << "in hash" << endl;
    int curr = k.length() - 1;
    for (int i = 4; i >= 0; i--) {//outer for loop goes through each w
        for (int j = 5; j >= 0; j--) {//goes through each a for each w
            //iterate through the whole string from end to first string
            if (curr >= 0) {
                for (int l = 1; l < alphabet.length(); l++) {//constant time-> runs through the alphabet
                    if (k[curr] == alphabet[l]) {
                        a[j] = l;
                    }
                }
            } 
            else {
                a[j] = 0;//once the word is over, just fill with 0's
            }
            curr--;
        }
        
        long long total = ((27 * 27 * 27 * 27 * 27) * a[0]) + ((27 * 27 * 27 * 27) * a[1]) + ((27 * 27 * 27) * a[2]) + ((27 * 27) * a[3]) + (27 * a[4]) + a[5];
        w[i] = total;
    }
    long long index = 0;

    for (int i = 0; i < 5; i++) {//calculates final value to be modded with size
        index = index + (w[i] * r[i]);
    }

    index = index % size;//mods final value with size
    int realindex = (int)index;//converts to int

    return realindex;
}