
		org $1000

BCDNUMBER	equ $80 ; #define BCDNUMBER $80

START		equ *

		lda <TEXT 	;czytaj mlodszy bajt adresu TEXT
		sta $82 	;zapisz akumulator
		lda >TEXT  	;czytaj starszy bajt adresu TEXT
		sta $83		;zapisz
		lda #226 	;załaduj akumulator - liczbę konwertujemy
		sta NUMBER 	;zapisz ja w NUMBER - zmiennej pomocniczej
		jsr BCD 	;wywołalnie podprogramu
		jsr PRINT 	;wywoalnie podprogramu
		brk

NUMBER		dta b(0)


BCD		equ *

					;zeruj wartosci:
		lda #0			;załaduj 0 do A
		sta BCDNUMBER		;zapisz A, teraz BCDNUMBER = 0
		sta BCDNUMBER+1		;zapisz A, teraz BCDNUMBER+1 = 0
		ldx #8 			;załaduj 8 do X - mamy 8 bitow - licznik pętli
		sed 			;przestaw sie na decimal mode
LOOP		asl NUMBER 		;a << 1
					; A *= 2 
		lda BCDNUMBER 		;czytaj BCDNUMBER z pamięci
		adc BCDNUMBER 		;dodaj z carry, wynik w A
		sta BCDNUMBER 		;zapisz A, BCDNUMBER+=A
		rol BCDNUMBER+1 	; <<1 ( cyklicznie) + C  cyklicznie tzn. 1010 << 1 --> 0101, zas bez cyklu to 0100
					;(czyli wtedy 1 znowu jest na ostantim miejscu, a bez cyklu jej nie ma) + Carry
		dex 			;dekrementuj x
		bne LOOP 		;odgałęzienie, gdy wynik =!0 (skok do LOOP)
		cld			;czysc znacznik D
		rts 			;powrót do rozkazu

PRINT		equ *
		ldy #0			;Y=0
		clc 			;wyczysc carry flage
		lda BCDNUMBER+1 	;czytaj jeden bajt BCDNUMBER - '02'
		adc #'0' 		;dodaj wartosc ASCII
		sta ($82),Y  		;zapisz kod ascii w 'text' na odpowiednim miejscu
					;tzn wez addr, przesun sie o Y i tak zapisz
		iny			;zwiększenie o 1 zawartosci rejestru Y
		lda BCDNUMBER 		;czytaj kolejny bajt BCDNUMBER - '26'
					
		and #$F0 		;Zeruje cztery młodsze bity - '6'
					;A >> 4, dzieki temu 4 starsze bity maja wartosc mlodszych		
		lsr @ 			 ; przesunięcie bitu w lewo
		lsr @			 ; przesunięcie bitu w lewo
		lsr @			 ; przesunięcie bitu w lewo
		lsr @			 ; przesunięcie bitu w lewo
		adc #'0'  		;dodaj z carry
		sta ($82),Y 		;zapisz kod ascii w text na odpowiednim miejscu
					;tzn. wez addr, przesun sie o Y i tak zapisz
		iny 			;zwiększenie o 1 zawartosci rejestru Y
		lda BCDNUMBER 		; czytaj kolejny bajt BCDNUMBER - '26'
		and #$F 		;zeruj 4 starsze bity - '2'
		adc #'0'  		;dodaj z carry 
		sta ($82),Y 		;zapisz kod ascii w text na odpowiednim miejscu
					;tzn wez addr, przesun sie o Y i tak zapisz
		lda <TEXT
		ldx >TEXT
		jsr $FF80 		;w emulatorze jest to adres wyswietlania na ekranie
		rts

		org $3000

TEXT		equ *

		dta b(0),b(0),b(0),b(10) ;dta oznacza rezerwacje pamieci, b oznacza bajt, czyli jest to char[4] = {'\0', '\0', '\0', '\n'}


		org $2E0

		dta a(START)

		end of file
