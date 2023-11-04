#include <bits/stdc++.h>
#include "BigReal.h"

#include <regex>
using namespace std;


int main() {
    BigReal r1("-333.9999");
    BigReal r2("1233.777");
    BigReal r3("3338.8");
    BigReal r4("0.");


//    r1.print();
//    r2.print();
//    r3.print();
//    r4.print();

  //  r1.isValidReal("+333.9999") ? cout << "True" : cout << "false";

    if(r1 < r2){
        cout <<"\n";
    }
    if(r2 < r3){
        cout << "\n";
    }

    return 0;
}
