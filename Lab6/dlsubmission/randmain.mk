OPTIMIZE = -O2
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -march=native -mtune=native -mrdrnd


randmain: randmain.o randcpuid.o
	gcc $(CFLAGS) -ldl -Wl,-rpath=$(PWD) -o randmain randmain.o randcpuid.o

randcpuid.o: randcpuid.c randcpuid.h
	gcc $(CFLAGS) -c randcpuid.c -o randcpuid.o

randlibhw.o : randlibhw.c randlib.h
	gcc $(CFLAGS) -fPIC -c randlibhw.c -o randlibhw.o

randlibsw.o : randlibsw.c randlib.h
	gcc $(CFLAGS) -fPIC -c randlibsw.c -o randlibsw.o

randlibsw.so:randlibsw.o
	gcc $(CFLAGS) -shared -o randlibsw.so randlibsw.o

randlibhw.so:randlibhw.o	
	gcc $(CFLAGS) -shared -o randlibhw.so randlibhw.o

randmain.o: randmain.c randcpuid.h
	gcc $(CFLAGS) -c randmain.c -o randmain.o

.PHONY: clean  

clean:
	rm -f *.o *.so randmain

