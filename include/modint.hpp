#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>

namespace akTARDIGRADE13 {

template <std::uint_fast64_t Modulus> struct modint {

public:
  modint();
  modint(const std::int_fast64_t _val);
  std::uint_fast64_t value() const;

  modint operator+(const modint rhs) { return modint(*this) += rhs; }
  modint operator-(const modint rhs) { return modint(*this) -= rhs; }
  modint operator*(const modint rhs) { return modint(*this) *= rhs; }
  modint operator/(const modint rhs) { return modint(*this) /= rhs; }
  modint &operator+=(const modint rhs) {
    val += rhs.val;
    if (val >= Modulus) {
      val -= Modulus;
    }
    return *this;
  }
  modint &operator-=(const modint rhs) {
    if (val < rhs.val) {
      val += Modulus;
    }
    val -= rhs.val;
    return *this;
  }
  modint &operator*=(const modint rhs) {
    val = val * rhs.val % Modulus;
    return *this;
  }
  modint &operator/=(modint rhs) {
    std::uint_fast64_t exp = Modulus - 2;
    while (exp) {
      if (exp & 1) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp >>= 1;
    }
    return *this;
  }
  modint &operator++() {
    val++;
    if (val == Modulus)
      val = 0;
    return *this;
  }
  modint &operator--() {
    if (val == 0)
      val = Modulus;
    val--;
    return *this;
  }
  modint operator++(int) {
    modint result = *this;
    ++*this;
    return result;
  }
  modint operator--(int) {
    modint result = *this;
    --*this;
    return result;
  }
  modint operator+() const { return *this; }
  modint operator-() const { return modint() - *this; }
  modint pow(long long n) const {
    assert(0 <= n);
    modint x = *this, r = 1;
    while (n) {
      if (n & 1)
        r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  modint inv() const { return pow(Modulus - 2); }
  friend bool operator==(const modint &lhs, const modint &rhs) {
    return lhs.value() == rhs.value();
  }
  friend bool operator!=(const modint &lhs, const modint &rhs) {
    return lhs.value() != rhs.value();
  }

  friend std::istream &operator>>(std::istream &is, modint<Modulus> &value) {
    std::int_fast64_t input;
    is >> input;
    value = modint<Modulus>(input);
    return is;
  }

  friend std::ostream &operator<<(std::ostream &os, const modint<Modulus> &op) {
    os << op.value();
    return os;
  }

private:
  std::uint_fast64_t val;
};

template <std::uint_fast64_t Modulus> modint<Modulus>::modint() : val(0){};

template <std::uint_fast64_t Modulus>
modint<Modulus>::modint(const std::int_fast64_t _val)
    : val((_val % (std::int_fast64_t)Modulus + Modulus) % Modulus) {}

template <std::uint_fast64_t Modulus>
std::uint_fast64_t modint<Modulus>::value() const {
  return val;
}

using modint998244353 = modint<998244353ul>;
using modint1000000007 = modint<1000000007ul>;

} // namespace akTARDIGRADE13