#include <bits/stdc++.h>
#include "BigReal.h"

#include <regex>

using namespace std;


int main() {
    BigReal r1("-56.8");
    BigReal r2("-123.55");
    BigReal r3("56.8");
    BigReal r4("123.55");

    cout << r1 + r1 << '\n'; //-113.6 (CORRECT WITH WRONG EXIT CODE) (-ve + -ve ) same number
    cout << r1 + r2 << '\n'; //-180.35 (CORRECT WITH WRONG EXIT CODE) (-ve + -ve) diff nums
    cout << r1 + r3; //0 (NO OUTPUT, WRONG EXIT CODE) (-ve + +ve) same number ////////
    cout << "\n";
    cout << r1 + r4; //66.75 (WORKING) (-ve + +ve) diff nums
    cout << "\n";
    cout << r2 + r1;// -180.35 (CORRECT WITH WRONG EXIT CODE)
    cout << "\n";
    cout << r2 + r2;//-247.1 (CORRECT WITH WRONG EXIT CODE)
    cout << '\n';
    cout << r2 + r3 << '\n';// -66.75 (WORKING)
    cout << r2 + r4; // 0 (NO OUTPUT WRONG EXIT CODE)
    cout << "\n";
    cout << r3 + r1; // 0 (NO OUTPUT WITH WRONG EXIT CODE) //////////
    cout << "\n";
    cout << r3 + r2; // -66.75 (WORKING)
    cout << "\n";
    cout << r3 + r3; // 113.6 (CORRECT WITH WRONG EXIT CODE)
    cout << "\n";
    cout << r3 + r4; // 180.35 (CORRECT WITH WRONG EXIT CODE)
    cout << "\n";
    cout << r4 + r1; // 66.75 (WORKING)
    cout << "\n";
    cout << r4 + r2; // 0 (NO OUTPUT, WRONG EXIT CODE)
    cout << "\n";
    cout << r4 + r3; // 180.35 (CORRECT WITH WRONG EXIT CODE)
    cout << "\n";
    cout << r4 + r4; //247.1 (CORRECT WITH WRONG EXIT CODE)




    return 0;
}
