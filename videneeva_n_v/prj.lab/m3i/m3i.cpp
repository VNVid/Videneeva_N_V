#include <m3i/m3i.h>

#include <algorithm>

M3iInner::M3iInner(const size_t size, const int num) {
  size1 = size;
  size2 = size;
  size3 = size;
  data = new int[size1 * size2 * size3];
  fill(num);
  counter = 1;
}
M3iInner::M3iInner(const size_t size1, const size_t size2, const size_t size3,
                   const int num)
    : size1(size1), size2(size2), size3(size3) {
  data = new int[size1 * size2 * size3];
  fill(num);
  counter = 1;
}
M3iInner::M3iInner(const size_t size1, const size_t size2, const size_t size3)
    : size1(size1), size2(size2), size3(size3) {
  data = new int[size1 * size2 * size3];
  counter = 1;
}
M3iInner::M3iInner(const std::initializer_list<
                   std::initializer_list<std::initializer_list<int>>> &list) {
  size1 = list.size();
  size2 = list.begin()->size();
  size3 = list.begin()->begin()->size();

  data = new int[size1 * size2 * size3];
  int ind = 0;
  for (auto outerlst : list) {
    for (auto midlst : outerlst) {
      for (auto elem : midlst) {
        data[ind] = elem;
        ++ind;
      }
    }
  }

  counter = 1;
}
M3iInner::~M3iInner() {
  delete[] data;
  data = nullptr;
}

void M3iInner::fill(const int value) {
  for (size_t i = 0; i < GetFLatSize(); i++) {
    data[i] = value;
  }
}

M3i::M3i(const size_t size, const int num) { info = new M3iInner(size, num); }
M3i::M3i(const size_t size1, const size_t size2, const size_t size3) {
  if (size1 <= 0 || size2 <= 0 || size3 <= 0) {
    throw M3iException("Impossible size: should be >= 0");
  }
  info = new M3iInner(size1, size2, size3);
}
M3i::M3i(const size_t size1, const size_t size2, const size_t size3,
         const int num) {
  if (size1 <= 0 || size2 <= 0 || size3 <= 0) {
    throw M3iException("Impossible size: should be >= 0");
  }
  info = new M3iInner(size1, size2, size3, num);
}
M3i::M3i(const std::initializer_list<
         std::initializer_list<std::initializer_list<int>>> &list) {
  info = new M3iInner(list);
}

M3i::M3i(const M3i &other) {
  info = other.info;
  (info->counter)++;
}

M3i::~M3i() {
  if (info->counter > 0) {
    (info->counter)--;
  } else {
    delete info;
    info = nullptr;
  }
}

M3i &M3i::operator=(const M3i &other) {
  if (this == &other) {
    return *this;
  }
  info = other.info;
  (info->counter)++;
  return *this;
}

M3i M3i::Clone() const {
  M3i cloned = M3i();
  cloned.info = new M3iInner();
  cloned.info->size1 = info->size1;
  cloned.info->size2 = info->size2;
  cloned.info->size3 = info->size3;
  cloned.info->counter = 1;
  cloned.info->data = new int[info->GetFLatSize()];
  for (size_t i = 0; i < info->GetFLatSize(); i++) {
    cloned.info->data[i] = info->data[i];
  }
  return cloned;
}

int &M3i::At(const size_t index1, const size_t index2, const size_t index3) {
  if (index1 < info->size1 && index2 < info->size2 && index3 < info->size3) {
    return info->data[index1 * info->size2 * info->size3 +
                      index2 * info->size3 + index3];
  } else {
    throw std::out_of_range("index out of range");
  }
}
const int &M3i::At(const size_t index1, const size_t index2,
                   const size_t index3) const {
  if (index1 < info->size1 && index2 < info->size2 && index3 < info->size3) {
    return info->data[index1 * info->size2 * info->size3 +
                      index2 * info->size3 + index3];
  } else {
    throw std::out_of_range("index out of range");
  }
}

void M3i::Resize(const size_t new_size1, const size_t new_size2,
                 const size_t new_size3, const int num) {
  if (new_size1 <= 0 || new_size2 <= 0 || new_size3 <= 0) {
    throw M3iException("Impossible size: should be >= 0");
  }

  int *old_data = info->data;
  size_t old_size1 = info->size1;
  size_t old_size2 = info->size2;
  size_t old_size3 = info->size3;

  info->data = new int[new_size1 * new_size2 * new_size3];
  info->size1 = new_size1;
  info->size2 = new_size2;
  info->size3 = new_size3;
  Fill(num);

  for (size_t i = 0; i < std::min(info->size1, old_size1); i++) {
    for (size_t j = 0; j < std::min(info->size2, old_size2); j++) {
      for (size_t k = 0; k < std::min(info->size3, old_size3); k++) {
        this->At(i, j, k) =
            old_data[i * old_size2 * old_size3 + j * old_size3 + k];
      }
    }
  }

  delete[] old_data;
}

void M3i::Fill(const int value) { info->fill(value); }

std::ostream &M3i::WriteTo(std::ostream &ostrm) const {
  ostrm << Size(0) << Size(1) << Size(2) << "\n";
  for (size_t i = 0; i < info->size1; i++) {
    for (size_t j = 0; j < info->size2; j++) {
      for (size_t k = 0; k < info->size3; k++) {
        ostrm << At(i, j, k) << " ";
      }
      ostrm << "\n";
    }
    ostrm << "\n";
  }

  return ostrm;
}
std::istream &M3i::ReadFrom(std::istream &istrm) {
  istrm >> info->size1 >> info->size2 >> info->size3;
  for (size_t i = 0; i < info->size1; i++) {
    for (size_t j = 0; j < info->size2; j++) {
      for (size_t k = 0; k < info->size3; k++) {
        istrm >> At(i, j, k);
      }
    }
  }

  return istrm;
}
std::ostream &operator<<(std::ostream &stream, const M3i &m) {
  m.WriteTo(stream);
  return stream;
}
std::istream &operator>>(std::istream &stream, M3i &m) {
  m.ReadFrom(stream);
  return stream;
}

int M3i::Size(const int dim) const {
  if (dim == 0) {
    return info->size1;
  }
  if (dim == 1) {
    return info->size2;
  }
  if (dim == 2) {
    return info->size3;
  }

  throw M3iException("Impossible size dimension");
}