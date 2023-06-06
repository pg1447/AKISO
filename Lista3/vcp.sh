#!/bin/bash

info(){
  echo "Skrypt sluzy do kopiowania plikow z widocznym postepem. Uruchamianie:"
  echo "$0 [Plik do skopiowania] [Plik skopiowany]"
}

if [ $# -lt 2 ]; then
  info
  exit 1
fi

if [ -d $2 ]; then
  nowy=./$2/$1
else
  nowy=./$2
fi


cp -r $1 $2 & pid=$!
r1=$(du -d 0 $1 | cut -f1)
r2s=0
while [ "`ps | grep "$!"`" ]; do
  r2n=$(du -d 0 $nowy | cut -f1)
  roznica=$(($r2n-$r2s))
  czas=$(($(($r1-$r2n))/$(($roznica+1))))
  printf "\r Trwa kopiowanie...\t"$r2n"\tz\t"$r1"\tpredkosc kopiowania\t"$roznica"\tpozostaly czas\t"$czas"  \t "
  r2s=$r2n
  sleep 1
done
printf "\nKopiowanie Zakonczone\n"

