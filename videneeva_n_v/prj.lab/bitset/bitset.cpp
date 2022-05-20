#include "bitset.h"

BitSet::BitSet(const int length, const bool default_value) {
  if (length <= 0) {
    throw BitsetException("Length must be > 0");
  }

  size = length;
  data_size = (length + 7) / 8;
  data = new uint8_t[data_size];
  Fill(default_value);
}

BitSet::BitSet(const BitSet& other) {
  size = other.size;
  data_size = other.data_size;

  data = new uint8_t[data_size];
  for (size_t i = 0; i < data_size; i++) {
    data[i] = other.data[i];
  }
}
BitSet::BitSet(BitSet&& other) {
  data = other.data;
  size = other.size;
  data_size = other.data_size;
  other.data = nullptr;
}

BitSet& BitSet::operator=(const BitSet& other) {
  if (this == &other) {
    return *this;
  }
  size = other.size;

  delete[] data;
  data_size = (other.size + 7) / 8;
  data = new uint8_t[data_size];
  for (size_t i = 0; i < data_size; i++) {
    data[i] = other.data[i];
  }

  return *this;
}
BitSet& BitSet::operator=(BitSet&& other) {
  size = other.size;
  data_size = other.data_size;
  delete[] data;
  data = other.data;
  other.data = nullptr;

  return *this;
}

BitSet::~BitSet() { delete[] data; }

BitSet& BitSet::operator|=(const BitSet& other) {
  if (this->size != other.size) {
    throw BitsetException("Different sizes");
  }

  for (size_t i = 0; i < data_size; i++) {
    data[i] |= other.data[i];
  }
  return *this;
}
BitSet& BitSet::operator^=(const BitSet& other) {
  if (this->size != other.size) {
    throw BitsetException("Different sizes");
  }

  for (size_t i = 0; i < data_size; i++) {
    data[i] ^= other.data[i];
  }
  return *this;
}
BitSet& BitSet::operator&=(const BitSet& other) {
  if (this->size != other.size) {
    throw BitsetException("Different sizes");
  }

  for (size_t i = 0; i < data_size; i++) {
    data[i] &= other.data[i];
  }
  return *this;
}
const BitSet BitSet::operator~() const {
  for (size_t i = 0; i < size / 8; i++) {
    data[i] = ~data[i];
  }

  if (data_size > size / 8) {
    int last_num = 1;
    for (size_t i = 1; i < size % 8; i++) {
      last_num += (1 << i);
    }
    last_num &= ~data[data_size - 1];
    data[data_size - 1] = last_num;
  }

  return *this;
}

int BitSet::Size() const { return size; }

void BitSet::Resize(const int new_size) {
  if (new_size <= 0) {
    throw BitsetException("Length must be > 0");
  }

  size_t old_size = size;
  size_t old_data_size = data_size;
  uint8_t* old_data = data;

  size = new_size;
  data_size = (size + 7) / 8;
  data = new uint8_t[data_size];
  Fill(false);

  for (size_t i = 0; i < std::min(data_size, old_data_size); i++) {
    data[i] = old_data[i];
  }

  delete[] old_data;
}
void BitSet::Fill(const bool value) {
  for (size_t i = 0; i < data_size; i++) {
    data[i] = 0;
  }

  if (value) {
    for (size_t i = 0; i < size / 8; i++) {
      data[i] = 255;
    }
    if (data_size > size / 8) {
      int last_num = 1;
      for (size_t i = 1; i < size % 8; i++) {
        last_num += (1 << i);
      }

      data[data_size - 1] = last_num;
    }
  }
}

BitSet::BitHolder BitSet::operator[](const int idx) {
  if (idx < 0 || size <= idx) {
    throw BitsetException("Index out of range");
  }

  // std::cout << "number=" << int(data[idx / 8])
  //           << " mask=" << int((1 << (idx % 8)));
  return BitHolder(&data[idx / 8], idx % 8);
}
bool BitSet::operator[](const int idx) const {
  if (idx < 0 || size <= idx) {
    throw BitsetException("Index out of range");
  }

  // std::cout << int(data[idx / 8]) << " " << int((1 << (idx % 8)));
  return data[idx / 8] & (1 << (idx % 8));
}

BitSet::BitHolder::BitHolder(uint8_t* data, int _idx) {
  // std::cout << " _idx" << _idx << " ";
  data_piece = data;
  idx = _idx;
}
BitSet::BitHolder& BitSet::BitHolder::operator=(const bool value) {
  if (value) {
    *data_piece |= (1 << idx);
  } else {
    *data_piece &= ~(1 << idx);
  }

  return *this;
}
BitSet::BitHolder::operator bool() const {
  // std::cout << " bool=" << (*data_piece & (1 << idx))
  //           << " data_pice=" << int(*data_piece) << " (idx)=" << (idx) << "
  //           ";
  return (*data_piece & (1 << idx)) != 0;
}

std::istream& operator>>(std::istream& istrm, BitSet& bs) {
  std::string number = "";
  istrm >> number;

  if (number.size() == 0) {
    istrm.setstate(std::ios_base::failbit);
    return istrm;
  }

  bs = BitSet(number.size());
  for (size_t i = 0; i < number.size(); i++) {
    if (number[i] == '0') {
      bs[i] = false;
    } else if (number[i] == '1') {
      bs[i] = true;
    } else {
      istrm.setstate(std::ios_base::failbit);
      break;
    }
  }
  return istrm;
}
std::ostream& operator<<(std::ostream& ostrm, const BitSet& bs) {
  for (size_t i = 0; i < bs.Size(); i++) {
    ostrm << bs[i];
  }

  return ostrm;
}