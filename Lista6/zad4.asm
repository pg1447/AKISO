	global main
	extern printf
	extern scanf

	section .data
	msg db "Podaj liczbe: ",0
	fmt db "%d",0
	liczba dd 0,0,0,1

	section .bss
	inpt resb 4

	section .text
main:
	push msg
	call printf
	add esp,4

	push inpt
	push fmt
	call scanf	;wczytanie liczby
	add esp,8

		;sprawdzenie czy niezaduza liczba
	cmp dword[inpt],34
	jle go1
	push errorh
	call printf
	add esp,4
	ret
go1:		;sprawdzenie czy mniejsza niz 0
        cmp dword[inpt],0
        jge go2
        push errorl
        call printf
        add esp,4
        ret
go2:

		;sprawdzenie czy jest 0
	cmp dword[inpt],0
	jne go3
	mov eax,1
	push 1
	push 0
	push 0
	push 0
	push message
	call printf
	add esp,20
	ret
go3:

	mov ecx,dword[inpt]	;ustawienie licznika petli
	mov edx,0

nexti:
	mov eax, [liczba+12]
	mul ecx
	mov [liczba+12], eax

	mov ebx, edx
        mov eax, [liczba+8]
        mul ecx
	add eax, ebx
        mov [liczba+8], eax

        mov ebx, edx
        mov eax, [liczba+4]
        mul ecx
        add eax, ebx
        mov [liczba+4], eax

        mov ebx, edx
        mov eax, [liczba]
        mul ecx
        add eax, ebx
        mov [liczba], eax

	cmp ecx,dword[inpt]
	loop nexti

	push dword[liczba+12]
        push dword[liczba+8]
        push dword[liczba+4]
        push dword[liczba]
	push message
	call printf
	add esp,20

ret

message:
	db "wynik: %x%x%x%x",10,0
errorh:
	db "Za duza liczba!",10,0
errorl:
	db "Za mala liczba!",10,0
