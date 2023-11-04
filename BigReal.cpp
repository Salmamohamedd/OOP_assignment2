#include <bits/stdc++.h>
#include "BigReal.h"
#include <regex>


using namespace std;

//maybe create a default constructor, making value = 0.0?
BigReal::BigReal(string real) {
    if (isValidReal(real)) {
        if (real[0] == '-') {
            sign = '-';
            real.erase(0, 1);
        } else if (real[0] == '+') {
            sign = '+';
            real.erase(0, 1);
        }
        if (real.find('.') != -1) {
            integer = real.substr(0, real.find("."));
            fraction = real.substr(integer.size() + 1, real.find('\0') - integer.size() - 1);
        } else {
            integer = real.substr(0, real.find('\0'));
            fraction = '0';
        }
    } else {
        integer = '0';
        fraction = '0';
    }

}


bool BigReal::isValidReal(string real) {
    if (regex_match(real, regex("[-+]?\\d*.?\\d+"))) {
      //  cout << real << " is a Valid BigReal number!\n";
        return true;
    } else {
        //cout << real << " is an InValid BigReal number!\n";
        return false;
    }
}

void BigReal::print() {
    cout << sign << integer << "." << fraction << "\n";
}

BigReal BigReal::operator+(BigReal &anotherReal) {
    string result="";
    int common,temp, carry=0;
    if (fraction.size()> anotherReal.fraction.size()){
        result=fraction.substr((anotherReal.fraction.size())+1, fraction.size()-anotherReal.fraction.size());
        common=anotherReal.fraction.size();
    }else if(fraction.size()<anotherReal.fraction.size()){
        result=anotherReal.fraction.substr((fraction.size())+1, anotherReal.fraction.size()-fraction.size());
        common= fraction.size();
    }else{
        common=fraction.size();
    }
    for (int i = common-1; i >=0 ; --i) {
        temp = carry + fraction[i] + anotherReal.fraction[i] - '0';
        if (temp > '9'){
            carry=1;
            temp -= 10;
        }else {
            carry =0;
        }
        //result=temp +result;
    }

    //fraction + anotherReal.fraction;
}
