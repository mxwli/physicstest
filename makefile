
cc=gcc

all: bin/run

clean:
	rm bin/run

run:
	./bin/run

bin/run: main.c
	gcc main.c -o bin/run -lraylib -ldl -lm
