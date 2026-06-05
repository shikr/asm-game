bits 64
default rel

global contar_monedas_NASM
section .text

contar_monedas_NASM: ;esi=totalCeldas --- dl=monedaChar --- rdi=inicioMapa
    xor eax, eax ;contador de monedas
    xor ecx, ecx ;contador para recorrer la matriz

    .bucle:
        ;ve si ya llego al final de la matriz
        cmp ecx, esi
        jge .fin

        ;ve si el caracter es el de la moneda
        mov bl, [rdi + rcx]
        cmp bl, dl
        jne .siguiente ;si no es igual pasa a el siguiente caracter

        inc eax ;si si es igual incrementa el numero de monedas

    .siguiente:
        inc ecx
        jmp .bucle

    .fin:
        ret
