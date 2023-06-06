100	if,		Load	X
101			Subt	Y
102			Skipcond	800
103			Jump	else
104	then,	Load	X
105			Add		ascii
106			Output
107			Jump	endif
108	else,	Load	Y
109			Add		ascii
10A			Output
10B	endif,	Load	newl
10C			Output
10D			Halt
10E	X,		Dec		9
10F	Y,		Dec		7
110	newl,	Dec		10
111	ascii,	Dec		48