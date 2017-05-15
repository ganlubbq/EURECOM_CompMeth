CC = gcc

CFLAGS = -Wall -mmmx -msse -msse2 -mssse3 -msse4 -mavx2 -O0 -D__DEBUG__ -g -ggdb -fno-unroll-loops 

# Utility routines
UTIL_OBJS += lab2.o

#

all: fft

OBJ = $(UTIL_OBJS)
$(OBJ) : %.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

fft: $(OBJ)
	$(CC)  $(OBJ) -o lab2

clean:
	rm -f *.o
