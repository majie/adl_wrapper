DEFINES = 
INCLUDES = -I..
LIBS = -latiadlxx
CFLAGS = -ggdb

main: ../adl_wrapper.h main.o adl_wrapper.o
	gcc $(CFLAGS) $(LIBS) -o main main.o adl_wrapper.o 

main.o: ../adl_wrapper.h main.c
	gcc -c $(CFLAGS) $(DEFINES) $(INCLUDES) -o main.o main.c

adl_wrapper.o: ../adl_wrapper.h ../adl_wrapper.c
	gcc -c $(CFLAGS) $(DEFINES) $(INCLUDES) -o adl_wrapper.o ../adl_wrapper.c

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf main

