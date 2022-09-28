#include "number.h"

uint2022_t::uint2022_t() {}

uint2022_t::uint2022_t(uint32_t x) {
    for (size_t bit = 0; bit < 32; ++bit) {
        if ((x >> bit) & 1) {
            bits.set(bit);
        }
    }
}

uint2022_t::uint2022_t(const char* buff) {
    std::string input_bits = BigInteger(buff).to_binary().get_string();
    size_t input_length = input_bits.size();
    
    for (size_t i = 0; i < input_length; ++i) {
        if (input_bits[i] == '1') {
            bits.set(input_length - 1 - i);
        }
    }
}

uint2022_t::uint2022_t(const std::bitset<kNumberOfBits>& _bits) {
    bits = _bits;
}

uint2022_t from_uint(uint32_t i) {
    return uint2022_t(i);
}

uint2022_t from_string(const char* buff) {
    return uint2022_t(buff);
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    std::bitset<kNumberOfBits> result;
    unsigned short carry = 0;

    for (size_t i = 0; i < kNumberOfBits; ++i) {
        unsigned short new_carry = 0;
        unsigned short sum_value = lhs.bits[i] + rhs.bits[i] + carry;

        if (sum_value > 1) {
            new_carry = 1;
        }

        result.set(i, lhs.bits[i] ^ rhs.bits[i] ^ carry);
        carry = new_carry;
    }

    return uint2022_t(result);
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t extra = rhs;
    
    extra.bits.flip();
    extra = extra + uint2022_t(1);

    return uint2022_t(lhs + extra);
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

std::string convert_to_string(const uint2022_t& x) {
    BigInteger converted;
    BigInteger power_of_2 = BigInteger("1");

    for (size_t i = 0; i < kNumberOfBits; ++i) {
        if (x.bits[i]) {
            converted = converted + power_of_2;
        }

        power_of_2 = power_of_2 * 2;
    }

    return converted.get_string();
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    stream << convert_to_string(value);

    return stream;
}

std::ostream& operator<<(std::ostream& stream, const BigInteger& value) {
    stream << value.get_string();
    return stream;
}
