CFLAGS += -O2 -Wall -g -D_ISOMAC -I.
CFLAGS += -fmerge-all-constants -fno-math-errno
LDFLAGS = -lm

BENCHS = \
  bench-expf \
  bench-powf \
  bench-logf \
  bench-exp2f \
  bench-log2f \
  bench-sinf \
  bench-cosf \
  bench-sincosf

TOPTARGETS := all clean
SUBDIRS := $(wildcard */.)

COMMON_OBJS = json-lib.o

all:			$(BENCHS) $(SUBDIRS)

$(TOPTARGETS):		$(SUBDIRS)
$(SUBDIRS):
			$(MAKE) -C $@ $(MAKECMDGOALS)

bench-expf:		bench-expf.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

bench-powf:		bench-powf.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

bench-logf:		bench-logf.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

bench-exp2f:		bench-exp2f.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

bench-log2f:		bench-log2f.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

bench-sinf:		bench-sinf.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

bench-cosf:     	bench-cosf.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)

bench-sincosf:		bench-sincosf.o $(COMMON_OBJS)
			$(CC) -o $@ $^ $(LDFLAGS)
bench-sincosf.o:	bench-sincosf.c
			$(CC) $(CFLAGS) -D_GNU_SOURCE $^ -o $@ -c


.ONESHELL:
bench:		$(BENCHS)
		BENCHMARKS="bench-sinf bench-cosf bench-sincosf"
		LIBRARIES=`for i in $$(ls -d */); do echo $${i%%/}; done`
		for bench in $$BENCHMARKS; do
		  for lib in $$LIBRARIES; do
		    echo "Running $$bench with $$lib"
		    LD_PRELOAD=$$lib/lib$$lib.so ./$$bench -i 10 > $$bench-$$lib.out
		  done
		done

clean:
		rm -f *.o $(BENCHS) *.out

.PHONY: $(TOPTARGETS) $(SUBDIRS)
