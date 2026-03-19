.model small

.stack 100H

.data

.code

TOLOWER proc
    cmp AL,'A'
    jb FIM_TOLOWER
    cmp AL, 'Z'
    ja FIM_TOLOWER
    
    add AL,20H
    
FIM_TOLOWER:
    ret
endp

inicio:
    mov AX, @DATA
    mov DS, AX
          
    mov AL,'A'
    call TOLOWER
          
    mov AH, 4CH
    int 21H
end inicio