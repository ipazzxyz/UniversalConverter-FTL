#pragma once
#include <cstdint>
#include <ostream>
class BigInt // formally it is BigUInt
{
public:
  BigInt();
  BigInt(uint64_t);
  BigInt(const BigInt &);
  BigInt(const uint64_t &, const std::string &);
  BigInt &operator=(const BigInt &);
  BigInt &operator+=(const BigInt &);
  BigInt operator+(const BigInt &) const;
  BigInt &operator++();
  BigInt &operator-=(const BigInt &);
  BigInt operator-(const BigInt &) const;
  BigInt &operator--();
  BigInt &operator*=(const BigInt &);
  BigInt operator*(const BigInt &) const;
  BigInt &operator/=(const BigInt &);
  BigInt operator/(const BigInt &) const;
  BigInt &operator%=(const BigInt &);
  BigInt operator%(const BigInt &) const;
  bool operator>(const BigInt &) const;
  bool operator>=(const BigInt &) const;
  bool operator==(const BigInt &) const;
  bool operator!=(const BigInt &) const;
  bool operator<(const BigInt &) const;
  bool operator<=(const BigInt &) const;
  BigInt pow(const BigInt &) const;
  std::string toString(const uint64_t &) const;
  friend BigInt getMid(const BigInt &, const BigInt &);

private:
  const static uint64_t base_ = 1e9, size_ = 5e1;
  uint64_t digit_[size_];
  void validateBrackets(const std::string &) const;
};
BigInt gcd(BigInt, BigInt);
BigInt lcd(BigInt, BigInt);
