# -O3 optimizes, -g saves debug information, -Wall and -Wextra turns on additional warnings
CFLAGS=-O3 -g -Wall -Wextra

gamma: Main.c compare.c ReadAndWritePPM.c Test.c calculate.S
	gcc $(CFLAGS) -o $@ $^ -lm

.PHONY: clean
clean:
	rm -f gamma
