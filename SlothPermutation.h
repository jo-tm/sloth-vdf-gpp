#include <iostream>

#include <gmpxx.h>

#include <cstdint>

#include <vector>

class SlothPermutation {
  public:
    // Parameters
    static mpz_class p;

  bool sqrt_mod_p_verify(const mpz_class & y,
    const mpz_class & x,
      const mpz_class & p);
  mpz_class mod(const mpz_class & x,
    const mpz_class & y);
  mpz_class fast_pow(const mpz_class & base,
    const mpz_class & exponent,
      const mpz_class & modulus);
  bool quad_res(const mpz_class & x);
  mpz_class mod_sqrt_op(const mpz_class & x);
  mpz_class mod_op(const mpz_class & x,
    const mpz_class & t);
  bool mod_verif(const mpz_class & y,
    const mpz_class & x,
      const mpz_class & t);
  mpz_class generateProofVDF(const mpz_class & t,
    const mpz_class & x);
  bool verifyProofVDF(const mpz_class & t,
    const mpz_class & x,
      const mpz_class & y);
  std::vector < uint8_t > generateBufferProofVDF(const mpz_class & t,
    const std::vector < uint8_t > & x, size_t byteLen = 128);
  bool verifyBufferProofVDF(const mpz_class & t,
    const std::vector < uint8_t > & x,
      const std::vector < uint8_t > & y, size_t byteLen = 128);
  mpz_class readBigUIntLE(const std::vector < uint8_t > & buffer, size_t byteLen, size_t offset = 0);
  void writeBigUIntLE(const mpz_class & x, std::vector < uint8_t > & buffer, size_t byteLen, size_t offset = 0);
};
