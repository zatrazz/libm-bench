CFLAGS  = \
  -O2 -g \
  -I. \
  -DWANT_ERRNO=0 \
  -DWANT_ROUNDING=0 \
  -ffp-contract=fast

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

all:				liboptimized-routines.so

liboptimized-routines.so:	expf.o exp2f.o powf.o logf.o log2f.o \
				sinf.o cosf.o sincosf.o \
				exp2f_data.o math_errf.o powf_log2_data.o \
				logf_data.o log2f_data.o sincosf_data.o
				$(CC) $(CFLAGS) -shared -o $@ $^

expf.o:				expf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp2f.o:			exp2f.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
powf.o:				powf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
logf.o:				logf.c
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
exp2f_data.o:			exp2f_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
math_errf.o:			math_errf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
powf_log2_data.o:		powf_log2_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
logf_data.o:			logf_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
log2f_data.o:			log2f_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^

clean:
				rm -f *.o *.so
