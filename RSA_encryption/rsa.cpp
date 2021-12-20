#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;


vector<int> toBinary(int n);//function to convert to binary
unsigned long ModularExp(unsigned long b, vector<int>, int size, unsigned long m);//function for modular exponentiation
unsigned long euclid(unsigned long a, unsigned long b);//function for euclidean algorithm: GCD
unsigned long extendedeuclid(unsigned long e, unsigned long L);//function for extended euclidean algorithm
void reverseStr(string& str);//function to reverse string in decryption process



int main(int argc, char **argv) {
    if (argc != 3) {  // if not right amount of args passed through
        return -1;
    }

    unsigned long p = atoi(argv[1]);//first prime  
    unsigned long q = atoi(argv[2]);//second prime   
    string request;//ENCRYPT DECRYPT or EXIT
    long unsigned x = 0;

    while (1) {
        cout << "Enter a valid command (exit, encrypt, decrypt) followed by its needed arguments: " << endl;

        
        cin >> request;

        int e = 65537;
        unsigned long M;
        unsigned long C;
        unsigned long n;


        if (request == "EXIT") {
            exit(EXIT_SUCCESS);
        }


        else if (request == "DECRYPT") {
            string input;//input file name
            string output;//output file name
            cin >> input;
            cin >> output;

            int L = (((p - 1) * (q - 1))/(euclid(p-1, q-1))); //L value to be used in decryption process
            //debug: cout << L << endl;
            if (L <= e) {
                cout << "L value error. Goodbye" << endl;
                exit(EXIT_FAILURE);x

            }

            unsigned long d = extendedeuclid(e, L);//d is our decryption key
            if (d < 0) {
                d += ((p - 1) * (q - 1));
            }
            //debug: cout << d << endl << endl;
        

           ifstream inputFile;
           inputFile.open(input);//opens input file to be read in

           ofstream outputFile;
           outputFile.open(output, ios::out | ios::trunc); //opening and clearing new output file

           vector<int> binaryD = toBinary(d);//stores our vector d as a binary vector of ints (0 or 1
           n = (p * q);//value to be used in decryption
           //debug: cout << n << endl;

           while (inputFile >> C) {//takes in C values (encrypted string of length x) one by one
               string s = "";
               M = ModularExp(C, binaryD, binaryD.size(), n);//stores its decrypted value in M

               //debug: cout << M << endl;

               unsigned long t = 0;
               while (M != 0) {
                   t = M % 100;//takes last two numbers
                   if (t == 0) {//00 is a space
                       s.push_back(' ');
                   } 
                   else {
                       t += 96;//otherwise, ASCII to convert to a letter
                       s.push_back(t);
                   }
                   M = M / 100;
               }
               reverseStr(s);//reverses string because push back puts it in reverse order
               //debug: cout << s << endl;
               outputFile << s;//adds new string to output file


           }
        
        }

        else if (request == "ENCRYPT") {
            string filename;//output file to store encrypted values
            string message;//string message

            cin >> filename;
            cin >> n;
            getline(cin, message);
            //debug: cout << message << endl;

            //debug: cout << n << endl;
        
            if (n < 27) {
                cout << "Invalid n value. Goodbye." << endl;
                exit(EXIT_FAILURE);
            }

            x = (long unsigned)(1 + (log(n / 27) / log(100))); //formula to get x

            //debug: cout << x << endl;

            unsigned int cnt = 1;//start from 1 to scrape off leading space from cin >> message

            ofstream oFile;
            oFile.open(filename, ios::out | ios::trunc); 
            string m;

            while(cnt < message.length()) {
                m = "";//empty string to reinitialize each iteration of loop
                char spaceChecker = ' ';
                for (unsigned int i = cnt; i < cnt + x; i++) {//cnt allows us to start at each successive character every x characters. we can set i to this for the fo rloop
                    if (i > message.length() - 1) {
                        break;
                    }
                    if (message[i] == spaceChecker) {//if ' ', then make it 00
                        m = m + '0' + '0';
                    } 
                    else {
                        int temp = message[i] - 96;//uses ASCII to determine what letters are being used
                        if (temp < 10) {
                            m = m + '0' + to_string(temp);//if the letters are less than 10 (i.e. single digits), we want to add a 0 before them
                        } else {
                            m = m + to_string(temp);//otherwise we just want the two digit number
                        }
                    }
                }
            
                if (m.length() < 2 * x) {
                    while (!(m.length() == (2 * x))) {//this is primarily for the last iteration if we don't go all the way up to x, we want to add 0's so that we can have a word of length 2*x still.
                        m = m + "0";
                    }
                }
                M = stoi(m);//convert this string to an int value
                //debug: cout << "this is M: " << m << endl;
  
                vector<int> binaryE = toBinary(e);//store e=65537 as a int vector of binary 1s and 0s
            
            
                C = ModularExp(M, binaryE, binaryE.size(), n);//perform modular exponentiation to encrypt 
            
            

                oFile << C << " ";//output to oFile

                cnt = cnt + x;//increment count for next iteration in while loop
            }
        }

        else {
            cout << "Invalid Command. Goodbye." << endl;
            exit(EXIT_FAILURE);
        }
    }
}
//END MAIN FUNCTION



vector<int> toBinary(int n) {
    vector<int> a;
    int i = 0;
    while (n > 0) {
        a.push_back(n % 2);
        // debug: cout << a[i] << " ";
        n = n / 2;
        i++;
    }
    // debug: cout << endl;
    return a;
}
//END TOBINARY


unsigned long ModularExp(unsigned long b, vector<int> a, int size, unsigned long m) { 
    long x = 1;
    long power = b % m;
    for (int i = 0; i < size; i++) {
        if (a[i] == 1) {
            x = (x * power) % m;
        }
        power = power * power % m;
        //cout << x << " : " << power;
    }
    //debug: cout << endl;
    return x;
}
//END MODULAREXP



unsigned long euclid(unsigned long a, unsigned long b) {
    if (a < 1 || b < 1) {
        cout << "error: negative p and/or q: " << a << " " << b << endl;
    }
    int x = a;
    int y = b;
    int temp = 0;
    while (y != 0) {
        temp = x % y;
        x = y;
        y = temp;
    }
    //debug: cout << x << endl;
    return x;
}
//END EUCLID

unsigned long extendedeuclid(unsigned long e, unsigned long L) {
    int s = 0; 
    int old_s = 1;
    int t = 1;
    int old_t = 0;
    unsigned long r = e;
    unsigned long old_r = L;
    while (r != 0) {
        int quotient = old_r / r;
        int temp = r;
        r = old_r - (quotient * r);
        old_r = temp;
        temp = s;
        s = old_s - (quotient * s);
        old_s = temp;
        temp = t;
        t = old_t - (quotient * t);
        old_t = temp;
    }
    if (old_r != 1) {
        cout << "You had an unfortunate choice for p and q :( goodbye" << endl;
        exit(EXIT_FAILURE);
    }
    return old_t;
}
//END EXTENDEDEUCLID


void reverseStr(string& str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        swap(str[i], str[n - i - 1]);
    }
}
//END REVERSESTR