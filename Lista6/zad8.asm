section .text
		;deklaracje funkcji
		global main

		global ln
		global exp
		global pow2
		global sinh
		global sinh_1

		global printLN
		global printEXP
		global printSINH
		global printSINH_1

		extern printf
		extern scanf


; algorytm z wykladu
pow2:

		; potrzebujemy miejsca na (int)(x) i (frac)(x), zatem x wynosimy o 2miejsca
		fld st0
		fld st0
		frndint 	;zaokrąglenie do liczby całkowitej, st(0) = (int)(x), st(1) = x st(2) = x
		fxch st1 	;zamień st1 z st0: st(0) = x, st(1) = (int)(x), st(2) = x
		fsub st0, st1 	;otrzymujemy część ułamkową x: st(0) = x - (int)(x) = frac(x), st(1) = int(x) st(2) = x
		f2xm1 		;st(0) = 2^frac(x) - 1 ,st(1) = int(x), st(2) = x
		fld1 		;załaduj st(0) = 1, st(1) = 2^frac(x) -1, st(2) = int(x), st(3) = x
		faddp 		;dodaj wcześniej załadowane 1: st(0) = 2^frac(x), st(1) = int(x), st(2) = x
		fxch st1 	;zamień st1 z st0, st(0) = int(x), st(1) = 2^frac(x), st(2) = x
		fld1	        ;załaduj 1, st(0) = 1, st(1) = int(x), st(2) = 2^frac(x), st(3) = x
		fscale 		; st(0) = 2^(int)(x),st(1) = int(x), st(2) = 2^frac(x), st(3) = x
		fstp st1	;zapisz do pamieci i zdejmij ze stosu, st(0) = 2^int(x), st(1) = 2^frac(x), st(2) = x
		fmulp 		;pomnóż: st(0) = 2^x, st(1) = x

		ret

ln:

		fld st0 	;załaduj st0

		; skorzystamy z log_a(b) = log_c(b) / log_c(a)
		; dla c = 2
		; ln(x) = log2_(x) / log_2(e)
		; log_2(e) to stala ladowana fldl2e
		; log_2(x) obliczymy jako 1 * log(2)_x

		fld1		 ;st(0) = 1
		fld qword[x] 	 ;st(0) = x, st(1) = 1
		fyl2x  		 ;st(0) = st(1) * log_2(st(0))

		fldl2e 		 ;załaduj stałą, teraz st(0) = log_2(e)
		fxch st1 	 ;zamień st(0) z st(1), aby móc podzielić

		; teraz st(0) ma log_2(x), st(1) ma log_2(e), wiec mozemy dzielic

		fdiv st0, st1 	;dzielenie, wynik w st0
		fstp st1	;zaspisz do pamieci i zdejmij ze stosu
		fstp st1	

		fstp qword[result] 	

		ret		;powrót

exp:

		;skorzystamy ze wzoru a^log_a(b) = b oraz
		; log_a(b^c) = clog_a(b)
		; zatem e^x to
		; 2^log_2(e^x) mamy zatem
		; 2^(xlog_2(e))

		fldl2e 		;załaduj st(0) = log_2(e)
		fld qword[x]   	;załaduj st(0) = x, st(1) = log2_(e)
		fmul st0, st1 	;pomnóż: st(0) =  x*log2_(e)
		call pow2	;wywołanie funkcji potęgującej

		fstp st1	;zapisz do pamięci i zdejmij ze stosu
		fstp st1
		fstp qword[result]

		ret		;powrót

sinh:

		call exp		;wywołaj funkcję obliczającą e^x	
		fld qword[result]
		fld qword[x]		;kopiujemy x zeby zrobic -x
		fld qword[x]
		fchs			;zmiana znaku: x = -x
		fstp qword[x] 		;teraz pod x jest wartosc -x
		call exp 		;w result jest e^-x
		fstp qword[x] 		;pod x dajemy starego x
		fld qword[result]
		fsubp st1, st0 		;odejmujemy st(0) = e^x - e^-x
		fld1
		fld1
		fscale 			;st(0) = 2, st(1) = 1, st(3) = e^x - e^-x
		fstp st1;
		fdivp st1, st0		;finalnie dzielimy: st(0) = sinh

		fstp qword[result]

		ret

sinh_1:
		fld qword[x]		;załaduj x
		fld st0			;załaduj x
		fmulp st1 		;pomnóż x^2		
		fld1			;załaduj 1
		faddp st1 		;x^2 + 1
		fsqrt			;pierwiastkuj: sqrt(x^2 + 1)
		fstp st1 		;zapisz w pamieci
		fld qword[x]		;załaduj x
		fadd st1 		;dodaj: x + sqrt(x^2 + 1)
		fld qword[x]; 		;załaduj x
		fxch st1		;zamień st0 i st1
		fstp qword[x]		;zapisz w pamieci
		call ln			;wywołaj funkcję logarytmującą
					
		fstp qword[x] 		;w result jest sihn^-1 wiec nie musimy nic zapisywac

					
		ret


printLN:
		
		push ebp
		mov ebp, esp
		
		;wrzuć na stos od najmłodszego bajtu
		push dword[result + 4]
		push dword[result]
		push dword[x + 4]
		push dword[x]
		push printLn
		call printf

		leave
		ret

printEXP:
		push ebp
		mov ebp, esp

		push dword[result + 4]
		push dword[result]
		push dword[x + 4]
		push dword[x]
		push printExp
		call printf

		leave
		ret


printSINH:

		push ebp
		mov ebp, esp

		push dword[result + 4]
		push dword[result]
		push dword[x + 4]
		push dword[x]
		push printSinh
		call printf

		leave
		ret

printSINH_1:

		push ebp
		mov ebp, esp

		push dword[result + 4]
		push dword[result]
		push dword[x + 4]
		push dword[x]
		push printSinh_1
		call printf

		leave
		ret
main:
		finit		;instrukcja inicjalizacji FPU
		push x
		push scanFloat	;pobierz liczbę
		call scanf
		add esp, 8
		
		;wywołania kolejnch funkcji: obliczającej i drukującej
		call ln
		call printLN

		call exp
		call printEXP

		call sinh
		call printSINH

		call sinh_1
		call printSINH_1

		ret

section .data

		scanFloat: db'%lf',0

		printLn: db'ln(%lf) = %lf',10,0
		printExp: db'e^%lf = %lf',10,0
		printSinh: db'sinh(%lf) = %lf',10,0
		printSinh_1: db'sinh^-1(%lf) = %lf',10,0

section .bss
		;dane niezainicjalizowane
		x resq 1	;qword - 8 bajtów
		result resq 1
