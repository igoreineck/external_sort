all: compile_files clear run

compile_files: main.o extract_sort.o comparison.o
	gcc main.o extract_sort.o comparison.o -o app

main.o: main.c
	gcc -c main.c

extract_sort.o: extract_sort.c
	gcc -c extract_sort.c

comparison.o: comparison.c
	gcc -c comparison.c

clear:
	rm -f *.o
	# rm data/*

run:
	./app