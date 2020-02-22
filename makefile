CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LIBS = -lm
SOURCES = AFHU_shell.c executor.c
OBJECTS = $(subst .c,.o,$(SOURCES))
BIN = shell_AFHU


shell_AFHU: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

all : $(BIN)

clean:
	rm -f $(OBJECTS) $(BIN) *~

