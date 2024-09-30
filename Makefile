# Compilar el código fuente y generar un ejecutable: make
# Limpiar ficheros .o y ejecutable: make clean
# Ejemplo de ejecución: ./main resource/input.txt resource/salida.txt

# Variables
CC = g++
CFLAGS = -Wall -g -std=c++17 -Wno-class-conversion

# Objetivo por defecto (se ejecuta al correr solo "make")
make: src/main.cc
	$(CC) $(CFLAGS) -o main src/main.cc

# Objetivo alternativo (se ejecuta al correr "make test")
test: src/test_main.cc
	$(CC) $(CFLAGS) -o test_main src/test_main.cc

# Limpiar los archivos binarios
clean:
	rm -f *.o main test_main