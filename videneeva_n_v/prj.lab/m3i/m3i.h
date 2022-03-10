#ifndef M3i_H
#define M3i_H

#include <cstdio>
#include <iostream>

class M3i {
 public:
  M3i() = default;
  M3i(const M3i&);
  M3i(M3i&&) = default;
  M3i(const size_t size,
      const int num = 0);  // строим матрицу размера size*size*size и заполняем
                           // значением num
  M3i(const size_t size1, const size_t size2, const size_t size3,
      const int num = 0);  //строим матрицу размера size1*size2*size3
                           //  и заполняем значением num

  ~M3i();

  M3i clone() const;

  M3i& operator=(const M3i& other);
  M3i& operator=(M3i&& other) = default;

  int& at(const size_t index1, const size_t index2, const size_t index3);
  const int& at(const size_t index1, const size_t index2,
                const size_t index3) const;

  void resize(const size_t size1, const size_t size2, const size_t size3,
              const int num = 0);

  std::ostream& write_to(std::ostream& ostrm) const;

  void fill(const int value);

  int size(const int dim);

  int getCopiesNumber() { return *counter; }

 private:
  int* data = nullptr;
  size_t size1 = 0;
  size_t size2 = 0;
  size_t size3 = 0;

  int* counter;

  inline size_t GetFLatSize() const { return size1 * size2 * size3; }
};

#endif