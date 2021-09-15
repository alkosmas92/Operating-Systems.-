

objects = main.o mngstd.c

main : $(objects)
	gcc $(objects) -o main

main.o : interface.h types.h
implementation.o : interface.h types.h

clean :
	rm main $(objects)
