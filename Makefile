all: dumshell
	gcc -o dumshell dumshell.c

clean:
	rm -rf dumshell
