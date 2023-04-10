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

mpz_class SlothPermutation::p = mpz_class("170082004324204494273811327264862981553264701145937538369570764779791492622392118654022654452947093285873855529044371650895045691292912712699015605832276411308653107069798639938826015099738961427172366594187783204437869906954750443653318078358839409699824714551430573905637228307966826784684174483831608534979");

bool SlothPermutation::sqrt_mod_p_verify(const mpz_class & y,
  const mpz_class & x,
    const mpz_class & p) {
  mpz_class y_squared = (y * y) % p;
  return y_squared == (x % p);
}

mpz_class SlothPermutation::mod(const mpz_class & x,
  const mpz_class & y) {
  return (x - (x / y) * y);
}

mpz_class SlothPermutation::fast_pow(const mpz_class & base,
  const mpz_class & exponent,
    const mpz_class & modulus) {
  if (modulus == 1) return 0;
  mpz_class result = 1;
  mpz_class b = base % modulus;
  mpz_class exp = exponent;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * b) % modulus;
    }
    exp = exp / 2;
    b = (b * b) % modulus;
  }
  return result;
}

bool SlothPermutation::quad_res(const mpz_class & x) {
  mpz_class exp = (p - 1) / 2;
  return fast_pow(x, exp, p) == 1;
}

mpz_class SlothPermutation::mod_sqrt_op(const mpz_class & x) {
  mpz_class y;
  if (quad_res(x)) {
    mpz_class exp = (p + 1) / 4;
    y = fast_pow(x, exp, p);
  } else {
    mpz_class x_prime = (p - x) % p;
    mpz_class exp = (p + 1) / 4;
    y = fast_pow(x_prime, exp, p);
  }
  return y;
}

mpz_class SlothPermutation::mod_op(const mpz_class & x,
  const mpz_class & t) {
  mpz_class x_mod_p = x % p;
  for (mpz_class i = 0; i < t; i++) {
    x_mod_p = mod_sqrt_op(x_mod_p);
  }
  return x_mod_p;
}

bool SlothPermutation::mod_verif(const mpz_class & y,
  const mpz_class & x,
    const mpz_class & t) {
  mpz_class y_pow = y % p;
  for (mpz_class i = 0; i < t; i++) {
    y_pow = (y_pow * y_pow) % p;
  }
  if (!quad_res(y_pow)) {
    y_pow = (p - y_pow) % p;
  }
  mpz_class x_mod_p = x % p;
  return x_mod_p == y_pow || (p - x_mod_p) % p == y_pow;
}

mpz_class SlothPermutation::generateProofVDF(const mpz_class & t,
  const mpz_class & x) {
  return mod_op(x, t);
}

bool SlothPermutation::verifyProofVDF(const mpz_class & t,
  const mpz_class & x,
    const mpz_class & y) {
  return mod_verif(y, x, t);
}

std::vector < uint8_t > SlothPermutation::generateBufferProofVDF(const mpz_class & t,
  const std::vector < uint8_t > & x, size_t byteLen) {
  std::vector < uint8_t > ret(byteLen, 0);
  writeBigUIntLE(mod_op(readBigUIntLE(x, byteLen), t), ret, byteLen);
  return ret;
}

bool SlothPermutation::verifyBufferProofVDF(const mpz_class & t,
  const std::vector < uint8_t > & x,
    const std::vector < uint8_t > & y, size_t byteLen) {
  return mod_verif(readBigUIntLE(y, byteLen), readBigUIntLE(x, byteLen), t);
}

mpz_class SlothPermutation::readBigUIntLE(const std::vector < uint8_t > & buffer, size_t byteLen, size_t offset) {
  if (offset + byteLen > buffer.size()) {
    throw std::out_of_range("Out of bounds");
  }

  mpz_class result = 0;

  for (size_t i = 0; i < byteLen; i++) {
    mpz_class tmp = mpz_class(buffer[offset + i]);
    tmp *= (mpz_class(1) << mpz_class(i * 8));
    result += tmp;
  }

  return result;
}

void SlothPermutation::writeBigUIntLE(const mpz_class & x, std::vector < uint8_t > & buffer, size_t byteLen, size_t offset) {
  if (offset + byteLen > buffer.size()) {
    throw std::out_of_range("Out of bounds");
  }
  mpz_class y = x;
  mpz_class big256 = 256;

  for (size_t i = 0; i < byteLen; i++) {
    buffer[offset + i] = static_cast < uint8_t > (mpz_class(y % big256).get_ui());
    y >>= 8;
  }
}
