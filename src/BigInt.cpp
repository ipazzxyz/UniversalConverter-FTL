#include "../inc/BigInt.hpp"

#include <algorithm>

BigInt::BigInt(const uint64_t &initial_base, const std::string &s)
{
  if (initial_base == 0)
  {
    throw std::runtime_error("Base 0, wtf?");
  }
  if (initial_base == 1)
  {
    throw std::runtime_error("Base 1, wtf?");
  }
  bool is_opened = false;
  for (int i = 0; i < s.size(); ++i)
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

  for (uint64_t i = 0; i < size_; ++i)
  {
    digit_[i] = 0;
  }

  for (int64_t i = 0; i < s.size(); ++i)
  {
    BigInt digit = 0;

    if (s[i] >= '0' && s[i] <= '9')
    {
      digit = s[i] - '0';
    }
    else if (s[i] >= 'A' && s[i] <= 'Z')
    {
      digit = s[i] - 'A' + 10;
    }
    else if (s[i] >= 'a' && s[i] <= 'z')
    {
      digit = s[i] - 'a' + 10;
    }
    else if (s[i] == '[')
    {
      if (s[i + 1] == ']')
      {
        throw std::runtime_error(std::to_string(i + 1) + ": Empty brackets");
      }
      while (s[++i] != ']')
      {
        if (s[i] > '9' || s[i] < '0')
        {
          throw std::runtime_error(std::to_string(i + 1) +
                                   ": Not a '0'...'9' in brackets");
        }

        digit = digit * 10 + (s[i] - '0');
      }
    }
    else
    {
      throw std::runtime_error(std::to_string(i + 1) + ": Invalid digit");
    }
    if (digit >= initial_base)
    {
      throw std::runtime_error(
          std::to_string(s.size() - i) +
          ": It is impossible to represent a digit in base");
    }
    *this = *this * initial_base + digit;
  }
}
BigInt::BigInt()
{
  for (uint64_t i = 0; i < size_; ++i)
  {
    this->digit_[i] = 0;
  }
}
BigInt::BigInt(int64_t x)
{
  for (uint64_t i = 0; i < size_; ++i)
  {
    digit_[i] = 0;
  }

  uint64_t next = 0;
  while (x)
  {
    digit_[next++] = x % base_;
    x /= base_;
  }
}
BigInt::BigInt(const BigInt &other)
{
  for (uint64_t i = 0; i < size_; ++i)
  {
    digit_[i] = other.digit_[i];
  }
}

BigInt &BigInt::operator=(const BigInt &other)
{
  for (uint64_t i = 0; i < size_; ++i)
  {
    digit_[i] = other.digit_[i];
  }

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
  for (int i = 0; i < size_; ++i)
  {
    for (int j = 0; j < size_ - i; j++)
    {
      result.digit_[i + j] += digit_[i] * other.digit_[j];
    }
  }
  for (int i = 0; i < size_ - 1; ++i)
  {
    result.digit_[i + 1] += result.digit_[i] / base_;
    result.digit_[i] %= base_;
  }
  return result;
}

BigInt &BigInt::operator/=(const int64_t &x)
{
  for (int i = size_ - 1; i >= 0; i--)
  {
    if (i)
    {
      digit_[i - 1] += (digit_[i] % x) * base_;
    }
    digit_[i] /= x;
  }
  return *this;
}
BigInt BigInt::operator/(const int64_t &x) const
{
  BigInt n(*this);
  n /= x;
  return n;
}

BigInt &BigInt::operator%=(const uint64_t &x)
{
  return *this -= *this / x * x;
}
BigInt BigInt::operator%(const uint64_t &x) const
{
  BigInt result(*this);
  return result %= x;
}

bool BigInt::operator>(const BigInt &other) const
{
  for (int i = 0; i < size_; ++i)
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
  for (int i = 0; i < size_; ++i)
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

std::string BigInt::to_string(const uint64_t &base = 10) const
{
  std::string result;
  BigInt number(*this);
  while (number >= base)
  {
    result += std::to_string((number % base).digit_[0]);
    number /= base;
  }
  result += std::to_string((number % base).digit_[0]);
  std::reverse(result.begin(), result.end());
  return result;
}