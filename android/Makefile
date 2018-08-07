CFLAGS  = \
  -O2 \
  -I. \
  -D'__FBSDID(a)=' \
  -D'__RENAME_LDBL(a,b,c)=' \
  -D'__INTRODUCED_IN(a)=' \
  -D'__INTRODUCED_IN_X86(a)=' \
  -D'__INTRODUCED_IN_ARM(a)=' \
  -D'__INTRODUCED_IN_MIPS(a)=' \
  -D'__VERSIONER_NO_GUARD=' \
  -D'__strong_reference(a,b)='

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
ASMOBJS=\
  floor_x86_64.o \
  sqrtf_x86_64.o \
  e_exp-x86_64.o \
  e_log-x86_64.o \
  e_pow-x86_64.o
endif
ifeq ($(UNAME), aarch64)
ASMOBJS=sqrt_aarch64.o
COBJS=e_exp.o e_log.o e_pow.o
endif

all:			libandroid.so

libandroid.so:		e_expf.o s_exp2f.o e_powf.o e_logf.o e_log2f.o \
			s_sinf.o s_cosf.o s_sincosf.o k_rem_pio2.o \
			s_scalbn.o s_scalbnf.o s_exp2.o e_log2.o \
			$(ASMOBJS) $(COBJS)
			$(CC) $(CFLAGS) -shared -o $@ $^

e_expf.o:		e_expf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_exp2f.o:		s_exp2f.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_powf.o:		e_powf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_logf.o:		e_logf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_log2f.o:		e_log2f.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_sinf.o:		s_sinf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_cosf.o:		s_cosf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_sincosf.o:		s_sincosf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
k_rem_pio2.o:		k_rem_pio2.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_scalbn.o:		s_scalbn.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_scalbnf.o:		s_scalbnf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^

e_exp.o:		e_exp.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
s_exp2.o:		s_exp2.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_log.o:		e_log.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_log2.o:		e_log2.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_pow.o:		e_pow.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^

sqrtf_x86_64.o:		sqrtf_x86_64.S
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
floor_x86_64.o:		floor_x86_64.S
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_exp-x86_64.o:		e_exp-x86_64.S
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_log-x86_64.o:		e_log-x86_64.S
			$(CC) $(CFLAGS) -fpic -c -o $@ $^
e_pow-x86_64.o:		e_pow-x86_64.S
			$(CC) $(CFLAGS) -fpic -c -o $@ $^

sqrt_aarch64.o:		sqrt_aarch64.S
			$(CC) $(CFLAGS) -fpic -c -o $@ $^

clean:
			rm -f *.o *.so
