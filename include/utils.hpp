#include <string>
#include <sstream>
namespace LIRA{
namespace Utils{
template<typename T>
T to_numeric(const std::string& str, bool allow_hex = false, bool allow_binary = false) {
    //TODO:Write it properly to handle hex and stuff in future. And also give error if we get float in integer and all that
    std::istringstream iss(str);
    T num;
    iss >> num;
    if (iss.fail()) {
        throw std::invalid_argument("Invalid numeric string: " + str);
    }
    return num;
}
}
}