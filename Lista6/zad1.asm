
		org $1000

START		equ *


		lda <TEXT ; czytaj mlodszy bajt adresu TEXT
		sta $80	; zapisz akumulator
		lda >TEXT ; czytaj starszy bajt adresu TEXT
		sta $81
		ldy #1	; wczytaj index z pamięci
		lda #$B2 ; liczba do konwertowania
		jsr CONV2HEX ; wywoalnie podprogramu
		lda <TEXT
		ldx >TEXT
		jsr $FF80	;skocz do podporgramu
		brk


CONV2HEX	pha ; zapisz na stosie akumulator
		jsr HEXDIGIT
		pla ; zdejmij ze stosu akumulator
		; a << 4
		lsr @ ; przesunięcie bitu w lewo TODO
		lsr @
		lsr @
		lsr @
HEXDIGIT	and #$F ; czytaj 4 mlodsze bity
		clc	; wyczysc carry flage
		adc #'0'	; dodaj z carry
		cmp #'9'+1	; comapre with accumulator
		bcc DIGIT ; wykonuje sie jesli flaga carry jest 0
		clc ; wyczysc carry flage
		adc #'A'-'9'-1 ; kod ascii > '9' konwertuj na 'A' - 'F'
DIGIT		sta ($80),Y ;zapisz kod ascii w text na odpowiednim miejscu
		;  tzn wez addr z 80 i 81 przesun sie o Y i tak zapisz
		dey ; --y
		rts	; zwróć z podporgramu


		org $3000 ; ustawia nowy adres asmeblacji

TEXT		equ * ;oblicz adres
		dta b(0),b(0),b(10) ; 2 znaki + \n, rezerwacja pamięci, definiowanie danych strukturalnych
		; ustawiam nowy adres linijek ponizej, tzn pointer do startu jest pod adresem 0x2E0 (czyli w hexie)
		org $2E0 ; 

		dta a(START)	; TODO: co to za dowołanie?

		end of file
