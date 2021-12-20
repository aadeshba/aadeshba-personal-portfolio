#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Hashtable.h"

using namespace std;

static char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                           'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

string randomStr() {
    string str = "";
    for (int i = 0; i < 28; i++) {
        str = str + letters[rand() % 26];
    }
    return str;
}

int main() { 
    Hashtable<int> h(false, 11);
    int n = 30000;
    int probes = 0;
    for (int i = 0; i < n; i++) {
        int temp = h.add(randomStr(), 10);
        probes += temp;
    }

    cout << "Number of probes: " << probes << endl;
    cout << "What number of probes should be slightly less than: " << (2 * n) / 3 << endl;
    
}