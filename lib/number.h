#pragma once

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cinttypes>
#include <iostream>
#include <stdexcept>
#include <vector>

const size_t kNumberOfBits = 2022;

struct uint2022_t {
    std::bitset<kNumberOfBits> bits;

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

uint2022_t operator%(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator<<(const uint2022_t& lhs, const size_t rhs);

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator>(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);

std::istream& operator>>(std::istream& stream, uint2022_t& value);
