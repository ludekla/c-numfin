CC = gcc
CFLAGS = -Wall -g -std=c99
LDFLAGS = -lm
INC = -I include

BIN = crr
OBJS = bin/main.o bin/option.o bin/crr.o

bin/$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS): bin/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	
clean:
	rm bin/*.o

wipe:
	rm bin/*