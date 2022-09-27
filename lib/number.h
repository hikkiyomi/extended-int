#pragma once
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cinttypes>
#include <iostream>

class BigInteger {
    static char to_char(unsigned short i) {
        return char('0' + i);
    }
public:
    BigInteger()
        : digits_("0")
    {
        length_ = 1;
    }

    BigInteger(const char* buff)
        : digits_(buff)
    {
        length_ = digits_.size();
    }

    BigInteger(const std::string& buff)
        : digits_(buff)
    {
        length_ = digits_.size();
    }

    std::string get_string() const {
        return digits_;
    }

    unsigned short get_digit(size_t index) const {
        return digits_[index] - '0';
    }

    size_t size() const {
        return length_;
    }

    BigInteger operator+(const BigInteger& other) {
        size_t a_size = size(), b_size = other.size();
        size_t sum_length = std::max(a_size, b_size) + 1;
        std::string sum;
        unsigned short carry = 0;

        for (size_t i = 0; i < sum_length; ++i) {
            unsigned short digit_sum = 100;

            if (i >= size() && i >= other.size()) {
                if (carry != 0) {
                    sum += '1';
                }

                continue;
            } else if (i >= size()) {
                digit_sum = other.get_digit(b_size - i - 1);
            } else if (i >= other.size()) {
                digit_sum = get_digit(a_size - i - 1);
            } else {
                digit_sum = get_digit(a_size - i - 1) + other.get_digit(b_size - i - 1);
            }

            assert(digit_sum != 100);

            digit_sum += carry;
            sum += std::string(1, to_char(digit_sum % 10));
            carry = digit_sum / 10;
        }

        std::reverse(sum.begin(), sum.end());

        return BigInteger(sum);
    }
private:
    std::string digits_;
    size_t length_;
};

struct uint2022_t {
    std::bitset<2100> bits; // reserved some bits for handling integer overflow

    uint2022_t();
    uint2022_t(uint32_t x);
    uint2022_t(const char* buff);
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);

char* to_string(const uint2022_t& x);

std::ostream& operator<<(std::ostream& stream, const BigInteger& value);