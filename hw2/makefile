CC = gcc

CFLAGS = -g -Wall -O

TARGET = sort

all: $(TARGET)

$(TARGET): main.o bubbleSort.o quickSort.o insertionSort.o
	$(CC) $(CFLAGS) -Xlinker -Map=$(TARGET).map -o $(TARGET) main.o bubbleSort.o quickSort.o insertionSort.o
	-gcc -Xlinker -Map=bubbleSort.map bubbleSort.c
	-gcc -Xlinker -Map=insertionSort.map insertionSort.c
	-gcc -Xlinker -Map=quickSort.map quickSort.c
	-gcc -Xlinker -Map=main.map main.c
main.o: main.c bubbleSort.h quickSort.h insertionSort.h
	$(CC) $(CFLAGS) -c main.c
bubbleSort.o: bubbleSort.c bubbleSort.h
	$(CC) $(CFLAGS) -c bubbleSort.c
quickSort.o: quickSort.c quickSort.h
	$(CC) $(CFLAGS) -c quickSort.c
insertionSort.o: insertionSort.c insertionSort.h
	$(CC) $(CFLAGS) -c insertionSort.c
clean:
	$(RM) $(TARGET) *.o *~ *.map
