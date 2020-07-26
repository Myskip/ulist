SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
LIB:=ulist.a

.PHONY:all clean lib

all:lib

$(OBJS):
	$(CC) -o $@ -c $(patsubst %.o,%.c,$@) $(CFLAGS)

lib:$(OBJS)
	$(AR) r $(LIB) $(OBJS)

clean:
	$(RM) r $(OBJS) $(LIB)