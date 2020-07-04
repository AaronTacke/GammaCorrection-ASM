# -O3 optimizes, -g saves debug information, -Wall and -Wextra turns on additional warnings
CFLAGS=-O3 -g -Wall -Wextra

gamma: Main.c assembler/compareBoth.c ReadAndWritePPM.c TestAndBenchmarking.c assembler/calculateGrayscale.S
	gcc $(CFLAGS) -o $@ $^ -lm

.PHONY: clean
clean:
	rm -f gamma
