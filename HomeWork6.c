#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char a[100][100];    // 0°
  char r90[100][100];  // 90°
  char r180[100][100]; // 180°
  char r270[100][100]; // 270°

  char reducida[20][20];

  int i, j;
  int bi, bj;
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
      r90[i][j] = a[99 - j][i];       // 90°
      r180[i][j] = a[99 - i][99 - j]; // 180°
      r270[i][j] = a[j][99 - i];      // 270°
    }
  }

  printf("--- CARITA 0° ---\n");
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      printf("%c", a[i][j]);
    }
    printf("\n");
  }

  printf("\n--- CARITA 90° ---\n");
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      printf("%c", r90[i][j]);
    }
    printf("\n");
  }

  printf("\n--- CARITA 180° ---\n");
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      printf("%c", r180[i][j]);
    }
    printf("\n");
  }

  printf("\n--- CARITA 270° ---\n");
  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      printf("%c", r270[i][j]);
    }
    printf("\n");
  }

  int op_angulo, op_tamano;

  printf("\nEscoja que carita imprimir:\n");
  printf("1) 0 deg\n");
  printf("2) 90 deg\n");
  printf("3) 180 deg\n");
  printf("4) 270 deg\n");
  printf("Opcion: ");
  scanf("%d", &op_angulo);

  printf("\nEscoja el tamano:\n");
  printf("1) Normal (100x100)\n");
  printf("2) Reducida (20x20)\n");
  printf("Opcion: ");
  scanf("%d", &op_tamano);

  if (op_tamano == 1) {
    if (op_angulo == 1) {
      for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
          printf("%c", a[i][j]);
        }
        printf("\n");
      }
    } else if (op_angulo == 2) {
      for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
          printf("%c", r90[i][j]);
        }
        printf("\n");
      }
    } else if (op_angulo == 3) {
      for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
          printf("%c", r180[i][j]);
        }
        printf("\n");
      }
    } else if (op_angulo == 4) {
      for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
          printf("%c", r270[i][j]);
        }
        printf("\n");
      }
    }
  }

  else if (op_tamano == 2) {
    for (i = 0; i < 20; i++) {
      for (j = 0; j < 20; j++) {
        char simbolo = ' ';

        for (bi = 0; bi < 5; bi++) {
          for (bj = 0; bj < 5; bj++) {
            char c = ' ';

            if (op_angulo == 1)
              c = a[i * 5 + bi][j * 5 + bj];
            else if (op_angulo == 2)
              c = r90[i * 5 + bi][j * 5 + bj];
            else if (op_angulo == 3)
              c = r180[i * 5 + bi][j * 5 + bj];
            else if (op_angulo == 4)
              c = r270[i * 5 + bi][j * 5 + bj];

            if (c == 'O' || c == 'X') {
              simbolo = c;
            }
          }
        }
        reducida[i][j] = simbolo;
      }
    }

    for (i = 0; i < 20; i++) {
      for (j = 0; j < 20; j++) {
        printf("%c", reducida[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}