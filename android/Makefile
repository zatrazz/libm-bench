CFLAGS  = -O2 -I.
# Mimic Android flags
CFLAGS += \
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

libandroid.so:		e_expf.o
			$(CC) $(CFLAGS) -shared -o $@ $^

e_expf.o:		e_expf.c
			$(CC) $(CFLAGS) -fpic -c -o $@ $^

clean:
			rm -f *.o *.so
