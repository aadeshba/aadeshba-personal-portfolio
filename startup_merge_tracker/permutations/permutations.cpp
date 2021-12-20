#include <iostream>
#include <string>
using namespace std;

void swap(char* r, char* s) {
    char temp = *r;
    *r = *s;
    *s = temp;
}

void append(string s, int x) {
    if (x == (s.length() - 1)) {
        cout << s << endl;
        return;
    }
    for (int i = x; i < s.length(); i++) {
        swap(s[x], s[i]);
        append(s, x + 1);
    }
}

void permutations(string in) {
    int a = 0;
    append(in, a);
}
