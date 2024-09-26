collatz: collatz.c
	gcc -o collatz collatz.c

clean:

	rm collatz

test: collatz
	bash test.sh