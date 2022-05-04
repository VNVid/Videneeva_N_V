#include "bitset.h"

BitSet::BitSet(const int length, const bool default_value) {}

BitSet& BitSet::operator|=(const BitSet& other) { return *this; }
BitSet& BitSet::operator^=(const BitSet& other) { return *this; }
BitSet& BitSet::operator&=(const BitSet& other) { return *this; }
const BitSet BitSet::operator~() const { return *this; }

int BitSet::Size() const { return 0; }

void BitSet::Resize(const int new_size) {}
void BitSet::Fill(const bool value) {}

BitSet::BitHolder BitSet::operator[](const int idx) {
  return BitSet::BitHolder(true);
}
bool BitSet::operator[](const int idx) const { return true; }