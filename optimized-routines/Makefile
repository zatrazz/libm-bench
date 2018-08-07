CFLAGS  = \
  -O2 -g \
  -I. \
  -DWANT_ERRNO=0 \
  -DWANT_ROUNDING=0 \
  -ffp-contract=fast \
  -fno-math-errno

# Mimic Android flags
CFLAGS += \
  -D_DEFAULT_SOURCE \
  -DFLT_EVAL_METHOD=0 \
  -Wall \
  -Werror \
  -Wno-missing-braces \
  -Wno-parentheses \
  -Wno-sign-compare \
  -Wno-unknown-pragmas \
  -Wno-unused-const-variable \
  -Wno-unused-variable

UNAME := $(shell uname -m)
ifeq ($(UNAME), x86_64)
endif
ifeq ($(UNAME), aarch64)
CFLAGS += \
  -DHAVE_FAST_FMA=1
endif

all:				liboptimized-routines.so

liboptimized-routines.so:	expf.o exp2f.o powf.o logf.o log2f.o \
				sinf.o cosf.o sincosf.o exp.o exp2.o \
				log.o log2.o pow.o \
				exp2f_data.o math_errf.o powf_log2_data.o \
				logf_data.o log2f_data.o sincosf_data.o \
				exp_data.o math_err.o log_data.o log2_data.o \
				pow_log_data.o
				$(CC) $(CFLAGS) -shared -o $@ $^

expf.o:				expf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp.o:				exp.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp2f.o:			exp2f.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp2.o:				exp2.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
powf.o:				powf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
pow.o:				pow.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
log.o:				log.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
logf.o:				logf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
log2.o:				log2.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
log2f.o:			log2f.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
sinf.o:				sinf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
cosf.o:				cosf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
sincosf.o:			sincosf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
sincosf_data.o:			sincosf_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp_data.o:			exp_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp2f_data.o:			exp2f_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
math_errf.o:			math_errf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
pow_log2_data.o:		pow_log2_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
powf_log2_data.o:		powf_log2_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
log_data.o:			log_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
logf_data.o:			logf_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
log2_data.o:			log2_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
log2f_data.o:			log2f_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^

clean:
				rm -f *.o *.so
