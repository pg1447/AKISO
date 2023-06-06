	global	main
	extern	printf

	section	.text
main:
	mov eax,1

nextx:
	add eax,1	;dodanie wartosci

	;czy wartosc maksymalna
	cmp eax,10000
	jne go		
	ret ; koniec programu 
go:
		;ustawienie konca petli ecx=eax/2
	push eax
	mov ecx,2
	mov edx,0
	div ecx
	mov ecx,eax
	pop eax

	mov ebx,2 	;ustawienie licznika na 2

nexti:
	;modulo
	mov edx, 0	;edx to reszta
	push eax
	div ebx
	pop eax

	;sprawdzenie czy reszta == 0 jesli tak to nextx
	cmp edx,0
	je nextx 	

	add ebx,1

	;sprawdzenie czy ebx==ecx jesli nie to nastepne zwieksz  
	cmp ebx,ecx
	jle nexti

	;jesli petla skonczona to jest to liczba 1 
	push eax
	push message
	call printf

	add esp,4 	;czyszczenie stosu
	pop eax
	jmp nextx

message:
	db "%d", 10, 0
