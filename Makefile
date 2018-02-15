erg: cckShell.o
	gcc -o erg cckShell.o
cckShell.o: cckShell.c
	gcc -c cckShell.c
clean:
	rm cckShell.o
