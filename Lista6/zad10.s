.text
.global main
.extern printf
main:
        push {r7, lr}           //na stos: link register - adres powrotu i r7
        mov r3, #12             //załaduj 12 do r3
        mov r4, #45             //załaduj 45 do r4

NWD:
        cmp r3, r4               //porównaj zawartości rejestrów
        subgt r3, r3, r4         //jeśli r3 > r4 ->  r3=r3-r4
        sublt r4, r4, r3        //jeśli r3 < r4 ->  r4=r4-r3 
        bne NWD  //wykonuj pętlę dopóki r0 różne od r1(skok do etykiety nwd)
                 //jeśli równe - koniec programu, nwd znaleziony

end:
	ldr r0, =output  //załaduj adres 'output'
        mov r1, r4      //przenieś wynik z r4 do r1(będzie parametrem)
        bl printf       //call printf

        pop {r7, pc}

.data
output:
 .asciz "NWD: %d\n"


