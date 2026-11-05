#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100    // lado de la carita normal (100x100)
#define NR 20    // lado de la carita reducida (20x20)
#define BLOQUE 5 // 100 / 20 = 5: cada casilla reducida resume 5x5 casillas

//  1) GENERAR LA CARITA

// Llena la matriz 'a' (100x100) con el dibujo de la cara.
void generar_cara(char a[N][N]) {
  int i, j;
  double d1, d2; // distancias con decimales (double)

  // Datos de cada parte de la cara
  int coY1 = 30, coX1 = 35;                       // ojo izquierdo (centro)
  int coY2 = 30, coX2 = 65;                       // ojo derecho (centro)
  int r = 8;                                      // radio de los ojos
  int itop = 45, ibottom = 55, jcenter = 50;      // nariz (triángulo)
  int imin = 65, imax = 75, jmin = 15, jmax = 80; // boca (rectángulo)

  // Recorremos TODAS las casillas: i = fila, j = columna
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {

      // Distancia de esta casilla al centro de cada ojo
      d1 = sqrt((i - coY1) * (i - coY1) + (j - coX1) * (j - coX1));
      d2 = sqrt((i - coY2) * (i - coY2) + (j - coX2) * (j - coX2));

      if ((d1 <= r) || (d2 <= r) ||
          ((i >= itop) && (i <= ibottom) && (abs(j - jcenter) <= (i - itop))) ||
          ((i >= imin) && (i <= imax) && (j >= jmin) && (j <= jmax))) {
        // Si la casilla cae dentro de un ojo, la nariz o la boca: 'O'
        a[i][j] = 'O';
      } else {
        // Si no, vemos si está en el borde de la matriz
        if ((i == 0) || (i == N - 1) || (j == 0) || (j == N - 1)) {
          a[i][j] = 'X';
        } else {
          a[i][j] = ' ';
        }
      }
    }
  }
}

//  2) TRANSFORMACIONES

// Gira la matriz 'src' y guarda el resultado en 'dst'.
//   n      = lado de la matriz (100 normalmente)
//   angulo = 0, 90, 180 o 270
void rotar(char src[N][N], char dst[N][N], int n, int angulo) {
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      if (angulo == 90) {
        dst[i][j] = src[n - 1 - j][i];
      } else if (angulo == 180) {
        dst[i][j] = src[n - 1 - i][n - 1 - j];
      } else if (angulo == 270) {
        dst[i][j] = src[j][n - 1 - i];
      } else {
        // 0 grados: copia tal cual
        dst[i][j] = src[i][j];
      }
    }
  }
}

// Reduce una matriz de 100x100 a una de 20x20.
// Divide la grande en bloques de 5x5. Si dentro del bloque hay
// algún 'O' o 'X', la casilla reducida toma ese símbolo.
void reducir(char src[N][N], char dst[N][N]) {
  int i, j;   // posición en la matriz reducida (20x20)
  int bi, bj; // posición dentro del bloque de 5x5
  char simbolo, c;

  for (i = 0; i < NR; i++) {
    for (j = 0; j < NR; j++) {

      simbolo = ' '; // empezamos suponiendo que el bloque está vacío

      for (bi = 0; bi < BLOQUE; bi++) {
        for (bj = 0; bj < BLOQUE; bj++) {
          // fila real = i*5 + bi, columna real = j*5 + bj
          c = src[i * BLOQUE + bi][j * BLOQUE + bj];
          if (c == 'O' || c == 'X') {
            simbolo = c;
          }
        }
      }

      dst[i][j] = simbolo;
    }
  }
}

// Aplica lo que eligió el usuario (rotación y tamaño) a la carita base.
// Deja el resultado en 'salida' y DEVUELVE su lado (100 o 20).
int construir(char base[N][N], int angulo, int reducida, char salida[N][N]) {
  char rotada[N][N];

  // Primero rotamos...
  rotar(base, rotada, N, angulo);

  // ...y luego reducimos, si el usuario lo pidió
  if (reducida == 1) {
    reducir(rotada, salida);
    return NR;
  } else {
    // Copiamos 'rotada' a 'salida' casilla por casilla
    int i, j;
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        salida[i][j] = rotada[i][j];
      }
    }
    return N;
  }
}

//  3) SALIDA EN PANTALLA

// Imprime una matriz de n x n
void imprimir(char m[N][N], int n) {
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      printf("%c", m[i][j]);
    }
    printf("\n"); // salto de línea al terminar cada fila
  }
}

//  4) GUARDAR COMO IMAGEN BMP

//  Un BMP es un archivo con:
//    - una cabecera de 54 bytes (tamaño, colores, etc.)
//    - los píxeles, en orden BGR (azul, verde, rojo), de ABAJO hacia ARRIBA
//  Los números de más de 1 byte se guardan "al revés" (byte menos
//  significativo primero). Por eso existen las dos funciones de abajo.

// Escribe un número de 2 bytes en el archivo
void escribir_u16(FILE *f, unsigned int v) {
  fputc(v & 0xFF, f);        // byte menos significativo
  fputc((v >> 8) & 0xFF, f); // byte siguiente
}

// Escribe un número de 4 bytes en el archivo
void escribir_u32(FILE *f, unsigned int v) {
  fputc(v & 0xFF, f);
  fputc((v >> 8) & 0xFF, f);
  fputc((v >> 16) & 0xFF, f);
  fputc((v >> 24) & 0xFF, f);
}

// Guarda la matriz 'm' (n x n) como imagen BMP.
// 'escala' = cuántos píxeles ocupa cada casilla (la hace más grande).
// Devuelve 1 si se guardó bien, 0 si hubo error.
int guardar_bmp(char m[N][N], int n, char ruta[], int escala) {
  FILE *f;
  int lado, relleno, x, y, p;
  unsigned int tam_datos;
  unsigned char b, g, r;
  char c;

  f = fopen(ruta, "wb"); // "wb" = escribir en modo binario
  if (f == NULL) {
    return 0; // no se pudo crear el archivo
  }

  lado = n * escala; // ancho y alto de la imagen en píxeles

  // BMP exige que cada fila de píxeles ocupe un múltiplo de 4 bytes.
  // Cada píxel usa 3 bytes, así que calculamos cuántos bytes de relleno faltan
  relleno = (4 - (lado * 3) % 4) % 4;

  tam_datos = (lado * 3 + relleno) * lado; // bytes totales de píxeles

  // ----- Cabecera del archivo (14 bytes) -----
  fputc('B', f); // firma "BM"
  fputc('M', f);
  escribir_u32(f, 54 + tam_datos); // tamaño total del archivo
  escribir_u32(f, 0);              // reservado
  escribir_u32(f, 54);             // dónde empiezan los píxeles

  // ----- Cabecera de la imagen (40 bytes) -----
  escribir_u32(f, 40);        // tamaño de esta cabecera
  escribir_u32(f, lado);      // ancho
  escribir_u32(f, lado);      // alto
  escribir_u16(f, 1);         // planos (siempre 1)
  escribir_u16(f, 24);        // bits por píxel: 24 = color real
  escribir_u32(f, 0);         // sin compresión
  escribir_u32(f, tam_datos); // tamaño de los datos
  escribir_u32(f, 2835);      // resolución horizontal
  escribir_u32(f, 2835);      // resolución vertical
  escribir_u32(f, 0);         // colores en paleta (no aplica)
  escribir_u32(f, 0);         // colores importantes (no aplica)

  // ----- Píxeles -----
  // BMP guarda las filas de abajo hacia arriba, por eso y baja de lado-1 a 0
  for (y = lado - 1; y >= 0; y--) {
    for (x = 0; x < lado; x++) {

      // Pixel (x, y) de la imagen -> casilla de la matriz.
      // Dividir entre 'escala' hace que varios píxeles vecinos
      // copien la misma casilla (así se agranda la imagen).
      c = m[y / escala][x / escala];

      if (c == 'O') { // cara: gris oscuro
        b = 40;
        g = 40;
        r = 40;
      } else if (c == 'X') { // borde: azul
        b = 200;
        g = 120;
        r = 40;
      } else { // fondo: blanco
        b = 255;
        g = 255;
        r = 255;
      }

      // Se escribe en orden BGR
      fputc(b, f);
      fputc(g, f);
      fputc(r, f);
    }

    // Bytes de relleno al final de cada fila
    for (p = 0; p < relleno; p++) {
      fputc(0, f);
    }
  }

  fclose(f);
  return 1;
}

//  5) INTERFAZ (menús y lectura de datos)

// Borra la pantalla usando una secuencia especial de la terminal
void limpiar_pantalla(void) { printf("\033[2J\033[H"); }

// Muestra 'mensaje' y pide un número entero entre min y max.
// Si el usuario escribe algo inválido, vuelve a preguntar.
// Devuelve -1 si ya no hay más entrada (por ejemplo, Ctrl+D).
int leer_entero(char mensaje[], int min, int max) {
  char linea[64];
  int valor;
  int valido = 0;

  while (valido == 0) {
    printf("%s", mensaje);

    // fgets lee una línea completa de texto; si falla, no hay más entrada
    if (fgets(linea, 64, stdin) == NULL) {
      return -1;
    }

    // sscanf intenta convertir ese texto a número.
    // Devuelve 1 si lo logró.
    if (sscanf(linea, "%d", &valor) == 1 && valor >= min && valor <= max) {
      valido = 1;
    } else {
      printf("  Opción inválida (%d-%d). Intenta de nuevo.\n", min, max);
    }
  }

  return valor;
}

// Pide un nombre de archivo. Si el usuario solo presiona ENTER,
// se usa el nombre 'defecto'. El resultado queda en 'dest'.
void leer_nombre(char mensaje[], char defecto[], char dest[], int tam) {
  int i;

  printf("%s [%s]: ", mensaje, defecto);

  if (fgets(dest, tam, stdin) == NULL || dest[0] == '\n') {
    strcpy(dest, defecto); // copia el nombre por defecto
  } else {
    // fgets deja el '\n' al final; lo buscamos y lo cambiamos por '\0'
    i = 0;
    while (dest[i] != '\0' && dest[i] != '\n') {
      i++;
    }
    dest[i] = '\0';
  }
}

// Dibuja el menú principal mostrando la configuración actual
void mostrar_menu(int angulo, int reducida) {
  printf("╔══════════════════════════════════════════╗\n");
  printf("║            CARITA   -   MENÚ             ║\n");
  printf("╠══════════════════════════════════════════╣\n");
  printf("║  Rotación actual : %3d°                  ║\n", angulo);
  if (reducida == 1) {
    printf("║  Tamaño actual   : 20x20   "
           "              ║\n");
  } else {
    printf("║  Tamaño actual   : 100x100 "
           "              ║\n");
  }
  printf("╠══════════════════════════════════════════╣\n");
  printf("║  1) Cambiar rotación                     ║\n");
  printf("║  2) Cambiar tamaño                       ║\n");
  printf("║  3) Ver carita en pantalla               ║\n");
  printf("║  4) Guardar como imagen (BMP)            ║\n");
  printf("║  0) Salir                                ║\n");
  printf("╚══════════════════════════════════════════╝\n");
}

// Pregunta la rotación y la guarda en *angulo.
// Se recibe un puntero (int *) para poder MODIFICAR la variable
// original del main.
void menu_rotacion(int *angulo) {
  int op;

  printf("\n  1) 0°   2) 90°   3) 180°   4) 270°\n");
  op = leer_entero("  Rotación: ", 1, 4);

  if (op > 0) {
    *angulo = (op - 1) * 90; // 1->0, 2->90, 3->180, 4->270
  }
}

// Pregunta el tamaño y lo guarda en *reducida (0 = normal, 1 = reducida)
void menu_tamano(int *reducida) {
  int op;

  printf("\n  1) Normal (100x100)   2) Reducida (20x20)\n");
  op = leer_entero("  Tamaño: ", 1, 2);

  if (op == 1) {
    *reducida = 0;
  } else if (op == 2) {
    *reducida = 1;
  }
}

// Construye la carita según la configuración y la guarda como BMP
void accion_guardar_bmp(char base[N][N], int angulo, int reducida) {
  char m[N][N];
  char nombre[200];
  int n, escala;

  n = construir(base, angulo, reducida, m);

  // Escala para que la imagen mida 400 px: 20*20 = 400 y 100*4 = 400
  if (reducida == 1) {
    escala = 20;
  } else {
    escala = 4;
  }

  leer_nombre("  Nombre del archivo", "carita.bmp", nombre, 128);

  // Si el nombre no contiene ".bmp", se lo agregamos
  if (strstr(nombre, ".bmp") == NULL) {
    strcat(nombre, ".bmp");
  }

  if (guardar_bmp(m, n, nombre, escala) == 1) {
    printf("  ✔ Imagen guardada: %s (%dx%d px)\n", nombre, n * escala,
           n * escala);
  } else {
    printf("  ✘ No se pudo guardar '%s'.\n", nombre);
  }
}

// Espera a que el usuario presione ENTER
void pausa(void) {
  char tmp[8];

  printf("\n  Presiona ENTER para continuar...");
  fgets(tmp, 8, stdin);
}

//  6) PROGRAMA PRINCIPAL

int main(void) {
  char base[N][N];  // la carita original, sin transformar
  char vista[N][N]; // la carita ya rotada/reducida, lista para mostrar
  int angulo = 0;   // rotación elegida: 0, 90, 180 o 270
  int reducida = 0; // 0 = tamaño normal, 1 = reducida
  int opcion;
  int n;
  int salir = 0; // cuando valga 1, el programa termina

  // Dibujamos la carita una sola vez al inicio
  generar_cara(base);

  // Bucle del menú: se repite hasta que el usuario elija salir
  while (salir == 0) {
    limpiar_pantalla();
    mostrar_menu(angulo, reducida);
    opcion = leer_entero("  Opción: ", 0, 4);

    if (opcion == 1) {
      menu_rotacion(&angulo); // '&' pasa la dirección de la variable

    } else if (opcion == 2) {
      menu_tamano(&reducida);

    } else if (opcion == 3) {
      n = construir(base, angulo, reducida, vista);
      printf("\n");
      imprimir(vista, n);
      pausa();

    } else if (opcion == 4) {
      accion_guardar_bmp(base, angulo, reducida);
      pausa();

    } else {
      // opcion == 0 (salir) o -1 (se acabó la entrada)
      printf("\n  ¡Hasta luego!\n");
      salir = 1;
    }
  }

  return 0;
}