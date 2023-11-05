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
            integer = real.substr(0, real.find('.'));
            while (integer.length() > 1 && integer[0] == '0') {
                integer = integer.substr(1);
            }
            if (integer.empty())
                integer = '0';
            fraction = real.substr(integer.size() + 1, real.find('\0') - integer.size() - 1);
            while (fraction.length() > 1 && fraction[fraction.length() - 1] == 0) {
                fraction.pop_back();
            }
            if (fraction.empty())
                fraction = '0';
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

BigReal BigReal::operator+(BigReal &anotherReal) {
    if (sign == anotherReal.sign) {
        string result = "";
        int common, temp, carry = 0;
        if (fraction.size() > anotherReal.fraction.size()) {
            result = fraction.substr((anotherReal.fraction.size()), fraction.size() - anotherReal.fraction.size());
            common = anotherReal.fraction.size();
        } else if (fraction.size() < anotherReal.fraction.size()) {
            result = anotherReal.fraction.substr((fraction.size()), anotherReal.fraction.size() - fraction.size());
            common = fraction.size();
        } else {
            common = fraction.size();
        }
        for (int i = common - 1; i >= 0; --i) {
            temp = carry + (fraction[i] - '0') + (anotherReal.fraction[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            } else {
                carry = 0;
            }
            result = to_string(temp) + result;
        }
        while (result.length() > 1 && result[result.length() - 1] == '0') {
            result.pop_back();
        }
        result = '.' + result;

        if (integer.size() > anotherReal.integer.size()) {
            for (int i = 0; i < (integer.size() - anotherReal.integer.size()); ++i) {
                anotherReal.integer = '0' + anotherReal.integer;
            }
        } else if (integer.size() < anotherReal.integer.size()) {
            for (int i = 0; i < (anotherReal.integer.size() - integer.size()); ++i) {
                integer = '0' + integer;
            }
        }
        for (int i = integer.size() - 1; i >= 0; --i) {
            temp = carry + (integer[i] - '0') + (anotherReal.integer[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            } else {
                carry = 0;
            }
            result = to_string(temp) + result;
        }
        if (carry == 1) {
            result = '1' + result;
        }

        while (result.length() > 1 && result[0] == '0' && result[1] != '.') {
            result = result.substr(1);
        }

        if (sign == '-') {
            result = '-' + result;
        }
        //cout << result;
        return result;
    } else {
        int temp, carry = 0;
        string result, this1 = (integer + '.' + fraction), another = (anotherReal.integer + '.' + anotherReal.fraction);

        if (((anotherReal < *this) && (BigReal('-' + (this1))) < anotherReal) ||
            (anotherReal > *this && (BigReal('-' + (another))) > *this)) {
            if (fraction.size() > anotherReal.fraction.size()) {
                for (int i = anotherReal.fraction.size(); i < (fraction.size()); ++i) {
                    anotherReal.fraction = anotherReal.fraction + '0';
                }
            } else if (fraction.size() < anotherReal.fraction.size()) {
                for (int i = fraction.size(); i < (anotherReal.fraction.size()); ++i) {
                    fraction = fraction + '0';
                }
            }
            for (int i = fraction.size() - 1; i >= 0; --i) {
                temp = carry + (fraction[i] - '0') - (anotherReal.fraction[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;
            }
            while (result.length() > 1 && result[result.length() - 1] == '0') {
                result.pop_back();
            }
            result = '.' + result;

            if (integer.size() > anotherReal.integer.size()) {
                for (int i = 0; i < (integer.size() - anotherReal.integer.size()); ++i) {
                    anotherReal.integer = '0' + anotherReal.integer;
                }
            } else if (integer.size() < anotherReal.integer.size()) {
                for (int i = 0; i < (anotherReal.integer.size() - integer.size()); ++i) {
                    integer = '0' + integer;
                }
            }
            for (int i = integer.size() - 1; i >= 0; --i) {
                temp = carry + (integer[i] - '0') - (anotherReal.integer[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;

            }
            while (result.length() > 1 && result[0] == '0' && result[1] != '.') {
                result = result.substr(1);
            }
            if (sign == '-') {
                result = '-' + result;
            }
            //cout << result;
            return result;
        } else if ((anotherReal < *this && (BigReal('-' + (this1))) > anotherReal) ||
                   (anotherReal > *this && (BigReal('-' + (another))) < *this)) {
            if (fraction.size() > anotherReal.fraction.size()) {
                for (int i = anotherReal.fraction.size(); i < (fraction.size()); ++i) {
                    anotherReal.fraction = anotherReal.fraction + '0';
                }
            } else if (fraction.size() < anotherReal.fraction.size()) {
                for (int i = fraction.size(); i < (anotherReal.fraction.size()); ++i) {
                    fraction = fraction + '0';
                }
            }
            for (int i = fraction.size() - 1; i >= 0; --i) {
                temp = carry + (anotherReal.fraction[i] - '0') - (fraction[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;
            }
            while (result.length() > 1 && result[result.length() - 1] == '0') {
                result.pop_back();
            }
            result = '.' + result;

            if (integer.size() > anotherReal.integer.size()) {
                for (int i = 0; i <= (integer.size() - anotherReal.integer.size()); ++i) {
                    anotherReal.integer = '0' + anotherReal.integer;
                }
            } else if (integer.size() < anotherReal.integer.size()) {
                for (int i = 0; i <= (anotherReal.integer.size() - integer.size()); ++i) {
                    integer = '0' + integer;
                }
            }
            for (int i = integer.size() - 1; i >= 0; --i) {
                temp = carry + (anotherReal.integer[i] - '0') - (integer[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;

            }
            while (result.length() > 1 && result[0] == '0' && result[1] != '.') {
                result = result.substr(1);
            }
            if (sign == '+') {
                result = '-' + result;
            }
            //cout << result;
            return result;
        }
        else  {
            result = '0';
            //cout << result;
            return result;
        }
    }


}

bool BigReal::operator<(BigReal anotherReal) {
    if (sign != anotherReal.sign) {
        if (sign == '-') {
            //cout << "true";
            return true;
        } else {
            //cout << "False";
            return false;

        }
    }
    if (sign == '-') {
        if (integer.size() != anotherReal.integer.size()) {
            if (integer.size() < anotherReal.integer.size()) {
                //cout << "False";
                return false;
            } else {
                //cout << "true";
                return true;
            }
        } else {
            for (int i = 0; i < integer.size(); i++) {
                if (integer[i] < anotherReal.integer[i]) {
                    //cout << "False";
                    return false;
                } else if (integer[i] > anotherReal.integer[i]) {
                    //cout << "true";
                    return true;
                }

            }

        }

        if (fraction.size() > anotherReal.fraction.size()) {
            for (int i = anotherReal.fraction.size(); i < fraction.size(); ++i) {
                anotherReal.fraction[i] = '0';
            }
        } else if (fraction.size() < anotherReal.fraction.size()) {
            for (int i = fraction.size(); i < anotherReal.fraction.size(); ++i) {
                fraction[i] = '0';
            }
        }
        for (int i = 0; i < fraction.size(); i++) {
            if (fraction[i] < anotherReal.fraction[i]) {
                //cout << "False";
                return false;
            } else if (fraction[i] > anotherReal.fraction[i]) {
                //cout << "True";
                return true;
            }
        }
    }
    if (integer.size() != anotherReal.integer.size()) {
        if (integer.size() > anotherReal.integer.size()) {
            //cout << "False";
            return false;
        } else {
            //cout << "true";
            return true;
        }
    } else {
        for (int i = 0; i < integer.size(); i++) {
            if (integer[i] > anotherReal.integer[i]) {
                //cout << "False";
                return false;
            } else if (integer[i] < anotherReal.integer[i]) {
                //cout << "true";
                return true;
            }

        }

    }

    if (fraction.size() > anotherReal.fraction.size()) {
        for (int i = anotherReal.fraction.size(); i < fraction.size(); ++i) {
            anotherReal.fraction[i] = '0';
        }
    } else if (fraction.size() < anotherReal.fraction.size()) {
        for (int i = fraction.size(); i < anotherReal.fraction.size(); ++i) {
            fraction[i] = '0';
        }
    }
    for (int i = 0; i < fraction.size(); i++) {
        if (fraction[i] > anotherReal.fraction[i]) {
            //cout << "False";
            return false;
        } else if (fraction[i] < anotherReal.fraction[i]) {
            //cout << "True";
            return true;
        }
    }

}

bool BigReal::operator>(BigReal anotherReal) {
    if (sign != anotherReal.sign) {
        if (sign == '-') {
            //cout << "false";
            return false;
        } else {
            //cout << "true";
            return true;

        }
    }
    if (sign == '-') {
        if (integer.size() != anotherReal.integer.size()) {
            if (integer.size() > anotherReal.integer.size()) {
                //cout << "False";
                return false;
            } else {
                //cout << "true";
                return true;
            }
        } else {
            for (int i = 0; i < integer.size(); i++) {
                if (integer[i] > anotherReal.integer[i]) {
                    //cout << "False";
                    return false;
                } else if (integer[i] < anotherReal.integer[i]) {
                    //cout << "true";
                    return true;
                }

            }

        }

        if (fraction.size() > anotherReal.fraction.size()) {
            for (int i = anotherReal.fraction.size(); i < fraction.size(); ++i) {
                anotherReal.fraction[i] = '0';
            }
        } else if (fraction.size() < anotherReal.fraction.size()) {
            for (int i = fraction.size(); i < anotherReal.fraction.size(); ++i) {
                fraction[i] = '0';
            }
        }
        for (int i = 0; i < fraction.size(); i++) {
            if (fraction[i] > anotherReal.fraction[i]) {
                //cout << "False";
                return false;
            } else if (fraction[i] < anotherReal.fraction[i]) {
                //cout << "True";
                return true;
            }
        }
    }
    if (integer.size() != anotherReal.integer.size()) {
        if (integer.size() < anotherReal.integer.size()) {
            //cout << "False";
            return false;
        } else {
            //cout << "true";
            return true;
        }
    } else {
        for (int i = 0; i < integer.size(); i++) {
            if (integer[i] < anotherReal.integer[i]) {
                //cout << "False";
                return false;
            } else if (integer[i] > anotherReal.integer[i]) {
                //cout << "true";
                return true;
            }

        }

    }

    if (fraction.size() > anotherReal.fraction.size()) {
        for (int i = anotherReal.fraction.size(); i < fraction.size(); ++i) {
            anotherReal.fraction[i] = '0';
        }
    } else if (fraction.size() < anotherReal.fraction.size()) {
        for (int i = fraction.size(); i < anotherReal.fraction.size(); ++i) {
            fraction[i] = '0';
        }
    }
    for (int i = 0; i < fraction.size(); i++) {
        if (fraction[i] < anotherReal.fraction[i]) {
            //cout << "False";
            return false;
        } else if (fraction[i] > anotherReal.fraction[i]) {
            //cout << "True";
            return true;
        }
    }

}

bool BigReal::operator==(BigReal anotherReal) {
    if (sign != anotherReal.sign) {
        //cout<<"False";
        return false;
    }
    if (integer.size() == anotherReal.integer.size() && fraction.size() == anotherReal.fraction.size()) {
        for (int i = 0; i < integer.size(); i++) {
            if (integer[i] != anotherReal.integer[i])
                return false;
        }
        for (int i = 0; i < fraction.size(); i++) {
            if (fraction[i] != anotherReal.fraction[i])
                return false;
        }
        //cout<<"True";
        return true;
    }
    //cout<<"False";
    return false;
}

BigReal BigReal::operator-(BigReal &anotherReal) {
    string result = "";
    int temp, carry = 0;
    if (sign == anotherReal.sign) {
        if ((anotherReal < *this && sign == '+') || (anotherReal > *this && sign == '-')) {
            if (fraction.size() > anotherReal.fraction.size()) {
                for (int i = anotherReal.fraction.size(); i < (fraction.size()); ++i) {
                    anotherReal.fraction = anotherReal.fraction + '0';
                }
            } else if (fraction.size() < anotherReal.fraction.size()) {
                for (int i = fraction.size(); i < (anotherReal.fraction.size()); ++i) {
                    fraction = fraction + '0';
                }
            }
            for (int i = fraction.size() - 1; i >= 0; --i) {
                temp = carry + (fraction[i] - '0') - (anotherReal.fraction[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;
            }
            while (result.length() > 1 && result[result.length() - 1] == '0') {
                result.pop_back();
            }
            result = '.' + result;

            if (integer.size() > anotherReal.integer.size()) {
                for (int i = 0; i < (integer.size() - anotherReal.integer.size()); ++i) {
                    anotherReal.integer = '0' + anotherReal.integer;
                }
            } else if (integer.size() < anotherReal.integer.size()) {
                for (int i = 0; i < (anotherReal.integer.size() - integer.size()); ++i) {
                    integer = '0' + integer;
                }
            }
            for (int i = integer.size() - 1; i >= 0; --i) {
                temp = carry + (integer[i] - '0') - (anotherReal.integer[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;

            }
            while (result.length() > 1 && result[0] == '0' && result[1] != '.') {
                result = result.substr(1);
            }
            if (sign == '-') {
                result = '-' + result;
            }
            //cout << result;
            return result;
        } else if ((anotherReal > *this && sign == '+') || (anotherReal < *this && sign == '-')) {
            if (fraction.size() > anotherReal.fraction.size()) {
                for (int i = anotherReal.fraction.size(); i < (fraction.size()); ++i) {
                    anotherReal.fraction = anotherReal.fraction + '0';
                }
            } else if (fraction.size() < anotherReal.fraction.size()) {
                for (int i = fraction.size(); i < (anotherReal.fraction.size()); ++i) {
                    fraction = fraction + '0';
                }
            }
            for (int i = fraction.size() - 1; i >= 0; --i) {
                temp = carry + (anotherReal.fraction[i] - '0') - (fraction[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;
            }
            while (result.length() > 1 && result[result.length() - 1] == 0) {
                result.pop_back();
            }
            result = '.' + result;

            if (integer.size() > anotherReal.integer.size()) {
                for (int i = 0; i <= (integer.size() - anotherReal.integer.size()); ++i) {
                    anotherReal.integer = '0' + anotherReal.integer;
                }
            } else if (integer.size() < anotherReal.integer.size()) {
                for (int i = 0; i <= (anotherReal.integer.size() - integer.size()); ++i) {
                    integer = '0' + integer;
                }
            }
            for (int i = integer.size() - 1; i >= 0; --i) {
                temp = carry + (anotherReal.integer[i] - '0') - (integer[i] - '0');
                if (temp < 0) {
                    temp += 10;
                    carry = -1;
                } else {
                    carry = 0;
                }
                result = to_string(temp) + result;

            }
            while (result.length() > 1 && result[0] == '0' && result[1] != '.') {
                result = result.substr(1);
            }
            if (sign == '+') {
                result = '-' + result;
            }
            //cout << result;
            return result;
        } else {
            //cout << "0";
            result = '0';
        }
        return result;
    }
    else {
        int common;
        if (fraction.size() > anotherReal.fraction.size()) {
            result = fraction.substr((anotherReal.fraction.size()), fraction.size() - anotherReal.fraction.size());
            common = anotherReal.fraction.size();
        }
        else if (fraction.size() < anotherReal.fraction.size()) {
            result = anotherReal.fraction.substr((fraction.size()), anotherReal.fraction.size() - fraction.size());
            common = fraction.size();
        }
        else {
            common = fraction.size();
        }
        for (int i = common - 1; i >= 0; --i) {
            temp = carry + (fraction[i] - '0') + (anotherReal.fraction[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            } else {
                carry = 0;
            }
            result = to_string(temp) + result;
        }
        while (result.length() > 1 && result[result.length() - 1] == '0') {
            result.pop_back();
        }

        result = '.' + result;

        if (integer.size() > anotherReal.integer.size()) {
            for (int i = 0; i < (integer.size() - anotherReal.integer.size()); ++i) {
                anotherReal.integer = '0' + anotherReal.integer;
            }
        } else if (integer.size() < anotherReal.integer.size()) {
            for (int i = 0; i < (anotherReal.integer.size() - integer.size()); ++i) {
                integer = '0' + integer;
            }
        }
        for (int i = integer.size() - 1; i >= 0; --i) {
            temp = carry + (integer[i] - '0') + (anotherReal.integer[i] - '0');
            if (temp > 9) {
                carry = 1;
                temp -= 10;
            } else {
                carry = 0;
            }
            result = to_string(temp) + result;
        }
        if (carry == 1) {
            result = '1' + result;
        }
        while (result.length() > 1 && result[0] == '0' && result[1] != '.') {
            result = result.substr(1);
        }

        if (sign == '-') {
            result = '-' + result;
        }
        //cout << result;
        return result;

    }
}


ostream &operator<<(ostream &out, BigReal num) {
    if (num.sign == '-' && num.integer != "0" && num.fraction != "0") {
        out << num.sign << num.integer << '.' << num.fraction;
    } else {
        out << num.integer << '.' << num.fraction;
    }
    return out;
}
