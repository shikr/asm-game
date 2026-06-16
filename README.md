# Laberinto en ensamblador x86-64

Este proyecto es un juego de laberinto desarrollado usando C y NASM. El objetivo del juego es que el jugador navegue a través de un laberinto para encontrar la salida. El juego se ejecuta en la terminal y utiliza caracteres ASCII para representar el laberinto y al jugador.

## Requisitos

- NASM (Netwide Assembler)
- GCC (GNU Compiler Collection)
- Make
- Un sistema operativo Linux

## Compilación

Lo primero es obtener el código fuente del proyecto. Puedes clonar el repositorio, junto a sus **dependencias**, usando el siguiente comando:

```bash
git clone --recurse-submodules https://github.com/shikr/asm-game.git
cd asm-game
```

Para compilar el juego, simplemente ejecuta el siguiente comando en la terminal:

```bash
make
```

A partir de aquí, el comando `make` compilará el código fuente en ensamblador y el código en C, generando un ejecutable llamado `game` ubicado en el directorio `build`.

## Ejecución

Para ejecutar el juego, es posible usar los siguientes métodos:

### Usando make

Este método compila el juego (si no se ha compilado previamente) y luego lo ejecuta:

```bash
make run
```

### Ejecutando directamente el binario

Para ejecutar el juego directamente, es necesario tener el binario compilado. Si ya has ejecutado `make` y el binario está disponible, puedes ejecutar el juego con el siguiente comando:

```bash
./build/game
```
