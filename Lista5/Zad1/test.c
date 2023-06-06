#include "myinout.c"
int main(){
	
	
	
	int dec,hex,bin;
	char str[20];
	myprintf("Prosze wpisac dec, hex, bin oraz string\n");
	myscanf("%d%x%b%s", &dec,&hex,&bin,&str);
	myprintf("Wpisales liczbe dziesietna \n%d (10)\n%b (2)\n%x (16)\n", dec, dec, dec);
	myprintf("Wpisales liczbe szesnastkowa \n%d (10)\n%b (2)\n%x (16)\n", hex, hex, hex);
	myprintf("Wpisales liczbe binarna \n%d (10)\n%b (2)\n%x (16)\n", bin, bin, bin);
	myprintf("Wpisałeś tekst \n%s \n", str);
	return 0;
}