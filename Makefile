CFLAGS += -O2 -Wall -g -DDURATION=10 -D_ISOMAC -I. -fgnu89-inline
CFLAGS += -fmerge-all-constants -fno-math-errno
LDFLAGS = -lm

BENCHS = \
  bench-expf \
  bench-powf \
  bench-logf \
  bench-exp2f \
  bench-log2f \
  bench-sinf \
  bench-cosf

TOPTARGETS := all clean
SUBDIRS := $(wildcard */.)

all:		$(BENCHS) $(SUBDIRS)

$(TOPTARGETS):	$(SUBDIRS)
$(SUBDIRS):
		$(MAKE) -C $@ $(MAKECMDGOALS)

bench-expf:	bench-expf.o json-lib.o
		$(CC) -o $@ $^ $(LDFLAGS)

bench-powf:	bench-powf.o json-lib.o
		$(CC) -o $@ $^ $(LDFLAGS)

bench-logf:	bench-logf.o json-lib.o
		$(CC) -o $@ $^ $(LDFLAGS)

bench-exp2f:	bench-exp2f.o json-lib.o
		$(CC) -o $@ $^ $(LDFLAGS)

bench-log2f:	bench-log2f.o json-lib.o
		$(CC) -o $@ $^ $(LDFLAGS)

bench-sinf:	bench-sinf.o json-lib.o
		$(CC) -o $@ $^ $(LDFLAGS)

bench-cosf:     bench-cosf.o json-lib.o
		$(CC) -o $@ $^ $(LDFLAGS)

.ONESHELL:
bench:		$(BENCHS)
		BENCHMARKS="$^"
		LIBRARIES=`for i in $$(ls -d */); do echo $${i%%/}; done`
		for bench in $$BENCHMARKS; do
		  for lib in $$LIBRARIES; do
		    echo "Running $$bench with $$lib"
		    LD_PRELOAD=$$lib/lib$$lib.so taskset -c 4 ./$$bench > $$bench-$$lib.out
		  done
		done

clean:
		rm -f *.o $(BENCHS) *.out

.PHONY: $(TOPTARGETS) $(SUBDIRS)
