#include <iostream>
#include <cassert>
#include <cstdint>
#include <gmpxx.h>
#include "SlothPermutation.h"

void test_VDF01() {
    SlothPermutation sloth;
    mpz_class x = 10;
    SlothPermutation::p = mpz_class("23");
    x = x % SlothPermutation::p;
    mpz_class t = 50;
    mpz_class y = sloth.generateProofVDF(t, x);
    bool verified = sloth.verifyProofVDF(t, x, y);
    assert(verified);
}

void test_VDF02() {
    SlothPermutation sloth;
    mpz_class x("808080818080808080818080");
    SlothPermutation::p = mpz_class("73237431696005972674723595250817150843");
    x = x % SlothPermutation::p;
    mpz_class t = 2000;
    mpz_class y = sloth.generateProofVDF(t, x);
    bool verified = sloth.verifyProofVDF(t, x, y);
    assert(verified);
}


void test_VDF03() {
    mpz_class x = (mpz_class(0x789acdef) << 32) + mpz_class(0x06543210);
    SlothPermutation sloth;

    std::vector<uint8_t> buf(8);
    sloth.writeBigUIntLE(x, buf, 8);
    mpz_class y = sloth.readBigUIntLE(buf, 8);

    assert(x == y);
}

void test_VDF04() {
    mpz_class x = (mpz_class(0x789acdef) << 32) + mpz_class(0x06543210);
    SlothPermutation sloth;

    std::vector<uint8_t> buf(8);

    sloth.writeBigUIntLE(x, buf, 8);
    mpz_class y = sloth.readBigUIntLE(buf, 8);

    assert(x == y);
}

void test_VDF05() {
    mpz_class x = (mpz_class(0x789acdef) << 32) + mpz_class(0x06543210);
    x = x + (x << 64);
    SlothPermutation sloth;

    std::vector<uint8_t> buf(16);

    sloth.writeBigUIntLE(x, buf, 16);
    mpz_class y = sloth.readBigUIntLE(buf, 16);

    assert(x == y);
}

void test_VDF06() {
    const std::string challenge_str = "137010851887946622574152571239132315287";
    const std::string prime_str = "297010851887946822574352571639152315287";
    const int size = 16;
    mpz_class t("200");
    SlothPermutation sloth;
    SlothPermutation::p = mpz_class(prime_str, 10);
    mpz_class challenge;
    challenge.set_str(challenge_str, 10);

    // Determine the number of bytes needed to represent the integer
    size_t numBytes = mpz_size(challenge.get_mpz_t());

    // Allocate a byte array to hold the integer
    std::vector<uint8_t> myBytes(size+1);

    // Export the integer to the byte array
    mpz_export(myBytes.data(), nullptr, 1, 1, 0, 0, challenge.get_mpz_t());
    
    std::vector<uint8_t> proof = sloth.generateBufferProofVDF(t, myBytes, size);
    bool verified = sloth.verifyBufferProofVDF(t, myBytes, proof, size);
    assert(verified);
}

void test_VDF07() {
    const std::string challenge_str = "c8774beca835214089860e8b01157c6c883c70f4a25e83d190b577f7f56bcfd3";
    const std::string prime_str = "64106875808534963770974826322234655855469213855659218736479077548818158667371";
    const int size = 16;
    mpz_class t("200");
    SlothPermutation sloth;
    SlothPermutation::p = mpz_class(prime_str, 10);
    mpz_class challenge;
    challenge.set_str(challenge_str, 10);

    // Determine the number of bytes needed to represent the integer
    size_t numBytes = mpz_size(challenge.get_mpz_t());

    // Allocate a byte array to hold the integer
    std::vector<uint8_t> myBytes(size);

    // Export the integer to the byte array
    mpz_export(myBytes.data(), nullptr, 1, 1, 0, 0, challenge.get_mpz_t());

    std::vector<uint8_t> proof = sloth.generateBufferProofVDF(t, myBytes, size);
    bool verified = sloth.verifyBufferProofVDF(t, myBytes, proof, size);
    assert(verified);
}

void test_VDF08() {
    std::vector<uint8_t> challenge = {0x13, 0x70, 0x10, 0x85, 0x18, 0x87, 0x94, 0x66, 0x22, 0x57, 0x41, 0x52, 0x71, 0x23, 0x91, 0x32, 0x31, 0x52, 0x87};
    const mpz_class t = 200;
    SlothPermutation sloth;
    SlothPermutation::p = mpz_class("297010851887946822574352571639152315287");
    std::vector<uint8_t> proof = sloth.generateBufferProofVDF(t, challenge, 16);
    bool verified = sloth.verifyBufferProofVDF(t, challenge, proof, 16);
    assert(verified);
}

void test_VDF09() {
    std::vector<uint8_t> challenge = {0xc8, 0x77, 0x4b, 0xec, 0xa8, 0x35, 0x21, 0x40, 0x89, 0x86, 0x0e, 0x8b, 0x01, 0x15, 0x7c, 0x6c, 0x88, 0x3c, 0x70, 0xf4, 0xa2, 0x5e, 0x83, 0xd1, 0x90, 0xb5, 0x77, 0xf7, 0xf5, 0x6b, 0xcf, 0xd3};
    const mpz_class t = 200;
    SlothPermutation sloth;
    SlothPermutation::p = mpz_class("64106875808534963770974826322234655855469213855659218736479077548818158667371");
    std::vector<uint8_t> proof = sloth.generateBufferProofVDF(t, challenge, 32);
    bool verified = sloth.verifyBufferProofVDF(t, challenge, proof, 32);
    assert(verified);
}




// Add the other tests here

int main() {
    test_VDF01();
    test_VDF02();
    test_VDF03();
    test_VDF04();
    test_VDF05();
    test_VDF06();
    test_VDF07();
    test_VDF08();
    test_VDF09();

    std::cout << "All tests passed." << std::endl;
    return 0;
}
