#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
#include <cmath>
#include <iostream>
#include <array>

//Experimental version
//Made by Yesnt

using std::string;
//this is for internal use
bool afterpoint(long double n) {
    int64_t i = (int64_t)n;
    long double g = (long double)i;
    return !(g == n);
}
template<class VecType, class Type>
void UnpackArguments(std::vector<VecType>&vec, Type argument){
    vec.push_back(argument);
}

//this is for internal use
template<class VecType, class Type, class ... Args>
void UnpackArguments(std::vector<VecType>&vec,Type argument, Args ... args){
    //unpack
    vec.push_back(argument);
    UnpackArguments(vec, args...);
}

//accuracy to 4 digits after .
std::string UFormat(long double ld){
    std::stringstream stream;
    stream << ld;
    return stream.str();
}


class var;
template<class T>
var VarFromNumeric(T Type);

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
    bool isvector = false;
    std::vector<var>vecdata;
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
    var(char val) {
        this->numericdata = 0;
        this->isnumeric = false;
        this->isstring = true;
        this->sdata += val;
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
    //VERY EXPERIMENTAL MIGHT NOT WORK
    template<class Type, size_t ArraySize>
    var(std::array<Type, ArraySize>val){
        this->isvector = true;  
        this->isnumeric = false;
        this->isstring = false;
        for(size_t i = 0; i<ArraySize; i++){this->vecdata.push_back(val[i]);}
        return;
    }
    template<class Type>
    var(std::vector<Type>val){
        this->isvector = true;
        this->isnumeric = false;
        this->isstring = false;
        for(const auto& ref : val){
            this->vecdata.push_back(var(ref));
        }
        return;
    }
    template<class ... Args>
    var(Args ... arguments){
        this->isvector = true;
        UnpackArguments(this->vecdata, arguments...);
        return;
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
        else if(this->isvector){
            std::string ret;
            ret += "{";
            for(size_t i = 0; i<this->vecdata.size(); i++){
                if(i != 0 && this->vecdata[i].str() != ""){
                    ret += ',';
                }
                ret += this->vecdata[i].str();
            }
            ret += "}";
            return ret;
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
        else if(this->isvector){
            throw(VarException("Operator + is not supported with Array, you can use Append() or += operator!"));
            return 0;
        }
        return var(0);
    }
    var operator+(char sec) {
        if(this->isstring){
            return this->sdata + sec;
        }
        else if(this->isnumeric){
            return this->numericdata + sec;
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
       else if(this->isvector){
           this->vecdata.push_back(sec);
       }
    }
    void operator+=(char sec){
        if(this->isstring){
            this->sdata += sec;
            return;
        }
        else if(this->isnumeric){
            this->numericdata += sec;
            return;
        }
        else{
            throw(VarException("Invalid usage of addition char operator"));
            return;
        }
        return;
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
        this->vecdata.clear(); // memory leak protection
        this->sdata = ""; //memory leak protection
        this->isnumeric = sec.isnumeric;
        this->isstring = sec.isstring;
        this->numericdata = sec.numericdata;
        this->sdata = sec.sdata;
        this->isvector = sec.isvector;
        this->vecdata = sec.vecdata;
    }
    var operator*(var sec){
        if(!this->isnumeric || sec.isnumeric == false){
            throw(VarException("Multiplication of non numeric types is not yet supoorted!"));
            return 0;
        }
        else{
            return (this->numericdata * sec.numericdata);
        }
        return 0;
    }
    void operator*=(var sec){
        if(!this->isnumeric || sec.isnumeric == false){
            throw(VarException("Multiplication of non numeric types is not yet supoorted!"));
            return;
        }
        else{
            this->numericdata *= sec.numericdata;
            return;
        }
        this->numericdata = 0;
        this->isnumeric = true;
        this->nonetype = false;
        this->isstring = false;
        return;
    }
    var operator/(var sec){
        if(!this->isnumeric || sec.isnumeric == false){
            throw(VarException("Multiplication of non numeric types is not yet supoorted!"));
            return 0;
        }
        else{
            return (this->numericdata / sec.numericdata);
        }
        return 0;
    }
    void operator/=(var sec){
        if(!this->isnumeric || sec.isnumeric == false){
            throw(VarException("Multiplication of non numeric types is not yet supoorted!"));
            return;
        }
        else{
            this->numericdata /= sec.numericdata;
            return;
        }
        this->numericdata = 0;
        this->isnumeric = true;
        this->nonetype = false;
        this->isstring = false;
        return;
    }
    var operator%(var sec){
        if(!this->isnumeric || sec.isnumeric == false){
            throw(VarException("Modulo operator with non numeric types is not supoorted!"));
            return 0;
        }
        else{
            return var(fmodl(this->numericdata, sec.numericdata));
        }
        return 0;

    }
    void operator%=(var sec){
        if(!this->isnumeric || sec.isnumeric == false){
            throw(VarException("Modulo operator with non numeric types is not supoorted!"));
            return;
        }
        else{
            this->numericdata = fmodl(this->numericdata, sec.numericdata);
            return;
        }
        this->numericdata = 0;
        this->isnumeric = true;
        this->nonetype = false;
        this->isstring = false;
        return;
    }
    bool operator==(var sec){
        if(this->numericdata == sec.numericdata && sec.isnumeric == this->isnumeric && sec.isstring == this->isstring && sec.sdata == this->sdata && sec.isvector == this->isvector){
            if(this->isvector && sec.isvector){
                std::vector<var>&ref = this->vecdata;
                std::vector<var>&ref2 = sec.vecdata;
                if(ref.size() != ref2.size()){
                    return false;
                }
                for(size_t i = 0; i<ref.size(); i++){
                    if(!(ref[i] == ref2[i])){
                        return false;
                    }
                }
                return true;
            }
            return true;
        }
        return false;
    }
    void Append(var val){
        if(!this->isvector && this->isstring == false){
            throw(VarException("Appending is only supported by an Array or String!"));
            return;
        }
        if(this->isvector){
            this->vecdata.push_back(val);
        }
        else if(this->isstring){
            this->sdata += val.str();
        }    
    }
    //Used for Arrays, using it for string will return its size not length;
    size_t size(){
        if(this->isvector){
            return this->vecdata.size();
        }
        else if(this->isstring){
            return this->sdata.size();
        }
        else{
            throw(VarException("Size is only supported by an Array or String!"));
            return 0;
        }
    }
    //Used for strings, will return its length;
    size_t length(){
        if(!this->isstring){
            throw(VarException("length is only supported by a String!"));
            return 0;
        }
        else{
            return this->sdata.length();
        }
    }
    std::vector<var>&PureVector(){
        return this->vecdata;
    }
    //[] but for string type []support will be added in future)
    char &StrIndexReference(size_t index){
        if(!this->isstring){
            throw(VarException("length is only supported by a String!"));
        }
        else{
            return this->sdata[index];
        }
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
    bool IsArray(){
        return this->isvector;
    }
    ~var() {
        this->isnumeric = false;
        this->nonetype = false;
        this->isstring = false;
        this->numericdata = false;
        this->sdata = "";
    }
    //only usable []
    template<class Type>
    var& operator[](Type index){
        if(!this->isvector){
            throw(VarException("Operator [] is only supported by Array!"));
        }
        return this->vecdata[index];
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
    else if(val.IsArray()){
        return "Array";
    }
    return "None";
}
std::ostream& operator<<(std::ostream& os, var val) {
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
    else if(val.IsArray()){
        os << val.str();
    }
    else if(val.IsNone()){
        os << "None";
    }
    return os;
}

std::istream& operator>>(std::istream& is, var val) {
    std::string s;
    is >> s;
    if (s == "") {
        val = "";
        return is;
    }
    val = s;
    return is;
}

template<class T>
var VarFromNumeric(T Type){
    return var((long double)Type);
}