#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Para la función usleep()

int main(void) {
  int a[100][100];
  int b[100][100];
  int i, j;

  srand(time(NULL));

  for (i = 0; i < 100; i++) {
    for (j = 0; j < 100; j++) {
      if ((double)rand() / RAND_MAX < 0.20) {
        a[i][j] = 1; // 20% de probabilidad de vida
      } else {
        a[i][j] = 0;
      }
    }
  }

  while (1) {
    printf("\033[H\033[J");

    for (i = 0; i < 100; i++) {
      for (j = 0; j < 100; j++) {
        if (a[i][j] == 1) {
          printf("#");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }

    for (i = 1; i < 99; i++) {
      for (j = 1; j < 99; j++) {
        int vecinos = a[i - 1][j - 1] + a[i - 1][j] + a[i - 1][j + 1] +
                      a[i][j - 1] + a[i][j + 1] + a[i + 1][j - 1] +
                      a[i + 1][j] + a[i + 1][j + 1];

        if (a[i][j] == 1) {
          if (vecinos < 2 || vecinos > 3) {
            b[i][j] = 0; // Muere por soledad o sobrepoblación
          } else {
            b[i][j] = 1; // Sobrevive
          }
        } else {
          if (vecinos == 3) {
            b[i][j] = 1; // Nace por reproducción
          } else {
            b[i][j] = 0; // Sigue muerta
          }
        }
      }
    }

    for (i = 1; i < 99; i++) {
      for (j = 1; j < 99; j++) {
        a[i][j] = b[i][j];
      }
    }

    // Pausa (0.1 segundos)
    usleep(100000);
  }

  return 0;
}