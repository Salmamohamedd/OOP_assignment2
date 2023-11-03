#include <bits/stdc++.h>
#include <regex>
using namespace std;

class BigReal{
private:
    char sign = '+';
    string integer, fraction;
public:
    BigReal(string);
    BigReal operator+ (BigReal&);
    void print();
};

BigReal::BigReal(string real) {
    if (regex_match(real, regex("[+-]?[0-9]+?.?[0-9]+?"))) {
        if (real[0] == '-') {
            sign = '-';
            real[0] = '0';
        } else if (real[0] == '+') {
            real[0] = '0';
        }
    }

    if (integer.empty())
        integer = '0';
    if (fraction.empty())
        fraction = '0';
}


void BigReal::print() {
    cout << sign << integer << "." << fraction << "\n";
}

int main() {
    BigReal r1("+333.9999");
    BigReal r2("-.777");
    BigReal r3("33.38.8");
    BigReal r4("0.9999x");


    r1.print();
    r2.print();
    r3.print();
    r4.print();

    return 0;
}
