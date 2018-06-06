CFLAGS  = \
 -O2 \
  -I. \
  -DWANT_ERRNO=0

# Mimic Android flags
CFLAGS += \
  -D_BSD_SOURCE \
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

liboptimized-routines.so:	expf.o exp2f.o powf.o logf.o \
				exp2f_data.o math_errf.o powf_log2_data.o \
				logf_data.o
				$(CC) $(CFLAGS) -shared -o $@ $^

expf.o:				expf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp2f.o:			exp2f.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
powf.o:				powf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
logf.o:				logf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
exp2f_data.o:			exp2f_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
math_errf.o:			math_errf.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
powf_log2_data.o:		powf_log2_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^
logf_data.o:			logf_data.c
				$(CC) $(CFLAGS) -fpic -c -o $@ $^

clean:
				rm -f *.o *.so
