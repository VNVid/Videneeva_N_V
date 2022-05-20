#ifndef BITSET_H
#define BITSET_H

#include <cstdint>
#include <iostream>

class BitSet {
 private:
  class BitHolder;

 public:
  BitSet() = default;
  // except: length <= 0
  BitSet(const int length, const bool default_value = false);

  BitSet(const BitSet& other);
  BitSet(BitSet&& other);

  BitSet& operator=(const BitSet& other);
  BitSet& operator=(BitSet&& other);

  ~BitSet();

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
  uint8_t* data = nullptr;
  size_t size = 0;
  size_t data_size = 0;

  class BitHolder {
   public:
    BitHolder() = delete;

    BitHolder(uint8_t* data, int idx);

    BitHolder(const BitHolder& bitholder) = default;
    BitHolder(BitHolder&& bitholder) = default;
    ~BitHolder() = default;

    BitHolder& operator=(const BitHolder& other) = default;
    BitHolder& operator=(const bool value);
    BitHolder& operator=(BitHolder&& other) = default;

    operator bool() const;

   private:
    uint8_t* data_piece;
    int idx;
  };
};

inline const BitSet operator|(const BitSet& first, const BitSet& second) {
  return BitSet(first) |= second;
}
inline const BitSet operator&(const BitSet& first, const BitSet& second) {
  return BitSet(first) &= second;
}
inline const BitSet operator^(const BitSet& first, const BitSet& second) {
  return BitSet(first) ^= second;
}

std::istream& operator>>(std::istream& istrm, BitSet& bs);
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs);

#endif