all: crop bw colorshift overlay meme

crop: crop.o simp.o
	gcc -ansi -g -pedantic -o crop crop.o simp.o

crop.o: crop.c simp.o
	gcc -ansi -g -pedantic -c crop.c
	
bw: bw.o simp.o
	gcc -ansi -g -pedantic -o bw bw.o simp.o
	
bw.o: bw.c simp.o
	gcc -ansi -g -pedantic -c bw.c
	
colorshift: colorshift.o simp.o
	gcc -ansi -g -pedantic -o colorshift colorshift.o simp.o
	
colorshift.o: colorshift.c simp.o
	gcc -ansi -g -pedantic -c colorshift.c
	
overlay: overlay.o simp.o
	gcc -ansi -g -pedantic -o overlay overlay.o simp.o

overlay.o: overlay.c simp.o
	gcc -ansi -g -pedantic -c overlay.c 	
	
simp.o: simp.c simp.h
	gcc -ansi -g -pedantic -c simp.c	
	
meme: meme.o simp.o
	gcc -ansi -g -pedantic -o meme meme.o simp.o

meme.o: meme.c simp.o
	gcc -ansi -g -pedantic -c meme.c 	
	
test: test.c
	gcc -ansi -o test test.c
	
clean:
	rm -f *.o overlay crop colorshift bw meme test
