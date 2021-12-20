sustext: sustext.c
	$(CC) sustext.c -o sustext -Wall -Wextra -pedantic -std=c99
	./sustext
clean: sustext
	rm $^
