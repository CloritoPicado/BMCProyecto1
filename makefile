# change application name here (executable output name)
TARGET=main
 
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN = -w
 
PTHREAD=-pthread
 
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe -W -Wall
 
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

LIBS=-L/usr/lib/x86_64-linux-gnu -ldl -lm -lpthread
 
# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
 
OBJS=    MAIN.o
 
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

    
MAIN.o: src/MAIN.c
	$(CC)  -c $(CCFLAGS) src/MAIN.c $(GTKLIB) -o MAIN.o $(LIBS)

    
clean:
	rm -f *.o $(TARGET) 
