#include "number.h"

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

    bool operator!=(const BigInteger& other) const {
        return !((*this) == other);
    }

    void multiply_by_ten() {
        digits_ += "0";
        ++length_;
    }

    BigInteger operator+(const BigInteger& other) const {
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

    BigInteger operator-(const BigInteger& other) const {
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

    BigInteger operator*(const unsigned short k) const {
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

    BigInteger operator*(const BigInteger& other) const {
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

uint2022_t::uint2022_t(const std::bitset<kNumberOfBits>& _bits) 
    : bits(_bits)
{}

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
    uint2022_t flipped_rhs = rhs;
    
    flipped_rhs.bits.flip();
    flipped_rhs = flipped_rhs + uint2022_t(1);

    return uint2022_t(lhs + flipped_rhs);
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t result;

    for (size_t i = 0; i < kNumberOfBits; ++i) {
        if (lhs.bits[i] == 1) {
            uint2022_t to_sum = rhs;

            to_sum = to_sum << i;
            result = result + to_sum;
        }
    }

    return result;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (rhs.bits.none()) {
        throw std::overflow_error("Dividing by zero");
    }

    uint2022_t result;
    uint2022_t current_buffer;

    for (size_t i = 0; i < kNumberOfBits; ++i) {
        current_buffer = (current_buffer << 1) + uint2022_t(lhs.bits[kNumberOfBits - 1 - i]);
        result = result << 1;
        
        if (current_buffer < rhs) {
            continue;
        }

        result = result + uint2022_t(1);
        current_buffer = current_buffer - rhs;
    }

    return result;
}

uint2022_t operator%(const uint2022_t& lhs, const uint2022_t& rhs) {
    if (lhs < rhs) {
        return lhs;
    }

    return lhs - (lhs / rhs) * rhs;
}

uint2022_t operator<<(const uint2022_t& lhs, const size_t rhs) {
    if (kNumberOfBits <= rhs) {
        return uint2022_t();
    }
    
    std::bitset<kNumberOfBits> result;

    for (size_t i = rhs; i < kNumberOfBits; ++i) {
        result.set(i, lhs.bits[i - rhs]);
    }

    return uint2022_t(result);
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < kNumberOfBits; ++i) {
        if (lhs.bits[kNumberOfBits - 1 - i] == rhs.bits[kNumberOfBits - 1 - i]) {
            continue;
        }

        if (lhs.bits[kNumberOfBits - 1 - i] < rhs.bits[kNumberOfBits - 1 - i]) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (size_t i = 0; i < kNumberOfBits; ++i) {
        if (lhs.bits[kNumberOfBits - 1 - i] == rhs.bits[kNumberOfBits - 1 - i]) {
            continue;
        }

        if (lhs.bits[kNumberOfBits - 1 - i] > rhs.bits[kNumberOfBits - 1 - i]) {
            return true;
        } else {
            return false;
        }
    }

    return false;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    return lhs.bits == rhs.bits;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
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
