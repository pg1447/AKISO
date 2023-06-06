	global	main
	extern	printf

	section	.text
main:	
	mov eax, 2		;wartość początkowa eax = 2

pomocnicza:			;zapisz w esi liczbę pierwszą
	mov esi, eax		;znalezioną w poprzedniej iteracji

nextx:
	
	add eax,1		;kolejna liczba do sprawdzenia

				
	cmp eax, 10000		;czy wartosc maksymalna osiągnięta
	jne sito1		;jeśli nie - kontynuuj
	ret 			;koniec programu 

sito1:				
	push eax		;zachowaj stare eax
	mov ecx,2		;dzielnik
	mov edx,0		;reszta z dzielenia
	div ecx			;eax=eax:ecx
	mov ecx,eax		;wynik przenieś do ecx
	pop eax			;przywróć stare eax

	mov ebx,2 		;ustawienie licznika na 2

sito2:
				;modulo
	mov edx, 0		;edx to reszta
	push eax		;zachowaj stare eax
	div ebx			;dziel
	pop eax			;przywróć stare eax

				
	cmp edx,0		;sprawdzenie czy reszta == 0 
	je nextx 		;jeśli tak - nie jest to l. pierwsza
				;-> szukaj dalej.
	add ebx,1		;dzielnik + 1

				
	cmp ebx,ecx		;sprawdzenie czy ebx==ecx
	jle sito2		;jeśli nie - kontynuuj pętlę
	jmp para		;jeśli tak - sprawdź czy bliźniacza

	

para:	mov edi, eax		;kopiuj eax do edi
	sub edi, esi		;sprawdź czy różnica wynosi 2
	cmp edi, 2
	
	jne pomocnicza		;jeśli nie -> skocz i szukaj dalej
	
	
	

	;jesli petla skonczona, otrzymujemy parę liczb bliźniaczych
	push eax	;większa
	push esi	;mniejsza
	push message
	call printf

	add esp, 8	;czyszczenie stosu
	
	pop eax		;przywróć stare eax
	
	mov esi,eax	;ustal nową mniejszą liczbę pierwszą
	jmp nextx

message:
	db "%d, %d", 10, 0
