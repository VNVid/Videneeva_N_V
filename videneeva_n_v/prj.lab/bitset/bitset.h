#ifndef BITSET_H
#define BITSET_H

#include <iostream>

class BitSet {
 private:
  class BitHolder;

 public:
  BitSet() = default;
  // except: length <= 0
  BitSet(const int length, const bool default_value = false);

  BitSet(const BitSet& other) = default;
  BitSet(BitSet&& other) = default;

  BitSet& operator=(const BitSet& other) = default;
  BitSet& operator=(BitSet&& other) = default;

  ~BitSet() = default;

  // except: this->size != other.size
  BitSet& operator|=(const BitSet& other);
  // except: this->size != other.size
  BitSet& operator^=(const BitSet& other);
  // except: this->size != other.size
  BitSet& operator&=(const BitSet& other);
  const BitSet operator~() const;

  int Size() const;

  // except: length <= 0
  void Resize(const int new_size);
  void Fill(const bool value);

  // except: idx < 0 or idx >= size
  BitHolder operator[](const int idx);
  // except: idx < 0 or idx >= size
  bool operator[](const int idx) const;

  class BitsetException : public std::exception {
   private:
    std::string error;

   public:
    BitsetException(std::string error) : error(error) {}

    const char* what() const noexcept { return error.c_str(); }
  };

 private:
  // можно будет вернуть, нельзя создавать
  // auto smth = bset[123];  // compiles
  class BitHolder {
   public:
    BitHolder() = delete;

    // temporary
    BitHolder(bool value);

    BitHolder(const BitHolder& bitholder) = default;
    BitHolder(BitHolder&& bitholder) = default;

    BitHolder& operator=(const BitHolder& other) = default;
    BitHolder& operator=(const bool value);
    BitHolder& operator=(BitHolder&& other) = default;

    operator bool() const;
  };
};
// except: first.size != second.size
const BitSet operator|(const BitSet& first, const BitSet& second);
// except: first.size != second.size
const BitSet operator&(const BitSet& first, const BitSet& second);
// except: first.size != second.size
const BitSet operator^(const BitSet& first, const BitSet& second);

std::istream& operator>>(std::istream& istrm, BitSet& bs);
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);

#endif