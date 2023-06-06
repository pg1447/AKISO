
section .text

		;deklaracje funkcji
		global main
		global mult
		global factorial
		global printBigNumber

		extern printf
		extern scanf

mult:
		;tworzy nową ramkę stosu
		push ebp
		mov ebp, esp

		; edx bedzie uzywane do wyniku mnozenia
		; ebx bedzie mnoznikiem
		; ecx bedzie przechowywal 'carry' pomiedzy bajtami

		mov ebx,[ebp + 8]
		xor edx, edx 	;zerowanie

		;1 bajt
		mov eax,[bigNumber] ;najmłodszy bajt do rejestru eax
		mul ebx ; edx:eax = eax*ebx
		mov [bigNumber], eax
		mov ecx, edx ;przeniesienie miedzy bajtami

		;2 bajt
		mov eax, [bigNumber + 4]
		mul ebx
		add eax, ecx ;dodajemy przeniesinie
		mov[bigNumber + 4],eax
		mov ecx,edx

		;3 bajt
		mov eax, [bigNumber + 8]
		mul ebx
		add eax,ecx
		mov [bigNumber + 8], eax
		mov ecx,edx

		;4 bajt
		mov eax, [bigNumber + 12]
		mul ebx
		add eax,ecx
		mov [bigNumber + 12], eax

		leave 	;usuwa ramkę stosu
		ret 	;powrót do miejsca wywołania

factorial:
		
		;nowa ramka stosu
		push ebp	;zapisz stary base pointer (adres spodu stosu)
		mov ebp, esp	;nowy base pointer

		mov eax, [ebp + 8]	;wczytaj liczba do eax

		;sprawdzamy parzystość
		mov edi, eax	;kopiuj eax do edi
		and edi, 1	;
		cmp edi, 0 	;jeśli true to parzysta -> skok do etykiety
		je parzysta
		jne nieparzysta

nieparzysta:
mov ecx, 1
jmp loop


parzysta:
mov ecx, 2


		
		loop:
		cmp ecx,eax	;warunek - sprawdza czy mnożnik nie jest większy od liczby
		jg end		;jeśli większe -> skocz do end
		; zachowaj te wartosci ( rejestry sa uzywane w mult)
		push eax
		push ecx
		; mnoz przez ecx ( czyli 1 ... n )
		call mult  ;wywołaj funkcje mnożącą liczby
		;wez zapamietane wartosci z tej funkcji
		pop ecx
		pop eax
		inc ecx	 ;zwieksz mnoznik o 2
		inc ecx 
		jmp loop

		end:
		leave ;usun ramke stosu
		ret 	;powrot


printBigNumber:
		push ebp
		mov ebp, esp

		;sprawdź jak długa jest liczba
		cmp dword[bigNumber + 12], 0 ;jest zapisana na 4 bajtach
		jne inty4
		cmp dword[bigNumber + 8], 0 ;jest zapisana na 3 bajtach
		jne inty3
		cmp dword[bigNumber + 4], 0 ;jest zapisana na 2 bajtach
		jne inty2
				;jesli zadne z powyzszych tzn., ze jest 1-bajtowa
		int1:
		push dword[bigNumber]
		push printINT
		call printf
		jmp end2

		inty2:
		push dword[bigNumber]
		push dword[bigNumber + 4]
		push print2INT
		call printf
		jmp end2

		inty3:
		push dword[bigNumber]
		push dword[bigNumber + 4]
		push dword[bigNumber + 8]
		push print3INT
		call printf
		jmp end2

		inty4:
		push dword[bigNumber]		;najpierw najmłodszy bajt na stos
		push dword[bigNumber + 4]	;potem kolejne -> będą wypisywane		
		push dword[bigNumber + 8]	;w odwrotnej kolejnosci - LIFO
		push dword[bigNumber + 12]
		push print4INT			;drukuje liczbę
		call printf

		end2:
		leave
		ret

main:

		; wczytywanie 'n' i umiesczenie na stosie		
		push number;
		push scanINT;
		call scanf
		add esp,8
		push dword[number]

		call factorial

		call printBigNumber
		add esp, 4
		ret

section .data

		scanINT: db'%d',0

		printINT: db'%x',10,0

		print2INT: db'%x%x',10,0

		print3INT: db'%x%x%x',10,0

		print4INT: db'%x%x%x%x',10,0

		bigNumber dd 1,0,0,0 	;definiuje double word (4 bajty)
		; nasza liczba
		; [bigNumber] - najmlodsze bity, [bigNumber + 12] - najstarsze

section .bss

		number resb 4
