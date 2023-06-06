100	getch,	LoadI	chptr
101			Skipcond	400
102			Jump	outp
103			Halt
104	outp,	Output
105			Load 	chptr
106			Add		one
107			Store	chptr
108			Jump	getch
109	one,	Hex		1
10A	chptr,	Hex		10B
10B	string,	Dec		72
10C			Dec		101
10D			Dec		108
10E			Dec		108
10F			Dec		111
110			Dec		032
111			Dec		119
112			Dec		111
113			Dec		114
114			Dec		108
115			Dec		100
116			Dec		033
117			Dec		000