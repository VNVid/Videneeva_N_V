#ifndef M3i_H
#define M3i_H

#include <cstdio>
#include <iostream>

class M3i {
 public:
  M3i() = default;
  M3i(const M3i&) = default;
  M3i(M3i&&) = default;
  M3i(const size_t size,
      const int num = 0);  // строим матрицу размера size*size*size и заполняем
                           // значением num
  M3i(const size_t size1, const size_t size2, const size_t size3,
      const int num = 0);  //строим матрицу размера size1*size2*size3
                           //  и заполняем значением num

  ~M3i() { delete[] data; }

  M3i& operator=(const M3i& other) = default;
  M3i& operator=(M3i&& other) = default;

  int& atPosition(const size_t index1, const size_t index2,
                  const size_t index3);
  const int& atPosition(const size_t index1, const size_t index2,
                        const size_t index3) const;

  void resize(const size_t size1, const size_t size2, const size_t size3,
              const int num = 0);

  std::ostream& write_to(std::ostream& ostrm) const;

 private:
  int* data = nullptr;
  size_t size1 = 0;
  size_t size2 = 0;
  size_t size3 = 0;

  inline size_t GetFLatSize() { return size1 * size2 * size3; }
  void SetDefaultValue(const int value);
};

#endif