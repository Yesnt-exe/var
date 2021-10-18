#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
#include <iostream>

//Experimental version
//Made by Yesnt

using std::string;
//this is for internal use
bool afterpoint(long double n) {
    int64_t i = (int64_t)n;
    long double g = (long double)i;
    return !(g == n);
}

//accuracy to 4 digits after .
std::string UFormat(long double ld){
    std::stringstream stream;
    stream << ld;
    return stream.str();
}

class VarException{
private:
    std::string awhat;
public:
    VarException(std::string a){
        this->awhat = a;
    }
    std::string what(){
        return this->awhat;
    }
};

class var {
private:
    bool nonetype = false;
    bool isnumeric = false;
    bool isstring = false;
    long double numericdata = 0;
    std::string sdata = "";
    //3 for now
public:
    var(){
        this->numericdata = 0;
        this->isnumeric = false;
        this->isstring = false;
        this->nonetype = true;
        this->sdata = "";
    }
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
            return 0;
        }
    }
    template<class Type>
    Type CustomNumeric() {
        if (this->isnumeric) {
            return (Type)this->numericdata;
        }
        else {
            return (Type)0;
        }
    }
    //automatic formatting, maxium accuracy up to 4 digits after .
    std::string str(){
        if(this->isnumeric){
            return UFormat(this->numericdata);
        }
        else if(this->isstring){
            return this->sdata;
        }
        return "";
    }
    //returns to_string without removing any digits after .
    std::string fstr(){
        if(this->isnumeric){
            return std::to_string(this->numericdata);
        }
        else if(this->isstring){
            return this->sdata;
        }
        return "";
    }
    var operator+(var sec) {
        if(this->isnumeric){
            if(sec.isnumeric){
                 return var(this->numericdata + sec.numericdata);
            }
            else if(sec.isstring){
                 return var(this->str() + sec.str());
            }
        }
        else if(this->isstring || this->nonetype){
            return var(this->str() + sec.str());
        }
        return var(0);
    }
    var operator-(var sec) {
         if(this->IsNone() || this->IsString() || sec.IsNone() || sec.IsString()){
            throw(VarException("Substracting is not supported with other types than numeric!"));
        }
        else if(this->isnumeric && sec.isnumeric){
            return this->numericdata - sec.numericdata;
        }
        return var(0);
    }
    void operator+=(var sec) {
       if(this->isnumeric){
           if(sec.isnumeric){
               this->numericdata += sec.numericdata;
               this->isstring = false;
               return;
           }
           else if(sec.isstring){
               this->sdata = this->str() + sec.str();
               this->isstring = true;
               this->isnumeric = false;
               this->numericdata = 0;
               return;
           }
       }
       else if(this->isstring || this->nonetype){
           this->sdata += sec.str();
           this->isstring = true;
           this->isnumeric = false;
           this->nonetype = false;
           this->numericdata = 0;
           return;
       }
    }
    void operator-=(var sec) {
        if(this->nonetype || this->isstring || sec.IsNone() || sec.IsString()){
            throw(VarException("Substracting is not supported with other types than numeric!"));
            return;
        }
        else if(this->isnumeric && sec.isnumeric){
            this->numericdata -= sec.numericdata;
            return;
        }
        throw(VarException("An error occured while substracting!"));
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
    bool IsNone(){
        return this->nonetype;
    }
    ~var() {
        this->isnumeric = false;
        this->nonetype = false;
        this->isstring = false;
        this->numericdata = false;
        this->sdata = "";
    }

};


string Type(var val) {
    if (val.IsNumeric()) {
        if(afterpoint(val.longfloat())){
            return "Float";
        }
        else{
            return "Int";
        }
    }
    else if (val.IsString()) {
        return "String";
    }
    return "None";
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
    else if(val.IsNone()){
        os << "None";
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