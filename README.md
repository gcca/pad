# Pad

Un bloc de notas para pensar con números.

```
┌─────────────────────────────────────────────┐
│                     Pad                     │
├─────────────────────────────────────────────┤
│                                             │
│  sqrt(54 + 32)/(23 - 1)  =  0.334…          │
│  150 kg to lb            =  330.693 lb      │
│  45 USD to EUR           =  41.27 EUR       │
│                                             │
│                                             │
│                                             │
├─────────────────────────────────────────────┤
│  12 * (3 + 7)                               │
└─────────────────────────────────────────────┘
       ↑                          ↑
    entrada                 vista previa
```

## El problema

Las calculadoras son demasiado simples o demasiado complejas.
Las simples no manejan expresiones anidadas.
Las complejas te entierran en menús y modos.

A veces solo necesitas un lugar donde escribir una idea
y ver la respuesta — como garabatear en el reverso
de una servilleta, pero una que hace las cuentas por ti.

## Cómo funciona

Escribes. Obtienes respuestas. Una línea a la vez.

```
Escribes                          Ves
────────                          ───
sqrt(144)                          sqrt(144)  =  12
2 * (3 + 4)                      2 * (3 + 4)  =  14
100 / 3                              100 / 3  =  33.333…
```

Presionas enter y el resultado se queda.
El pad recuerda cada línea —
un historial continuo de tus cálculos.

Mientras escribes, la respuesta aparece de inmediato,
tenue, como trazos de lápiz antes de pasar a tinta.

## Qué hará

```
              ┌──────────────┐
              │  Aritmética  │
              │   2 + 2 = 4  │
              └──────┬───────┘
                     │
        ┌────────────┼────────────┐
        │            │            │
  ┌─────┴─────┐  ┌───┴────┐  ┌────┴─────┐
  │ Funciones │  │Unidades│  │ Monedas  │
  │ sqrt, sin │  │ kg→lb  │  │ USD→EUR  │
  │ log, abs  │  │ km→mi  │  │ BTC→PEN  │
  └───────────┘  └────────┘  └──────────┘
```

- **Expresiones** — Aritmética con anidamiento, precedencia de operadores
  y las funciones que esperas.

- **Conversión de unidades** — Escribe con naturalidad.
  `150 kg to lb` o `26.2 mi in km`.

- **Conversión de monedas** — Tasas en tiempo real.
  `500 USD to EUR` se actualiza con datos reales.

- **Historial** — Cada línea que ingresas se queda en el pad.
  Desplázate hacia atrás. Copia lo que necesites.

## Por qué un pad

No es una calculadora. No es una hoja de cálculo. Es un pad.

Escribes en él. Él te responde.

## Licencia

[AGPL-3.0](LICENSE)
