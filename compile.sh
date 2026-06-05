#!/bin/bash

# Configuración
CC=gcc
ASM=nasm
CFLAGS="-Wall -Wextra -O2"
LDFLAGS=""

# Crear directorio de salida
mkdir -p build

# Compilar archivos C
for file in src/*.c; do
    obj="build/$(basename "${file%.c}.o")"
    echo "Compilando C: $file"
    $CC $CFLAGS -c "$file" -o "$obj" || exit 1
done

# Compilar archivos NASM (64 bits ELF)
for file in src/*.asm; do
    obj="build/$(basename "${file%.asm}.o")"
    echo "Compilando ASM: $file"
    $ASM -f elf64 "$file" -o "$obj" || exit 1
done

# Enlazar ejecutable
echo "Enlazando..."
$CC build/*.o $LDFLAGS -o build/programa || exit 1

echo "Compilación completada."
echo "Ejecutable: build/programa"
