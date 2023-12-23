#pragma once
#include "BigInt.hpp"
class BigFraction
{
public:
    BigFraction();
    BigFraction(const uint64_t &);
    BigFraction(const BigInt &);
    BigFraction(const BigFraction &);
    BigFraction(const uint64_t &, std::string);
    BigFraction &operator=(const BigFraction &);
    BigFraction &operator+=(const BigFraction &);
    BigFraction operator+(const BigFraction &) const;
    BigFraction &operator++();
    BigFraction &operator-=(const BigFraction &);
    BigFraction operator-(const BigFraction &) const;
    BigFraction &operator--();
    BigFraction &operator*=(const BigFraction &);
    BigFraction operator*(const BigFraction &) const;
    BigFraction &operator/=(const BigFraction &);
    BigFraction operator/(const BigFraction &) const;
    bool operator>(const BigFraction &) const;
    bool operator>=(const BigFraction &) const;
    bool operator==(const BigFraction &) const;
    bool operator!=(const BigFraction &) const;
    bool operator<(const BigFraction &) const;
    bool operator<=(const BigFraction &) const;
    std::string toString(const uint64_t &) const;

private:
    BigInt numerator_ = 0,
           denominator_ = 1;
    uint64_t precision_ = 1e10;
    void reduce();
    void readPeriod(uint64_t, std::string);
};