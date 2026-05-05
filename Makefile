CC = gcc 
CFLAGS= -Wall -Wextra -ggdb -std=c11 -pedantic 
TARGET= my_program

SRCS = main.c 
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(TARGET) $(OBJS)
