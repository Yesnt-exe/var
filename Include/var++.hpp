#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
#include <iostream>


using std::string;
//this is for internal use
bool afterpoint(long double n) {
    int64_t i = (int64_t)n;
    long double g = (long double)i;
    return !(g == n);
}



class var {
private:
    bool isnumeric = true;
    bool isstring = false;
    long double numericdata = 0;
    std::string sdata = "";
    //3 for now
public:
    var(string val) {
        this->numericdata = 0;
        
        this->isnumeric = false;
        this->isstring = true;
        this->sdata = val;
    }
    var(const char* val) {
        this->numericdata = 0;
        this->isnumeric = false;
        this->isstring = true;
        this->sdata = std::string(val);
    }
    template<typename Type>
    var(short val) {
        
        this->numericdata = (long double)val;
        
        this->isstring = false;
        this->sdata = "";
        this->isnumeric = true;
    }
    var(unsigned short val) {

        this->numericdata = (long double)val;
        
        this->isstring = false;
        this->sdata = "";
        this->isnumeric = true;
    }
    var(int val) {

        this->numericdata = (long double)val;
        
        this->isstring = false;
        this->sdata = "";
        this->isnumeric = true;
    }
    var(unsigned int val) {

        this->numericdata = (long double)val;
        
        this->isstring = false;
        this->sdata = "";
        this->isnumeric = true;
    }
    var(float val) {

        this->numericdata = (long double)val;
        
        this->isstring = false;
        this->sdata = "";
        this->isnumeric = true;
    }
    var(long double val) {

        this->numericdata = val;
        
        this->isstring = false;
        this->sdata = "";
        this->isnumeric = true;
    }
    var(double val) {

        this->numericdata = (long double)val;

        this->isstring = false;
        this->sdata = "";
        this->isnumeric = true;
    }
    long double longfloat() {
        if (isnumeric) {
            return this->numericdata;
        }
        else {
            throw(false);
        }
    }
    template<class Type>
    Type CustomNumeric() {
        if (this->isnumeric) {
            return (Type)this->numericdata;
        }
        else {
            throw(std::exception());
        }
    }
    std::string str() {
        if (this->isnumeric) {
               return std::to_string(this->numericdata);
        }
        else if (this->isstring) {
            return sdata;
        }
    }
    std::string stri() {
        if (this->isnumeric) {
            return std::to_string((int64_t)this->numericdata);
        }
        else if (this->isstring) {
            return sdata;
        }
    }
    var operator+(var sec) {
        if (sec.isnumeric) {
            if (this->isnumeric) {
                return this->numericdata + sec.numericdata;
            }
            else if(this->isstring) {
                if (afterpoint(sec.numericdata)) {
                    return this->str() + sec.str();
                }
                else {
                    return this->str() + sec.stri();
                }
            }
        }
        else if (sec.isstring) {
            if (this->isnumeric) {
                if (afterpoint(this->numericdata)) {
                    return this->str() + sec.str();
                }
                else {
                    return this->stri() + sec.str();
                }
            }
            else {
                return this->str() + sec.str();
            }
        }
    }
    var operator-(var sec) {
        if (this->isstring || sec.isstring) {
            throw(false);
        }
        else if(this->isnumeric && sec.isnumeric) {
            return this->numericdata - sec.numericdata;
        }
    }
    void operator+=(var sec) {
        if (sec.isnumeric) {
            if (this->isnumeric) {
                this->numericdata = this->numericdata + sec.numericdata;
                this->isnumeric = true;
                this->sdata = "";
                this->isstring = false;
            }
            else if (this->isstring) {
                if (afterpoint(sec.numericdata)) {
                    this->sdata = this->str() + sec.str();
                    this->numericdata = 0;
                    this->isstring = true;
                    this->isnumeric = false;
                }
                else {
                    //string
                    this->sdata = this->str() + sec.stri();
                    this->numericdata = 0;
                    this->isstring = true;
                    this->isnumeric = false;
                }
            }
        }
        else if (sec.isstring) {
            this->sdata = this->str() + sec.str();
            this->numericdata = 0;
            this->isstring = true;
            this->isnumeric = false;
        }
    }
    void operator-=(var sec) {
        if (this->isstring || sec.isstring) {
            throw(false);
        }
        this->numericdata = this->numericdata - sec.numericdata;
        return;
    }
    void operator=(var sec) {
        this->isnumeric = sec.isnumeric;
        this->isstring = sec.isstring;
        this->numericdata = sec.numericdata;
        this->sdata = sec.sdata;
    }
    bool IsNumeric() {
        return this->isnumeric;
    }
    bool IsString() {
        return this->isstring;
    }
    ~var() {
        this->isnumeric = false;
        
        this->isstring = false;
        this->numericdata = false;
        this->sdata = "";
    }

};


string Type(var val) {
    if (val.IsNumeric()) {
        return "number";
    }
    else if (val.IsString()) {
        return "string";
    }
}
std::ostream& operator<<(std::ostream& os, var& val) {
    if (val.IsString()) {
        os << val.str();
    }
    else if (val.IsNumeric()) {
        if (afterpoint(val.longfloat())) {
            os << val.longfloat();
        }
        else {
            os << (int64_t)val.longfloat();
        }
    }
    return os;
}
std::istream& operator>>(std::istream& is, var& val) {
    std::string s;
    is >> s;
    if (s == "") {
        val = "";
        return is;
    }
    val = s;
    return is;
}