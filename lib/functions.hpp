#include <string>
#include <sstream>
#include <fstream>

template <typename T>
std::string to_hex(T num)
{
    std::stringbuf buf;
    std::ostream os(&buf);

    os << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2)
       << std::hex << num;

    return buf.str().c_str();
}