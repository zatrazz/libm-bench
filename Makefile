CFLAGS += -O2 -Wall -g -DDURATION=10 -D_ISOMAC -I. -fgnu89-inline
CFLAGS += -fmerge-all-constants -fno-math-errno
LDFLAGS = -lm

BENCHS = \
  bench-expf \
  bench-powf \
  bench-logf \
  bench-exp2f \
  bench-log2f



all:		$(BENCHS)

bench-expf:	bench-expf.o json-lib.o
		$(CC) -o $@ bench-expf.o json-lib.o $(LDFLAGS)

bench-powf:	bench-powf.o json-lib.o
		$(CC) -o $@ bench-powf.o json-lib.o $(LDFLAGS)

bench-logf:	bench-logf.o json-lib.o
		$(CC) -o $@ bench-logf.o json-lib.o $(LDFLAGS)

bench-exp2f:	bench-exp2f.o json-lib.o
		$(CC) -o $@ bench-exp2f.o json-lib.o $(LDFLAGS)

bench-log2f:	bench-log2f.o json-lib.o
		$(CC) -o $@ bench-log2f.o json-lib.o $(LDFLAGS)

clean:
		rm -f *.o $(BENCHS)
