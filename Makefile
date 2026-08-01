CC = gcc 
PKGS=sdl2
CFLAGS= -Wall  -ggdb -std=c11 -pedantic  `pkg-config --cflags sdl2`
LIBS= `pkg-config --libs sdl2`

SRCS = main.c 
OBJS = $(SRCS:.c=.o)
TARGET = gp

geneticAlgo: main.c 
	$(CC) $(CFLAGS) -o gp main.c $(LIBS)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
#
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 
#
clean:
	rm -f $(TARGET) $(OBJS)
