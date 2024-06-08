#include "bigfraction.hpp"
#include <iostream>
#include <map>
BigFraction::BigFraction() {}
BigFraction::BigFraction(const uint64_t &x) { numerator_ = x; }
BigFraction::BigFraction(const BigInt &x) { numerator_ = x; }
BigFraction::BigFraction(const BigFraction &other)
{
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;
}
BigFraction::BigFraction(const uint64_t &base, std::string number)
{
  if (base < 2)
  {
    throw std::runtime_error("Base should be greater than or equal to 2");
  }
  size_t q = number.find('(');
  if (q != std::string::npos)
  {
    readPeriod(base, number.substr(q + 1));
  }
  for (int64_t i = (q == std::string::npos ? number.size() - 1 : q - 1); i >= 0;
       --i)
  {
    BigFraction digit = 0;
    if (isdigit(number[i]))
    {
      digit = number[i] - '0';
    }
    else if (isalpha(number[i]))
    {
      digit = std::toupper(number[i]) - 'A' + 10;
    }
    else if (number[i] == ']')
    {
      if ((i) && number[i - 1] == '[')
      {
        throw std::runtime_error(std::to_string(i + 1) + ": Empty brackets");
      }
      int j = 0;
      while (number[--i] != '[')
      {
        if (number[i] > '9' || number[i] < '0')
        {
          throw std::runtime_error(std::to_string(i + 1) +
                                   ": Not a '0'...'9' in brackets");
        }
        if (j == 0)
        {
          digit += number[i] - '0';
        }
        else if (j == 1)
        {
          digit += 10 * (number[i] - '0');
        }
        else if (j == 2)
        {
          digit += 100 * (number[i] - '0');
        }
        else
        {
          throw std::runtime_error(
              std::to_string(number.size() - i) +
              ": It is impossible to represent a digit in base");
        }
        ++j;
      }
    }
    if (digit >= base)
    {
      throw std::runtime_error(
          std::to_string(number.size() - i) +
          ": It is impossible to represent a digit in base");
    }
    if (i != number.size() - 1)
    {
      *this /= base;
    }
    *this += digit;
  }
  *this /= base;
}
BigFraction &BigFraction::operator=(const BigFraction &other)
{
  numerator_ = other.numerator_;
  denominator_ = other.denominator_;
  reduce();
  return *this;
}
BigFraction &BigFraction::operator+=(const BigFraction &other)
{
  numerator_ =
      numerator_ * other.denominator_ + denominator_ * other.numerator_;
  denominator_ *= other.denominator_;
  reduce();
  return *this;
}
BigFraction BigFraction::operator+(const BigFraction &other) const
{
  BigFraction result(*this);
  result += other;
  return result;
}
BigFraction &BigFraction::operator++()
{
  numerator_ += denominator_;
  return *this;
}
BigFraction &BigFraction::operator-=(const BigFraction &other)
{
  numerator_ =
      numerator_ * other.denominator_ - denominator_ * other.numerator_;
  denominator_ *= other.denominator_;
  reduce();
  return *this;
}
BigFraction BigFraction::operator-(const BigFraction &other) const
{
  BigFraction result(*this);
  result -= other;
  return result;
}
BigFraction &BigFraction::operator--()
{
  numerator_ -= denominator_;
  return *this;
}
BigFraction &BigFraction::operator*=(const BigFraction &other)
{
  numerator_ *= other.numerator_;
  denominator_ *= other.denominator_;
  reduce();
  return *this;
}
BigFraction BigFraction::operator*(const BigFraction &other) const
{
  BigFraction result(*this);
  result *= other;
  return result;
}
BigFraction &BigFraction::operator/=(const BigFraction &other)
{
  numerator_ *= other.denominator_;
  denominator_ *= other.numerator_;
  reduce();
  return *this;
}
BigFraction BigFraction::operator/(const BigFraction &other) const
{
  BigFraction result(*this);
  result /= other;
  return result;
}
bool BigFraction::operator>(const BigFraction &other) const
{
  BigInt denominator = lcd(denominator_, other.denominator_);
  return denominator / denominator_ * numerator_ >
         denominator / other.denominator_ * other.numerator_;
}
bool BigFraction::operator>=(const BigFraction &other) const
{
  return !(*this < other);
}
bool BigFraction::operator==(const BigFraction &other) const
{
  return !(*this > other) && !(*this < other);
}
bool BigFraction::operator!=(const BigFraction &other) const
{
  return !(*this == other);
}
bool BigFraction::operator<(const BigFraction &other) const
{
  BigInt denominator = lcd(denominator_, other.denominator_);
  return denominator / denominator_ * numerator_ <
         denominator / other.denominator_ * other.numerator_;
}
bool BigFraction::operator<=(const BigFraction &other) const
{
  return !(*this > other);
}
std::string BigFraction::toString(const uint64_t &base) const
{
  std::string result;
  if (*this >= 1)
  {
    return "+";
  }
  BigFraction tmp(*this);
  std::map<BigFraction, uint64_t> seen;
  for (uint64_t i = 1; seen[tmp] == 0 && i < precision_; ++i)
  {
    seen[tmp] = i;
    tmp *= base;
    BigInt q = tmp.numerator_ / tmp.denominator_;
    result += (q).toString(base);
    tmp.numerator_ %= tmp.denominator_;
  }
  if (tmp == 0)
  {
    result.pop_back();
  }
  else
  {
    result.insert(seen[tmp] - 1, "(");
    result.push_back(')');
  }
  return result;
}
void BigFraction::reduce()
{
  BigInt divisor = gcd(numerator_, denominator_);
  numerator_ /= divisor;
  denominator_ /= divisor;
}
void BigFraction::readPeriod(uint64_t base, std::string number)
{
  number.pop_back();
  numerator_ = BigInt(base, number);
  denominator_ = BigInt(base, std::string(number.size(), std::to_string(base - 1)[0]));
  numerator_ *= base;
  reduce();
}
