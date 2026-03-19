; Comentário (;)
; Modelo TASM [Turbo Assembler]
; Programa que lê (LER_UINT16) e escreve (ESC_UINT16)
; um número de 16 bits sem sinal
.model small ; Separa em um segmento de código e outro de dados

.stack 100H   ; define uma pilha de 256 bytes (100H)

.data 
    CR EQU 13 ; define uma constante de valor 13 (Carriage Return)
    LF EQU 10 ; define uma constante de valor 10 (Line Feed)
	
.code
; Lê um caractere do teclado sem mostra-lo 
; Devolve o caractere lido em AL
LER_CHAR proc 
	mov AH, 7
    int 21H   
    ret       
endp
  
; Escreve na tela um caractere armazenado em DL     
ESC_CHAR proc
	push AX    ; salvar o reg AX
	mov AH, 2
	int 21H
	pop AX     ; restaurar o reg AX
	ret  
endp   
   
; Escreve na tela um inteiro sem sinal    
; de 16 bits armazenado no registrador AX
ESC_UINT16 proc 
    push AX      ; Salvar registradores utilizados na proc
    push BX
    push CX
    push DX 
       
    mov BX, 10   ; divisões sucessivas por 10
    xor CX, CX   ; contador de dígitos
      
LACO_DIV:
    xor DX, DX   ; zerar DX pois o dividendo é DXAX
    div BX       ; divisÃ£o para separar o dígito em DX
    
    push DX      ; empilhar o dígito
    inc CX       ; incrementa o contador de dígitos
     
    cmp AX, 0    ; AX chegou a 0?
    jnz LACO_DIV ; enquanto AX diferente de 0 salte para LACO_DIV
    
 LACO_ESCDIG:   
    pop DX       		; desempilha o dígito    
    add DL, '0'  		; converter o dígito para ASCII
    call ESC_CHAR               
    loop LACO_ESCDIG    ; decrementa o contador de dígitos
    
    pop DX       		; Restaurar registradores utilizados na proc
    pop CX
    pop BX
    pop AX
    ret     
endp   

; Lê um inteiro de 16 bits sem sinal do teclado
; Devolve o valor lido em AX
LER_UINT16 proc  
	; Salvar registradores utilizados na proc
	push BX
	push CX
	push DX 

	; inicializar os registradores
	xor AX, AX 
	xor CX, CX
	mov BX, 10
 
LER_UINT16_SALVA:
	push AX    ; salvando o acumulador
	  
	LER_UINT16_LEITURA:       
		call LER_CHAR           ; ler o caractere (sem mostrar)

		cmp AL, CR              ; verifica se eh ENTER
		jz LER_UINT16_FIM  ; jz == je

		cmp AL, '0'             ; verificar se eh valido
		jb LER_UINT16_LEITURA 

		cmp AL, '9'
		ja LER_UINT16_LEITURA 

		mov DL, AL      ; escrever o caractere na tela
		call ESC_CHAR

		sub DL, '0'     ; transforma o caractere em valor ('3' -> 3)

		pop AX          ; restaurando o acumulador 
		push DX         ; salvar DX

		mul BX          ; deslocamento esquerda do número para a soma   

		pop DX
		add AX, DX

		jmp LER_UINT16_SALVA

	LER_UINT16_FIM: 
		pop AX          ; restaurando o acumulador 

		mov DL, CR      ; Dar um enter após a leitura          
		call ESC_CHAR
		mov DL, LF             
		call ESC_CHAR

		; Restaurar registradores utilizados na proc
		pop DX
		pop CX
		pop BX

		ret
endp  
    
INICIO:		; Não é palavra reservada, pode ser 'inicio', 'main', 'start', 'runner'
	; Configuração do DS
	mov AX, @DATA
	mov DS, AX 

	call LER_UINT16
	call ESC_UINT16 

	; Finalização do programa
	mov AH, 4CH   
	int 21H	; Chama uma interrupção
 end INICIO