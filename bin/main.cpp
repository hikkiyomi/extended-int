#include <iostream>
#include <lib/number.h>

int main() {
    // uint2022_t value;
    // std::cout << value << std::endl;

    BigInteger x("41528612387617284612987624123412");
    BigInteger y("51872678967867861211111111111111111");

    std::cout << x << std::endl;
    std::cout << y << std::endl;

    BigInteger sum = x + y;
    std::cout << sum << std::endl;

    return 0;
}
