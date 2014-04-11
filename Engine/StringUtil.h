#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <string>
#include <sstream>
#include <typeinfo>
namespace engine{
template<typename T>
std::string convertToStdString(T val){
    std::stringstream s;
    s << val;
    std::string out;
    s >> out;
    return out;
}
template<typename T>
T convertFromStdString(std::string str){
    std::stringstream s;
    s << str;
    T out;
    s >> out;
    if(s.good()==false)
        throw std::bad_cast();
    return out;
}
}

#endif /* STRINGUTIL_H */
