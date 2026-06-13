bits 64
default rel

global contar_monedas_NASM
global validar_movimiento_NASM
global calcular_puntaje_NASM
section .text

;;---------------------------------------------------------------------------;;
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
;;---------------------------------------------------------------------------;;
validar_movimiento_NASM: ;rdi=inicioMapa --- esi=columnas --- edx=nuevaFila --- ecx=nuevaColumna
    ;calcular el offset de la nueva posicion (nuevaFila * columnas)+nuevaColumna
    mov eax, edx
    imul eax, esi
    add eax, ecx

    ;guarda el caracter en al
    mov al, [rdi+rax]
    cmp al,'#' ;checa si es pared
    je .true ;si si es devuelve 1

    mov eax,0 ;si no, devuelve 0
    ret 

    .true:
        mov eax,1
        ret
;;---------------------------------------------------------------------------;;
calcular_puntaje_NASM: ;edi=monedasColectadas --- esi=pasos --- edx=niveles | formula: cada moneda es un punto, por cada 50 pasos se resta una moneda y por cada nivel se suman 10 puntos
    ;mover parametros a registros de proposito general
     mov r8d, edi ;monedas
     mov r9d, esi ;pasos
     mov r10d, edx ;niveles

    ;calcular lo que se resta por pasos
    xor eax, eax
    xor edx, edx
    mov eax, r9d ;eax = pasos
    mov ecx, 30 ;ecx = 30
    div ecx ;eax = pasos/30
    cmp eax, r8d ;si el puntaje queda negativo solo lo  hace 0
    jg .hacerCero

    sub r8d, eax ;rd8 = puntaje -= eax

    .hacerCero:
        xor r8d, r8d

    ;calcular puntos extra por nivel
    mov eax, r10d ;eax = niveles
    mov ecx, 10 ;exc = 100;
    mul ecx ;eax = niveles * 50

    ;aplicar puntos extra
    add r8d, eax
    mov eax, r8d

    ret
;;---------------------------------------------------------------------------;;
