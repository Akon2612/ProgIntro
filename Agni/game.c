#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  int i, j, u, v, parar, alt, dimx = 100, dimy = 100, on;
  int a[dimy][dimx], b[dimy][dimx];
  srand(time(NULL));
  for (i = 0; i < dimy; i++) {
    for (j = 0; j < dimx; j++) {
      a[i][j] = 0;
    }
  }
  a[4][3] = 1;
  a[4][4] = 1;
  a[4][5] = 1;
  a[3][5] = 1;
  a[2][4] = 1;
  for (i = 0; i < dimy; i++) {
    printf("\n");
    for (j = 0; j < dimx; j++) {
      printf("%d", a[i][j]);
    }
  }
  printf("\n");
  for (parar = 1; parar == 1;) {
    for (i = 0; i < dimy; i++) {
      for (j = 0; j < dimx; j++) {
        u = i;
        v = j;
        int up = (i - 1 + dimy) % dimy;
        int down = (i + 1) % dimy;
        int left = (j - 1 + dimx) % dimx;
        int right = (j + 1) % dimx;
        on = a[up][left];
        on = on + a[up][j];
        on = on + a[up][right];
        on = on + a[i][left];
        on = on + a[i][right];
        on = on + a[down][left];
        on = on + a[down][j];
        on = on + a[down][right];

        if ((a[u][v] == 0) && (on == 3)) {
          b[u][v] = 1;
        }
        if ((a[u][v] == 1) && (on == 2)) {
          b[u][v] = 1;
        }
        if ((a[u][v] == 1) && (on == 3)) {
          b[u][v] = 1;
        }
        if ((a[u][v] == 1) && (on < 2)) {
          b[u][v] = 0;
        }
        if ((a[u][v] == 1) && (on > 3)) {
          b[u][v] = 0;
        }
      }
    }
    for (i = 0; i < dimy; i++) {
      printf("\n");
      for (j = 0; j < dimx; j++) {
        u = i;
        v = j;
        a[i][j] = b[u][v];
        printf("%d", a[i][j]);
      }
    }
    printf("\n");
    scanf("%d", &parar);
  }
  return 0;
}