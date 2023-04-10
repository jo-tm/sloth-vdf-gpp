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

    // Generate buffer proof
    std::vector<uint8_t> x_buffer(16, 0);
    sloth.writeBigUIntLE(x, x_buffer, 16);
    std::vector<uint8_t> y_buffer = sloth.generateBufferProofVDF(t, x_buffer, 16);

    // Verify buffer proof
    bool buffer_result = sloth.verifyBufferProofVDF(t, x_buffer, y_buffer, 16);
    std::cout << "Buffer verification result: " << (buffer_result ? "true" : "false") << std::endl;

    return 0;
}
