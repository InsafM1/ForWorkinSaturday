#include <iostream>
#include <cstddef>
#include <limits>

int ** make_mtx(int r, int c);
void output(const int *const* mtx);
void rm(int ** mtx, int rows, int cols);

int main() {
  int rows = 0, cols = 0;
  std::cin << rows << cols;
  if (std::cin.fail()) {
    return 1;
  }
  int ** mtx = nullptr;
  mtx = make_mtx(rows, cols);
  output(mtx);
  rm(mtx);
}

void rm(int ** mtx, int r, int c) {
  for (size_t i = 0; i < r; i++) {
    delete[] mtx[i]; // если мы сразу удалим  int ** mtx, то к матрицам, на которые он указывает, не будем иметь доступа - будет утечка памяти
  }
  delet[] mtx;
}

