#include <bits/stdc++.h>
#include "BigReal.h"

#include <regex>
using namespace std;


int main() {
    BigReal r1("+333.9999");
    BigReal r2("-.777");
    BigReal r3("33.38.8");
    BigReal r4("0.");


    r1.print();
    r2.print();
    r3.print();
    r4.print();

    r1.isValidReal("+333.9999") ? cout << "True" : cout << "false";

    return 0;
}
