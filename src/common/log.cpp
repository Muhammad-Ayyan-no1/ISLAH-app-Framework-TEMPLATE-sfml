#include <string>
#include <iostream>
void LOG_custom(std::string Prestr, std::string str)
{
    // TODO use a proper UI   stuff   this is just for during development
    std::cout << Prestr << ": " << str;
}