#pragma once
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cinttypes>
#include <iostream>
#include <vector>
#include <stdexcept>

const size_t kNumberOfBits = 2022;

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
        while (!digits_.empty() && digits_.front() == '0') {
            digits_ = digits_.substr(1);
        }

        if (digits_.empty()) {
            digits_ = "0";
        }

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

    bool operator<(const BigInteger& other) const {
        if (size() == other.size()) {
            for (size_t i = 0; i < size(); ++i) {
                int cur_digit = get_digit(i);
                int other_cur_digit = other.get_digit(i);

                if (cur_digit == other_cur_digit) {
                    continue;
                }
                
                return cur_digit < other_cur_digit;
            }

            return false;
        }

        return size() < other.size();
    }

    bool operator==(const BigInteger& other) const {
        if (size() == other.size()) {
            for (size_t i = 0; i < size(); ++i) {
                if (get_digit(i) != other.get_digit(i)) {
                    return false;
                }
            }

            return true;
        }

        return false;
    }

    bool operator>(const BigInteger& other) const {
        if (size() == other.size()) {
            for (size_t i = 0; i < size(); ++i) {
                int cur_digit = get_digit(i);
                int other_cur_digit = other.get_digit(i);

                if (cur_digit == other_cur_digit) {
                    continue;
                }
                
                return cur_digit > other_cur_digit;
            }

            return false;
        }

        return size() > other.size();
    }

    bool operator!=(const BigInteger& other) {
        return !((*this) == other);
    }

    void multiply_by_ten() {
        digits_ += "0";
        ++length_;
    }

    BigInteger operator+(const BigInteger& other) {
        size_t a_size = size();
        size_t b_size = other.size();
        size_t max_size = std::max(a_size, b_size);
        std::string result;
        unsigned short carry = 0;

        for (size_t i = 0; i < max_size; ++i) {
            unsigned short digit_sum = 100;

            if (i >= a_size) {
                digit_sum = other.get_digit(b_size - 1 - i);
            } else if (i >= b_size) {
                digit_sum = get_digit(a_size - 1 - i);
            } else {
                digit_sum = get_digit(a_size - 1 - i) + other.get_digit(b_size - 1 - i);
            }

            assert(digit_sum < 100);

            digit_sum += carry;
            result += std::to_string(digit_sum % 10);
            carry = digit_sum / 10;
        }

        if (carry > 0) {
            result += std::to_string(carry);
        }

        std::reverse(result.begin(), result.end());

        return BigInteger(result);
    }

    BigInteger operator-(const BigInteger& other) {
        // assume that current value >= other value, because this operation
        // will be used only in these cases

        assert(!(*this < other)); 

        size_t a_size = size();
        size_t b_size = other.size();
        std::string result;
        unsigned short carry = 0;

        for (size_t i = 0; i < a_size; ++i) {
            unsigned short subtract = carry;
            carry = 0;

            if (i < b_size) {
                subtract += other.get_digit(b_size - 1 - i);
            }

            short add_to_result = get_digit(a_size - 1 - i) - subtract;

            if (add_to_result < 0) {
                carry = 1;
                add_to_result += 10;
            }

            assert(add_to_result >= 0);

            result += std::to_string(add_to_result);
        }

        std::reverse(result.begin(), result.end());

        return BigInteger(result);
    }

    BigInteger operator*(const unsigned short k) {
        assert(k < 10);

        if (k == 0 || get_string() == "0") {
            return BigInteger("0");
        }
        
        std::string result;
        unsigned short carry = 0;

        for (size_t i = 0; i < length_; ++i) {
            unsigned short digit = get_digit(length_ - 1 - i);
            unsigned short add_to_result = digit * k + carry;
            
            result += std::to_string(add_to_result % 10);
            carry = add_to_result / 10;
        }

        if (carry > 0) {
            result += std::to_string(carry);
        }

        std::reverse(result.begin(), result.end());
        
        return BigInteger(result);
    }

    BigInteger operator*(const BigInteger& other) {
        if (get_string() == "0" || other.get_string() == "0") {
            return BigInteger("0");
        }

        std::vector<BigInteger> to_sum;
        unsigned zeros = 0;
        
        for (size_t i = 0; i < other.size(); ++i) {
            to_sum.emplace_back((*this) * other.get_digit(i));
            
            for (size_t _ = 0; _ < zeros; ++_) {
                to_sum.back().multiply_by_ten();
            }

            ++zeros;
        }

        BigInteger sum = to_sum.front();

        for (size_t i = 1; i < to_sum.size(); ++i) {
            sum = sum + to_sum[i];
        }

        return sum;
    }

    BigInteger operator/(const unsigned short k) {
        if (k == 0) {
            throw std::overflow_error("Dividing by zero");
        }

        std::string result;
        unsigned short buff = 0;

        for (size_t i = 0; i < size(); ++i) {
            buff = buff * 10 + get_digit(i);
            
            if (buff < k) {
                if (!result.empty()) {
                    result += "0";
                }

                continue;
            }

            result += std::to_string(buff / k);
            buff %= k;
        }

        if (result.empty()) {
            result = "0";
        }

        return BigInteger(result);
    }

    BigInteger to_binary() {
        std::string result;
        BigInteger current = *this;
        BigInteger endpoint = BigInteger("0");

        while (current != endpoint) {
            BigInteger division_result = current / 2;
            BigInteger remaining = current - division_result * 2;
            result += remaining.get_string();
            current = division_result;
        }

        std::reverse(result.begin(), result.end());

        return result;
    }
private:
    std::string digits_;
    size_t length_;
};

struct uint2022_t {
    std::bitset<kNumberOfBits> bits;
    // reserved some more bits for handling integer overflow

    uint2022_t();
    uint2022_t(uint32_t x);
    uint2022_t(const char* buff);
    uint2022_t(const std::bitset<kNumberOfBits>& _bits);
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

std::ostream& operator<<(std::ostream& stream, const BigInteger& value);
