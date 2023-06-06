lynx -dump $1 > strona1.txt 

while true;
do
	sleep $2;
	lynx -dump $1 > strona2.txt
	diff strona1.txt strona2.txt > wynik.txt

	if [ "" != "`cat wynik.txt`" ]
	then
		echo 'Cos sie zmienilo'
		cat < wynik.txt
		else
		echo 'Nic sie nie zmienilo'
		cat < strona2.txt
	fi
	
done
