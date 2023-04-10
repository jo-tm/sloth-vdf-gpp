#include <iostream>
#include <vector>
#include "SlothPermutation.h"

int main() {
    SlothPermutation sloth;
    mpz_class t = 1000;
    mpz_class x("12345678901234567890");
    mpz_class y;

    // Generate proof
    y = sloth.generateProofVDF(t, x);
    std::cout << "Generated proof: " << y << std::endl;

    // Verify proof
    bool result = sloth.verifyProofVDF(t, x, y);
    std::cout << "Verification result: " << (result ? "true" : "false") << std::endl;

    return 0;
}
