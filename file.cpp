#include <iostream>
#include <cstddef>
#include <limits>

int ** make(int r, int c);
void output(const int *const* mtx, int r, int c);
void rm(int ** mtx, int r);
int **conver(const int * t, size_t n, const size_t * lns, size_t rows);

int main() {
  size_t rows = 4;
  int ** table = nullptr;
  int * t = nullptr, int * lns = nullptr;
  try
  {
    int *t = new int[12]{5 ,5 ,5 ,5 ,6, 6, 7, 7, 7, 7, 7, 8};
    int *lns = new int[4]{4 ,2, 5, 1};
  }
  catch(const std::bad_alloc &e)
  {
    delete [] t;
    delete [] lns;
    lns = nullptr, t = nullptr;
    std::cerr << e.what() << std::endl;
    return 2;
  }
  size_t n = 0;
  for (size_t i = 0; i < rows; ++i) {
    n += lns[i];
  }
  try
  {
    table = conver(t, n, lns, rows);
  }
  catch (const std::bad_alloc &)
  {
    rm(table, rows);
    delete [] t;
    delete [] lns;
    return 2; // обработка беда - локк
  }
  output(table, rows, lns);
  delete [] t;
  delete [] lns;
  t = nullptr, lns = nullptr;
  rm(table, rows);
  return 0;
}

void rm(int ** mtx, int r) {
  for (int i = 0; i < r; i++) {
    delete[] mtx[i];
    mtx[i] = nullptr;
  }
  delete[] mtx;
  mtx = nullptr;
}

void output(const int *const* mtx, int r, int * lns) {
  for (size_t i = 0; i < r; ++i) {
    for (size_t j = 0; j < lns[i]; ++j) {
      std::cout << mtx[i][j] << " ";
    }
    std::cout << '\n';
  }
  rm(mtx, r);
}

int **conver(const int * t, size_t n, const size_t * lns, size_t rows) {
  int ** table = new int *[rows];
  size_t k = 0;
  for (size_t i = 0; i < rows; ++i) {
    try {
      table[i] = new int[lns[i]];
      for (size_t j = 0; j < lns[i]; ++j) {
        table[i][j] = t[k];
        k++;
      }
    }
    catch (...) {
      rm(table, i);
      throw;
    }
  }
  return table;
}
