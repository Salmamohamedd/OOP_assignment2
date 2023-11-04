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
    if (sign == anotherReal.sign){
        string result;
        int common,temp, carry = 0;
        if (fraction.size() > anotherReal.fraction.size()){
            result = fraction.substr((anotherReal.fraction.size()), fraction.size()-anotherReal.fraction.size());
            common = anotherReal.fraction.size();
        } else if(fraction.size() < anotherReal.fraction.size()){
            result = anotherReal.fraction.substr((fraction.size()), anotherReal.fraction.size()-fraction.size());
            common = fraction.size();
        } else {
            common = fraction.size();
        }
        for (int i = common-1; i >=0 ; --i) {
            temp = carry + (fraction[i] - '0') + (anotherReal.fraction[i] - '0');
            if (temp > 9){
                carry = 1;
                temp -= 10;
            }else {
                carry =0;
            }
            result = to_string(temp) + result;
        }
        //fraction + anotherReal.fraction;
        result = '.' + result;

        if (integer.size() > anotherReal.integer.size()){
            for (int i = 0; i < (integer.size() - anotherReal.integer.size()); ++i) {
                anotherReal = '0' + anotherReal.integer;
            }
        }else if (integer.size() < anotherReal.integer.size()){
            for (int i = 0; i < (anotherReal.integer.size() - integer.size()); ++i) {
                integer = '0' + integer;
            }
        }
        for (int i = integer.size() - 1; i >=0 ; --i) {
            temp = carry + (integer[i] - '0') + (anotherReal.integer[i] - '0');
            if (temp > 9){
                carry = 1;
                temp -= 10;
            }else {
                carry = 0;
            }
            result = to_string(temp) + result;
        }
        if (carry == 1){
            result = '1' + result;
        }

        if (sign == '-'){
            result = '-' + result;
        }
        //return result;
        cout << result;
    }



}

bool BigReal:: operator< (BigReal anotherReal){
    if (sign != anotherReal.sign) {
        if (sign == '-') {
            cout << "true";
            return true;
        }else {
            cout << "False";
            return false;

        }
    }
    if (integer.size() != anotherReal.integer.size()) {
        if (integer.size() > anotherReal.integer.size()) {
            cout << "False";
            return false;
        }
        else{
            cout << "true";
            return true;
        }
    }else {
        for(int i = 0; i < integer.size(); i++){
            if (integer[i] > anotherReal.integer[i]){
                cout << "False";
                return false;
            }
            else if (integer[i] < anotherReal.integer[i]){
                cout << "true";
                return true;
            }

        }

    }

    if (fraction.size() > anotherReal.fraction.size()){
        for (int i = anotherReal.fraction.size(); i < (fraction.size() - anotherReal.fraction.size()); ++i) {
            anotherReal.fraction[i] = '0';
        }
    } else if (fraction.size() < anotherReal.fraction.size()){
        for (int i = fraction.size(); i < (anotherReal.fraction.size() - fraction.size()); ++i) {
            fraction[i] = '0';
        }
    }
    for(int i = 0; i < fraction.size(); i++){
        if (fraction[i] > anotherReal.fraction[i]){
            cout << "False";
            return false;
        }
        else if (fraction[i] < anotherReal.fraction[i]) {
            cout << "True";
            return true;
        }
    }

}




bool BigReal::operator> (BigReal anotherReal){
    if (sign != anotherReal.sign) {
        if (sign == '-') {
            cout << "false";
            return false;
        }else {
            cout << "true";
            return true;

        }
    }
    if (integer.size() != anotherReal.integer.size()) {
        if (integer.size() < anotherReal.integer.size()) {
            cout << "False";
            return false;
        }
        else{
            cout << "true";
            return true;
        }
    }else {
        for(int i = 0; i < integer.size(); i++){
            if (integer[i] < anotherReal.integer[i]){
                cout << "False";
                return false;
            }
            else if (integer[i] > anotherReal.integer[i]){
                cout << "true";
                return true;
            }

        }

    }

    if (fraction.size() > anotherReal.fraction.size()){
        for (int i = anotherReal.fraction.size(); i < (fraction.size() - anotherReal.fraction.size()); ++i) {
            anotherReal.fraction[i] = '0';
        }
    } else if (fraction.size() < anotherReal.fraction.size()){
        for (int i = fraction.size(); i < (anotherReal.fraction.size() - fraction.size()); ++i) {
            fraction[i] = '0';
        }
    }
    for(int i = 0; i < fraction.size(); i++){
        if (fraction[i] < anotherReal.fraction[i]){
            cout << "False";
            return false;
        }
        else if (fraction[i] > anotherReal.fraction[i]) {
            cout << "True";
            return true;
        }
    }

}
bool BigReal::operator== (BigReal anotherReal) {
    if (sign != anotherReal.sign) {
        cout<<"False";
        return false;
    }
    if(integer.size() == anotherReal.integer.size() && fraction.size() == anotherReal.fraction.size()){
        for(int i = 0;i<integer.size();i++){
            if(integer[i] != anotherReal.integer[i])
                return false;
        }
        for(int i = 0;i<fraction.size();i++){
            if(fraction[i] != anotherReal.fraction[i])
                return false;
        }
        cout<<"True";
        return true;
    }
    cout<<"False";
    return false;
}
