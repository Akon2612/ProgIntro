#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TAM 50

int main(void) {
  int a[TAM][TAM] = {0};
  int b[TAM][TAM] = {0};
  int i, j;
  int eleccion;
  int patron;
  int probabilidad;

  printf("¿Qué deseas imprimir?\n");
  printf("1. Cuadrícula aleatoria\n");
  printf("2. Patrón específico\n");
  printf("Elige una opción: ");
  scanf("%d", &eleccion);

  if (eleccion != 1 && eleccion != 2) {
    printf("Esta opcion no es valida\n");
    return 0;
  }

  if (eleccion == 1) {
    printf("Probabilidad de que una celda esté viva (0 a 100): ");
    scanf("%d", &probabilidad);

    srand(time(NULL));

    for (i = 0; i < TAM; i++) {
      for (j = 0; j < TAM; j++) {
        if (rand() % 100 < probabilidad) {
          a[i][j] = 1;
        } else {
          a[i][j] = 0;
        }
      }
    }
  }

  if (eleccion == 2) {
    printf("Patrones disponibles:\n");
    printf("1. Planeador\n");
    printf("2. Parpadeador\n");
    printf("3. Sapo\n");
    printf("4. Nave ligera\n");
    printf("5. Pentominó R\n");
    printf("Elige un patrón: ");
    scanf("%d", &patron);

    if (patron < 1 || patron > 5) {
      printf("Esta opcion no es valida\n");
      return 0;
    }

    if (patron == 1) {
      a[1][2] = 1;
      a[2][3] = 1;
      a[3][1] = 1;
      a[3][2] = 1;
      a[3][3] = 1;
    }

    if (patron == 2) {
      a[10][9] = 1;
      a[10][10] = 1;
      a[10][11] = 1;
    }

    if (patron == 3) {
      a[10][11] = 1;
      a[10][12] = 1;
      a[10][13] = 1;
      a[11][10] = 1;
      a[11][11] = 1;
      a[11][12] = 1;
    }

    if (patron == 4) {
      a[10][11] = 1;
      a[10][14] = 1;
      a[11][10] = 1;
      a[12][10] = 1;
      a[12][14] = 1;
      a[13][10] = 1;
      a[13][11] = 1;
      a[13][12] = 1;
      a[13][13] = 1;
    }

    if (patron == 5) {
      a[24][25] = 1;
      a[24][26] = 1;
      a[25][24] = 1;
      a[25][25] = 1;
      a[26][25] = 1;
    }
  }

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
            b[i][j] = 0;
          } else {
            b[i][j] = 1;
          }
        } else {
          if (vecinos == 3) {
            b[i][j] = 1;
          } else {
            b[i][j] = 0;
          }
        }
      }
    }

    for (i = 0; i < TAM; i++) {
      for (j = 0; j < TAM; j++) {
        a[i][j] = b[i][j];
      }
    }

    usleep(100000);
  }

  return 0;
}