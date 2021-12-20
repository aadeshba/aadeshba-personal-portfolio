#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Hashtable.h"

using namespace std;

string randomStr();

int main() {
    Hashtable<int> h(true, 16);
    h.add("a", 10);
    h.add("c", 10);
    h.add("g", 10);
    h.add("s", 10);
    h.add("e", 10);
    h.add("aa", 10);
    h.add("ab", 10);

    return 1;
}

