#include "bigint.hpp"
#include <algorithm>
#include <iostream>
BigInt::BigInt()
{
  std::fill(digit_, digit_ + size_, 0);
}
BigInt::BigInt(uint64_t number)
{
  std::fill(digit_, digit_ + size_, 0);
  uint64_t next = 0;
  while (number)
  {
    digit_[next++] = number % base_;
    number /= base_;
  }
}
BigInt::BigInt(const BigInt &other)
{
  for (uint64_t i = 0; i < size_; ++i)
  {
    digit_[i] = other.digit_[i];
  }
}
BigInt::BigInt(const uint64_t &base, const std::string &number)
{
  if (base < 2)
  {
    throw std::runtime_error("Base should be greater than or equal to 2");
  }
  validateBrackets(number);
  std::fill(digit_, digit_ + size_, 0);
  for (int64_t i = 0; i < number.size(); ++i)
  {
    BigInt digit = 0;
    if (isdigit(number[i]))
    {
      digit = number[i] - '0';
    }
    else if (isalpha(number[i]))
    {
      digit = std::toupper(number[i]) - 'A' + 10;
    }
    else if (number[i] == '[')
    {
      if (number[i + 1] == ']')
      {
        throw std::runtime_error(std::to_string(i + 1) + ": Empty brackets");
      }
      while (number[++i] != ']')
      {
        if (number[i] > '9' || number[i] < '0')
        {
          throw std::runtime_error(std::to_string(i + 1) +
                                   ": Not a '0'...'9' in brackets");
        }
        digit = digit * 10 + (number[i] - '0');
      }
    }
    else
    {
      throw std::runtime_error(std::to_string(i + 1) + ": Invalid digit");
    }
    if (digit >= base)
    {
      throw std::runtime_error(
          std::to_string(number.size() - i) +
          ": It is impossible to represent a digit in base");
    }
    *this = *this * base + digit;
  }
}
BigInt &BigInt::operator=(const BigInt &other)
{
  std::copy(other.digit_, other.digit_ + size_, digit_);
  return *this;
}
BigInt &BigInt::operator+=(const BigInt &other)
{
  for (uint64_t i = 0; i < size_; ++i)
  {
    digit_[i] += other.digit_[i];
  }
  for (uint64_t i = 0; i < size_ - 1; ++i)
  {
    if (digit_[i] >= base_)
    {
      digit_[i] -= base_;
      digit_[i + 1]++;
    }
  }
  return *this;
}
BigInt BigInt::operator+(const BigInt &other) const
{
  BigInt n(*this);
  n += other;
  return n;
}
BigInt &BigInt::operator++()
{
  *this += 1;
  return *this;
}
BigInt &BigInt::operator-=(const BigInt &other)
{
  for (uint64_t i = 0; i < size_; ++i)
  {
    digit_[i] -= other.digit_[i];
  }

  for (uint64_t i = 0; i < size_ - 1; ++i)
  {
    if (digit_[i] < 0)
    {
      digit_[i] += base_;
      digit_[i + 1]--;
    }
  }
  return *this;
}
BigInt BigInt::operator-(const BigInt &other) const
{
  BigInt n(*this);
  n -= other;
  return n;
}
BigInt &BigInt::operator--()
{
  *this -= 1;
  return *this;
}
BigInt &BigInt::operator*=(const BigInt &other)
{
  return *this = *this * other;
}
BigInt BigInt::operator*(const BigInt &other) const
{
  BigInt result;
  for (uint64_t i = 0; i < size_; ++i)
  {
    for (uint64_t j = 0; j < size_ - i; j++)
    {
      result.digit_[i + j] += digit_[i] * other.digit_[j];
    }
  }
  for (uint64_t i = 0; i < size_ - 1; ++i)
  {
    result.digit_[i + 1] += result.digit_[i] / base_;
    result.digit_[i] %= base_;
  }
  return result;
}
BigInt &BigInt::operator/=(const BigInt &other)
{
  *this = *this / other;
  return *this;
}
BigInt BigInt::operator/(const BigInt &other) const
{
  BigInt l, r(*this + 1);
  while (r - l > 1)
  {
    BigInt m = getMid(l, r);
    if (m * other > *this)
    {
      r = m;
    }
    else
    {
      l = m;
    }
  }
  return l;
}
BigInt &BigInt::operator%=(const BigInt &other)
{
  // return *this -= *this / other * other;
  return *this;
}
BigInt BigInt::operator%(const BigInt &other) const
{
  return *this - (*this / other) * other;
  // BigInt result(*this);
  // return result %= other;
}
bool BigInt::operator>(const BigInt &other) const
{
  for (int64_t i = size_ - 1; i >= 0; --i)
  {
    if (digit_[i] > other.digit_[i])
    {
      return true;
    }
    else if (digit_[i] < other.digit_[i])
    {
      return false;
    }
  }
  return false;
}
bool BigInt::operator>=(const BigInt &other) const { return !(*this < other); }
bool BigInt::operator==(const BigInt &other) const { return !(*this != other); }
bool BigInt::operator!=(const BigInt &other) const
{
  return *this > other || *this < other;
}
bool BigInt::operator<(const BigInt &other) const
{
  for (int64_t i = size_ - 1; i >= 0; --i)
  {
    if (digit_[i] < other.digit_[i])
    {
      return true;
    }
    else if (digit_[i] > other.digit_[i])
    {
      return false;
    }
  }
  return false;
}
bool BigInt::operator<=(const BigInt &other) const { return !(*this > other); }
std::string BigInt::toString(const uint64_t &base = 10) const
{
  std::string result;
  BigInt number(*this);
  while (number >= base)
  {
    uint64_t digit = (number % base).digit_[0];
    if (digit <= 9)
    {
      result += std::to_string(digit);
    }
    else if (digit >= 10 && digit <= 36)
    {
      result += (char)(digit + 'a' - 10);
    }
    else
    {
      uint64_t q = result.size();
      result += '[' + std::to_string(digit) + ']';
      std::reverse(result.begin() + q, result.end());
    }
    number /= base;
  }
  uint64_t digit = (number % base).digit_[0];
  if (digit <= 9)
  {
    result += std::to_string(digit);
  }
  else if (digit >= 10 && digit <= 36)
  {
    result += (char)(digit + 'a' - 10);
  }
  else
  {
    uint64_t q = result.size();
    result += '[' + std::to_string(digit) + ']';
    std::reverse(result.begin() + q, result.end());
  }
  std::reverse(result.begin(), result.end());
  return result;
}
void BigInt::validateBrackets(const std::string &s) const
{
  bool is_opened = false;

  for (uint64_t i = 0; i < s.size(); ++i)
  {
    if (s[i] == '[')
    {
      if (is_opened)
      {
        throw std::runtime_error(std::to_string(i + 1) +
                                 ": Bracket inside brackets");
      }
      is_opened = true;
    }
    else if (s[i] == ']')
    {
      if (!is_opened)
      {
        throw std::runtime_error(std::to_string(i + 1) +
                                 ": There is no opening bracket");
      }
      is_opened = false;
    }
  }

  if (is_opened)
  {
    throw std::runtime_error("The bracket is not closed");
  }
}
BigInt getMid(const BigInt &a, const BigInt &b)
{
  BigInt result(a + b);
  for (int64_t i = a.size_ - 1; i >= 0; --i)
  {
    if (i)
    {
      result.digit_[i - 1] += (result.digit_[i] % 2) * a.base_;
    }
    result.digit_[i] /= 2;
  }
  return result;
}
BigInt gcd(BigInt a, BigInt b)
{
  if (a < 1)
  {
    return b;
  }
  BigInt mod = b % a;
  return gcd(mod, a);
}
BigInt lcd(BigInt a, BigInt b)
{
  return (a * b) / gcd(a, b);
}