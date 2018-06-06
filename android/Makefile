CFLAGS  = \
  -O2 \
  -I. \
  -D'__FBSDID(a)=' \
  -D'__RENAME_LDBL(a,b,c)=' \
  -D'__INTRODUCED_IN(a)=' \
  -D'__INTRODUCED_IN_X86(a)=' \
  -D'__INTRODUCED_IN_ARM(a)=' \
  -D'__INTRODUCED_IN_MIPS(a)=' \
  -D'__VERSIONER_NO_GUARD='

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

all:			libandroid.so

libandroid.so:		e_expf.o s_exp2f.o e_powf.o
			$(CC) $(CFLAGS) -shared -o $@ $^

e_expf.o:		e_expf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_exp2f.o:		s_exp2f.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_powf.o:		e_powf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^

clean:
			rm -f *.o *.so
