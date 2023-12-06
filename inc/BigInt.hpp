#pragma once

#include <cstdint>
#include <ostream>

class BigInt
{
public:
  BigInt();
  BigInt(int64_t);
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

  BigInt &operator/=(const int64_t &);
  BigInt operator/(const int64_t &) const;

  BigInt &operator%=(const uint64_t &);
  BigInt operator%(const uint64_t &) const;

  bool operator>(const BigInt &) const;
  bool operator>=(const BigInt &) const;
  bool operator==(const BigInt &) const;
  bool operator!=(const BigInt &) const;
  bool operator<(const BigInt &) const;
  bool operator<=(const BigInt &) const;

  std::string to_string(const uint64_t &base) const;

private:
  const static uint64_t base_ = 1e9;
  const static uint64_t size_ = 1000;

  int64_t digit_[size_];
};