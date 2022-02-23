#include "M3i.h"

#include <algorithm>

M3i::M3i(const size_t size, const int num)
    : size1(size), size2(size), size3(size) {
  data = new int[GetFLatSize()];
  SetDefaultValue(num);
}
M3i::M3i(const size_t size1, const size_t size2, const size_t size3,
         const int num)
    : size1(size1), size2(size2), size3(size3) {
  data = new int[GetFLatSize()];
  SetDefaultValue(num);
}

int& M3i::atPosition(const size_t index1, const size_t index2,
                     const size_t index3) {
  if (index1 < size1 && index2 < size2 && index3 < size3) {
    return data[index1 * size2 * size3 + index2 * size3 + index3];
  } else {
    throw std::out_of_range("index out of range");
  }
}
const int& M3i::atPosition(const size_t index1, const size_t index2,
                           const size_t index3) const {
  if (index1 < size1 && index2 < size2 && index3 < size3) {
    return data[index1 * size2 * size3 + index2 * size3 + index3];
  } else {
    throw std::out_of_range("index out of range");
  }
}

void M3i::resize(const size_t new_size1, const size_t new_size2,
                 const size_t new_size3, const int num) {
  int* old_data = data;
  size_t old_size1 = size1;
  size_t old_size2 = size2;
  size_t old_size3 = size3;

  data = new int[new_size1 * new_size2 * new_size3];
  size1 = new_size1;
  size2 = new_size2;
  size3 = new_size3;
  SetDefaultValue(num);

  for (size_t i = 0; i < std::min(size1, old_size1); i++) {
    for (size_t j = 0; j < std::min(size2, old_size2); j++) {
      for (size_t k = 0; k < std::min(size3, old_size3); k++) {
        this->atPosition(i, j, k) =
            old_data[i * old_size2 * old_size3 + j * old_size3 + k];
      }
    }
  }

  delete[] old_data;
}

void M3i::SetDefaultValue(const int value) {
  for (size_t i = 0; i < GetFLatSize(); i++) {
    data[i] = value;
  }
}

std::ostream& M3i::write_to(std::ostream& ostrm) const {
  for (size_t i = 0; i < size1; i++) {
    for (size_t j = 0; j < size2; j++) {
      for (size_t k = 0; k < size3; k++) {
        ostrm << atPosition(i, j, k) << " ";
      }
      ostrm << "\n";
    }
    ostrm << "\n";
  }

  return ostrm;
}