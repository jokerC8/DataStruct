TARGET := list

CFLAGS += -g -O0 -Wall -Werror -fPIC

LDFLAGS += -lpthread -lm

CC := clang

SRC := $(wildcard *.c)

OBJ := $(patsubst %.c, %.o, $(SRC))

$(TARGET):$(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY:clean

clean:
	@rm -rf $(TARGET) *.o

