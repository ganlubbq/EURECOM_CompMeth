CC = gcc

override CFLAGS += -Wall -mmmx -msse -msse2 -mssse3 -msse4 -D__PYTHON__ -g -ggdb 

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
