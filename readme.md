# Advent of Code 2025

Hola! Este repo contiene todas mis soluciones para el evento de programación **Advent of Code 2025**.

Autor: **Jose Gabriel Hernandez**

---

## ✨ Resumen Rápido

* Evento global de programación, 25 días, 2 problemas por día.
* Resolví los 12 primeros días completos (24 estrellas ⭐).
* Todo hecho en **C++** con enfoque en claridad y simulación directa.
* En algunos días usé **Excalidraw** para visualizar problemas (grillas, grafos, etc).

---

## Progreso

| Día | Nombre              | ⭐ Parte 1 | ⭐ Parte 2 |
| --- | ------------------- | --------- | --------- |
| 1   | Secret Entrance     | ⭐         | ⭐         |
| 2   | Gift Shop           | ⭐         | ⭐         |
| 3   | Lobby               | ⭐         | ⭐         |
| 4   | Printing Department | ⭐         | ⭐         |
| 5   | Cafeteria           | ⭐         | ⭐         |
| 6   | Trash Compactor     | ⭐         | ⭐         |
| 7   | Laboratories        | ⭐         | ⭐         |
| 8   | Playground ✨        | ⭐         | ⭐         |
| 9   | Movie Theater       | ⭐         | ⭐         |
| 10  | Factory             | ⭐         | ⭐         |
| 11  | Reactor             | ⭐         | ⭐         |
| 12  | Christmas Tree Farm | ⭐         | ⭐         |

**Total:** 24 estrellas ✨

---

## Tecnología usada

* Lenguaje: **C++** (100%)
* Estructuras comunes: `structs`, simulaciones paso a paso, grillas, recorridos BFS/DFS.
* Optimizado para legibilidad, no performance extrema.
* Algunas visualizaciones hechas con **Excalidraw**.

---

## Organización del repo

Cada día tiene su propia carpeta:

```
/day01
  ├── main.cpp
  ├── input.txt
  └── (opcional) diagramas/*.excalidraw
```

---

## Ejemplo de enfoques

* **Día 1:** Dial circular modelado con lista doble enlazada.
* **Día 2:** Parsing de strings sin `stoi`, con ASCII manual.
* **Día 6:** Interpretación de grilla vertical con operadores +/*.
* **Día 8 (Playground):** ✨

  * Se trabajó sobre estructuras de grafos, con visualización en Excalidraw para entender conexiones.
  * Parte 1: Conexión de 1000 pares más cercanos y análisis de componentes conexas.
  * Parte 2: Union-Find optimizado con path compression y multiplicación de coordenadas.
  * Incluye exportación de conexiones y agrupamientos a archivos `output.txt`, `output2.txt` y `grupos.txt`.
  * Solución visualizada con diagrama (ver imagen incluida en este repo).

---

## Por qué importa

Este evento no solo es divertido, también entrena:

* Pensamiento algorítmico
* Modelado de problemas
* Escritura de código limpio y mantenible
* Habilidades para entrevistas técnicas y competencias

---

Gracias por pasar ✨

> PD: Si querés saber más de mi forma de pensar, mirar el código de Advent of Code es una buena puerta de entrada. Pero si querés ver proyectos más complejos y reales, pasate por mi perfil: https://github.com/GyabiSito