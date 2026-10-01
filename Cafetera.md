```mermaid
flowchart TD
    %% BLOQUE 1: INICIO E INICIALIZACIÓN
    A([Inicio]) --> B[Inicializar Inventario hardware\ny Menú de Bebidas menu]
    B --> C[Definir opcion = -1]

    %% BLOQUE 2: MENÚ Y SELECCIÓN
    C --> D{¿opcion != 0?}
    D -- No --> E([Fin: Apagar Cafetera])
    D -- Sí --> F[Mostrar Menú de Bebidas]
    F --> G[/Leer opción del usuario/]
    
    G --> H{¿opcion == 0?}
    H -- Sí --> E
    H -- No --> I{¿opcion < 1 o opcion > 6?}
    I -- Sí (Inválida) --> J[/Mostrar error/] --> D
    I -- No (Válida) --> K[Obtener Bebida elegida = menu[opcion - 1]]

    %% BLOQUE 3: EXTRAS Y VALIDACIÓN DE INSUMOS
    K --> L[/Pedir leche extra (0 a 15 ml)/]
    L --> M{¿Leche válida?}
    M -- No --> L
    M -- Sí --> N[/Pedir azúcar extra (0 a 10 g)/]
    N --> O{¿Azúcar válida?}
    O -- No --> N
    O -- Sí --> P[Calcular lecheTotal = base + extra]

    P --> Q{¿hardware tiene\ninsumos suficientes?}
    Q -- No --> R[/Mostrar 'Insumos insuficientes'/] --> D
    
    %% BLOQUE 4: COBRO, CAMBIO Y ENTREGA
    Q -- Sí --> S[/Leer monedas ingresadas: m5U, m2U, m1U/]
    S --> T[Calcular montoTotal]
    T --> U{¿montoTotal >= precio?}
    U -- No --> V[/Mostrar 'Monto insuficiente'/] --> D

    U -- Sí --> W[Calcular cambio = montoTotal - precio]
    W --> X[Sumar monedas del usuario a la caja]
    X --> Y[Calcular cambio exacto con algoritmo Greedy:\nusar monedas de $5, $2 y $1]
    
    Y --> Z{¿Se entregó\ncambio exacto?}
    Z -- No --> AA[Restar monedas del usuario de la caja] --> AB[/Mostrar 'Cambio insuficiente'/] --> D
    
    Z -- Sí --> AC[Descontar insumos de la máquina]
    AC --> AD[Descontar monedas entregadas de la caja]
    AD --> AE[/Entregar Bebida y Cambio/]
    AE --> D
```
