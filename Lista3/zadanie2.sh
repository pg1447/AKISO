#!/bin/bash

info() {
	echo "Skrypt sluzacy do sledzenia zmian na stronie. Uruchamianie:"
	echo "$0 [Strona] [czas odswierzania w sekundach]"
}

if [ $# -lt 2 ];then
	info
	exit 1
fi

strona=$1
czas=$2
temp=./~temp
stara=~stara
nowa=~nowa
zmiana=~zmiana
mkdir $temp

links -dump $strona > $temp/$stara

while [ true ];do
	sleep $czas
	links -dump $strona > $temp/$nowa

	diff $temp/$stara $temp/$nowa >$temp/$zmiana

	if [ -n "`cat $temp/$zmiana`" ];then
		zenity --info --text="Nastapila zmiana"
		rm $temp/$stara $temp/$nowa $temp/$zmiana
		rmdir $temp
		exit 0
	fi
done

