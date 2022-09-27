#include "number.h"

uint2022_t::uint2022_t() {}

uint2022_t::uint2022_t(uint32_t x) {
    for (size_t bit = 0; bit < 32; ++bit)
        if ((x >> bit) & 1)
            bits.set(bit);
}

uint2022_t::uint2022_t(const char* buff) {

}

uint2022_t from_uint(uint32_t i) {
    return uint2022_t(i);
}

uint2022_t from_string(const char* buff) {
    return uint2022_t();
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    return false;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return false;
}

char* to_string(const uint2022_t& x) {
    // TODO
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    stream << "Implement me";

    return stream;
}