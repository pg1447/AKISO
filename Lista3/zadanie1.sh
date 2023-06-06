#!/bin/bash

info() {
	echo "Ten skrypt liczy AnB i A/B, dwoch plikow. Uruchamianie:"
	echo -e "$0 [plik 1] [plik 2] \n"
}

if [ $# -lt 2 ]
then
	info
	exit 1
fi


plik1=$1
plik2=$2
suma="suma"
roznica="roznica"

sort -u $plik1 > ./~temp_$plik1
sort -u $plik2 > ./~temp_$plik2

cat ~temp_$plik1 ~temp_$plik2 | sort -u > $suma
cat ~temp_$plik1 ~temp_$plik2 | sort | uniq -d | cat > ~temp
cat ~temp_$plik1 ~temp | sort | uniq -u | cat > $roznica

rm ~temp ~temp_$plik1 ~temp_$plik2

exit 0
