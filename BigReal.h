#include <bits/stdc++.h>
using namespace std;

#ifndef BIGREAL_BIGREAL_H
#define BIGREAL_BIGREAL_H

class BigReal{
private:
    char sign = '+';
    string integer, fraction;
    //bool ValidReal;
public:
//    void setValid(string);
//    bool getValid;
    bool isValidReal(string);
    BigReal(string);
    BigReal operator+ (BigReal& anotherReal );
    BigReal operator- (BigReal& anotherReal);
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    friend ostream& operator << (ostream& out, BigReal num);

};

#endif //BIGREAL_BIGREAL_H
