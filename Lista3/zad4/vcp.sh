cp $1 cp$1 &

sleep 1

x="`stat -c'%s' $1`"
y=0
i=0
s=0
ETA=0

while [ "`stat -c'%s' cp$1`" != $x ];
do

	z="`stat -c'%s' cp$1`"
	
	speed=$[ z-y ]

	s=$[ $[ $[ s*i ]+speed ]/$[ i+1 ] ]
	i=$[ i+1 ]

	ETA=$[ $[ x-z ]/$s ]

	printf "\rsrednia predkosc na sekunde: $s ETA: $ETA           "  	
	
	y=$z
	sleep 1	
done
printf "\n"
