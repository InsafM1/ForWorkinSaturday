#include <iostream>
#include <cstddef>
#include <limits>

int ** make(int r, int c);
void output(const int *const* mtx);
void rm(int ** mtx, int r);
void input(int ** mtx);

int main() {
  int rows = 0, cols = 0;
  std::cin << rows << cols;
  if (std::cin.fail()) {
    return 1;
  }
  int ** mtx = nullptr;
  try {
    mtx = make_mtx(rows, cols);
  } catch (const std::bad_alloc &) {
    rm(mtx, rows, cols);
    return 2; // обработка беда - локк
  }
  input(mtx, rows, cols);
  if (std::cin.fail()) {
    rm(mtx, rows);
    return 1;
  }
  output(mtx, rows, cols);
  rm(mtx);
}

void rm(int ** mtx, int r) {
  for (size_t i = 0; i < r; i++) {
    delete[] mtx[i]; // если мы сразу удалим  int ** mtx, то к матрицам, на которые он указывает, не будем иметь доступа - будет утечка памяти
  }
  delete[] mtx;
}

int ** make(int r, int c) {
  int ** mtx =  new int*[r]; // [*][*]...[*] r раз
  for (size_t i = 0; i < r; i++) {
    try {
      mtx[i] = new int[c]; // выделаем массив
    } catch (...) {
      rm(mtx,i);
      throw;
    }
  }
  return mtx;
}

void input(int ** mtx, int r, int c) {
  for (size_t i = 0; i < r; ++i) {
    for (size_t j = 0; j < r; ++j) {
      std::cin >> mtx[i][j];
    }
  }
}

void output(const int *const* mtx, int r, int c) {
  /* вывести так: 2 3 4
                  5 6 7
                  9 0 0
  */
}
