#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char a[100][100];
  int i, j, n = 100;
  char r90[j][i];
  int c, b;
  int d1, d2;
  int coY1 = 30, coX1 = 35;                       // ojo izquierdo
  int coY2 = 30, coX2 = 65;                       // ojo derecho
  int r = 8;                                      // radio de los ojos
  int itop = 45, ibottom = 55, jcenter = 50;      // nariz
  int imin = 65, imax = 75, jmin = 15, jmax = 80; // boca

  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      d1 = sqrt((i - coY1) * (i - coY1) + (j - coX1) * (j - coX1));
      d2 = sqrt((i - coY2) * (i - coY2) + (j - coX2) * (j - coX2));
      if ((d1 <= r) || (d2 <= r) ||
          ((i >= itop) && (i <= ibottom) && (abs(j - jcenter) <= (i - itop))) ||
          ((i >= imin) && (i <= imax) && (j >= jmin) && (j <= jmax))) {
        a[i][j] = 'O';
      } else {
        if ((i == 0) || (i == 99) || (j == 0) || (j == 99)) {
          a[i][j] = 'X';
        } else {
          a[i][j] = ' ';
        }
      }
    }
  }
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      printf("%c", a[i][j]);
    }
    printf("\n");
  }
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      r90[i][j] = a[i][((n - 1) - j)];
    }
  }
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      printf("%c", r90[i][j]);
    }
    printf("\n");
  }
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      printf("%c", a[j][i]);
    }
    printf("\n");
  }
  return (0);
}