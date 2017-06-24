CC = icc

#override CFLAGS += -mavx2 -Wall -mmmx -msse -msse2 -mssse3 -msse4 -D__PYTHON__ -g -ggdb
#-march=core-avx2
override CFLAGS += -Wall -mssse3 -march=core-avx2 -O3 -D__PYTHON__ -g3 -ggdb

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
