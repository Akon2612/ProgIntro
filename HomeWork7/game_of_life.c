#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Para la función usleep()

#define TAM 100

int main(void) {
  int a[100][100];
  int b[100][100];
  int i, j;

  srand(time(NULL));

  for (i = 0; i < TAM; i++) {
    for (j = 0; j < TAM; j++) {
      a[i][j] = 0;
    }
  }

  a[50][49] = 1;
  a[50][50] = 1;
  a[50][51] = 1;

  while (1) {
    printf("\033[H\033[J");

    for (i = 0; i < TAM; i++) {
      for (j = 0; j < TAM; j++) {
        if (a[i][j] == 1) {
          printf("#");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }

    for (i = 0; i < TAM; i++) {
      for (j = 0; j < TAM; j++) {
        int up = (i - 1 + TAM) % TAM;
        int down = (i + 1) % TAM;
        int left = (j - 1 + TAM) % TAM;
        int right = (j + 1) % TAM;

        int vecinos = a[up][left] + a[up][j] + a[up][right] + a[i][left] +
                      a[i][right] + a[down][left] + a[down][j] + a[down][right];

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

    for (i = 0; i < TAM; i++) {
      for (j = 0; j < TAM; j++) {
        a[i][j] = b[i][j];
      }
    }

    // Pausa (0.1 segundos)
    usleep(100000);
  }

  return 0;
}