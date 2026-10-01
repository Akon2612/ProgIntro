#include <stdio.h>

typedef struct {
  char nombre[20];
  int precio;
  int cafe;
  int chocolate;
  int leche;
  int agua;
} Bebida;

typedef struct {
  int cafe;
  int leche;
  int agua;
  int chocolate;
  int azucar;
  int m5;
  int m2;
  int m1;
} Cafetera;

int main(void) {
  Cafetera hardware = {
      .cafe = 500,
      .leche = 800,
      .agua = 800,
      .chocolate = 300,
      .azucar = 500,
      .m5 = 20,
      .m2 = 20,
      .m1 = 20,
  };

  Bebida menu[6] = {
      {"Espresso", 35, 30, 0, 0, 30},   {"Latte", 42, 30, 0, 30, 50},
      {"Capuccino", 25, 40, 0, 10, 50}, {"Americano", 46, 50, 0, 0, 50},
      {"Chocolate", 53, 0, 40, 30, 50}, {"Moka", 52, 20, 20, 30, 50}};
  int opcion = -1;

  while (opcion != 0) {
    printf("\n");
    printf("           Menú de la Cafetera            ");
    printf("\n");

    for (int i = 0; i <= 5; i++) {
      printf("%d. %s - $%d\n", i + 1, menu[i].nombre, menu[i].precio);
    }
    printf("0. Apagar cafetera\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    if (opcion == 0) {
      printf("Cerrando cafetera. ¡Hasta luego!\n");
      break;
    }

    if (opcion < 1 || opcion > 6) {
      printf("Opción Inválida. Por favor, inténtelo de nuevo.");
      continue;
    }

    Bebida elegida = menu[opcion - 1];
    int lecheExtra = 0;
    int azucarExtra = 0;

    do {
      printf("¿Cuantos ml de leche extra desea? (0 a 15 ml): ");
      scanf("%d", &lecheExtra);
      if (lecheExtra < 0 || lecheExtra > 15) {
        printf("La cantidad debe ser entre 0 y 15 ml.\n");
      }
    } while (lecheExtra < 0 || lecheExtra > 15);

    do {
      printf("¿Cuantos g de azúcar extra desea? (0 a 10 g): ");
      scanf("%d", &azucarExtra);
      if (azucarExtra < 0 || azucarExtra > 15) {
        printf("La cantidad debe ser entre 0 y 10 g.\n");
      }
    } while (azucarExtra < 0 || azucarExtra > 15);

    int lecheTotal = elegida.leche + lecheExtra;

    if (hardware.cafe < elegida.cafe || hardware.leche < lecheTotal ||
        hardware.agua < elegida.agua ||
        hardware.chocolate < elegida.chocolate ||
        hardware.azucar < azucarExtra) {
      printf("Disculpe, no hay insumos suficientes para preparar su %s.\n.",
             elegida.nombre);
      continue;
    }

    int m5U = 0, m2U = 0, m1U = 0;
    printf("\nEl precio de su %s es de $%d.\n", elegida.nombre, elegida.precio);
    printf("Ingrese cantidad de monedas de $5: ");
    scanf("%d", &m5U);
    printf("Ingrese cantidad de monedas de $2: ");
    scanf("%d", &m2U);
    printf("Ingrese cantidad de monedas de $1: ");
    scanf("%d", &m1U);

    int montoTotal = (m5U * 5) + (m2U * 2) + (m1U * 1);

    if (montoTotal < elegida.precio) {
      printf("El dinero introducido es insuficiente");
      continue;
    }

    int cambio = montoTotal - elegida.precio;
    hardware.m5 += m5U;
    hardware.m2 += m2U;
    hardware.m1 += m1U;

    int restante = cambio;
    int dar5 = 0, dar2 = 0, dar1 = 0;

    while (restante >= 5 && hardware.m5 > 0) {
      dar5++;
      hardware.m5--;
      restante -= 5;
    }
    while (restante >= 2 && hardware.m2 > 0) {
      dar2++;
      hardware.m2--;
      restante -= 2;
    }
    while (restante >= 1 && hardware.m1 > 0) {
      dar1++;
      hardware.m1--;
      restante -= 1;
    }

    if (restante > 0) {
      hardware.m5 -= m5U;
      hardware.m2 -= m2U;
      hardware.m1 -= m1U;

      printf("Cambio insuficiente, Se devuelven sus monedas. Intente con un "
             "monto menor");
      continue;
    }

    hardware.cafe -= elegida.cafe;
    hardware.leche -= lecheTotal;
    hardware.agua -= elegida.agua;
    hardware.chocolate -= elegida.chocolate;
    hardware.azucar -= azucarExtra;

    printf("¡Su %s está listo!\n", elegida.nombre);
    if (cambio > 0) {
      printf("Su cambio de $%d se entrega así:\n", cambio);
      printf("  - Monedas de $5: %d\n", dar5);
      printf("  - Monedas de $2: %d\n", dar2);
      printf("  - Monedas de $1: %d\n", dar1);
    } else {
      printf("Pago exacto. ¡Gracias por su compra!\n");
    }
  }
  return 0;
}