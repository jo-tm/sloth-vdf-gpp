#include <iostream>
#include <cassert>
#include <cstdint>
#include <gmpxx.h>
#include "SlothPermutation.h"

void test_VDF01() {
    SlothPermutation sloth;
    mpz_class x = 10;
    sloth.setP("23");
    x = x % sloth.getP();
    mpz_class t = 50;
    mpz_class y = sloth.generateProofVDF(t, x);
    bool verified = sloth.verifyProofVDF(t, x, y);
    assert(verified);
}

// Add the other tests here

int main() {
    test_VDF01();
    // Call the other test functions here

    std::cout << "All tests passed." << std::endl;
    return 0;
}
