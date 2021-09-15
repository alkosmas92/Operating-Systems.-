SOURCE1		= myprime.o include.c
SOURCE4		= signalwaiting2.c include.c
SOURCE3		= prime1_1.c include.c
CFLAGS		= -c
CC		= gcc
OUT1		= myprime
OUT4		= sig2
OUT3		= prime1_1
LIBS		=
INCS		=

all: $(OUT1)  $(OUT4)  $(OUT3)

$(OUT1): $(SOURCE1)  types.h
	gcc -o $(OUT1) $(SOURCE1) -lm

$(OUT4): $(SOURCE4)  types.h
	gcc  $(SOURCE4) -o $(OUT4) -lm

$(OUT3): $(SOURCE3)  types.h
	gcc $(SOURCE3) -o $(OUT3) -lm



clean:
	rm -f $(OUT1) $(SOURCE1).o  $(SOURCE4) $(OUT4)  $(SOURCE3) $(OUT3)  a.out;
	touch $(SOURCE1).o  $(SOURCE4).c  $(SOURCE3).c
