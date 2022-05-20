#ifndef M3i_H
#define M3i_H

#include <cstdio>
#include <iostream>

struct M3iInner {
  int *data = nullptr;
  size_t size1 = 0;
  size_t size2 = 0;
  size_t size3 = 0;

  int counter = 0;

  M3iInner() = default;
  M3iInner(const size_t size, const int num);
  M3iInner(const size_t size1, const size_t size2, const size_t size);
  M3iInner(const size_t size1, const size_t size2, const size_t size3,
           const int num);
  M3iInner(const std::initializer_list<
           std::initializer_list<std::initializer_list<int>>> &list);
  ~M3iInner();

  void fill(const int value);
  inline size_t GetFLatSize() const { return size1 * size2 * size3; }
};

class M3i {
 public:
  M3i();
  M3i(const M3i &);
  M3i(M3i &&);
  M3i(const size_t size,
      const int num = 0);  // строим матрицу размера size*size*size и заполняем
                           // значением num
  M3i(const size_t size1, const size_t size2, const size_t size3);
  M3i(const size_t size1, const size_t size2, const size_t size3,
      const int num);  //строим матрицу размера size1*size2*size3
                       //  и заполняем значением num
  M3i(const std::initializer_list<
      std::initializer_list<std::initializer_list<int>>> &list);

  ~M3i();

  M3i Clone() const;

  M3i &operator=(const M3i &other);
  M3i &operator=(M3i &&other);

  int &At(const size_t index1, const size_t index2, const size_t index3);
  int &At(const size_t index1, const size_t index2, const size_t index3) const;

  void Resize(const size_t size1, const size_t size2, const size_t size3);

  std::ostream &WriteTo(std::ostream &ostrm) const;
  std::istream &ReadFrom(std::istream &istrm);

  void Fill(const int value);

  int Size(const int dim) const;

  int getCopiesNumber() const { return info->counter; }

  class M3iException : public std::exception {
   private:
    std::string error;

   public:
    M3iException(std::string error) : error(error) {}

    const char *what() const noexcept { return error.c_str(); }
  };

 private:
  M3iInner *info;
};

std::istream &operator>>(std::istream &istrm, M3i &m);
std::ostream &operator<<(std::ostream &ostrm, const M3i &m);

#endif