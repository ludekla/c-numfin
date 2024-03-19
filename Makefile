MAIN := main
LIB := crr
APP := crr
INC := -I include

bin/$(APP): bin/$(MAIN).o bin/$(LIB).o
	gcc -o bin/$(APP) bin/$(MAIN).o bin/$(LIB).o -lm

bin/$(MAIN).o: src/$(MAIN).c include/$(LIB).h
	gcc -o bin/$(MAIN).o $(INC) -c src/$(MAIN).c

bin/$(LIB).o: src/$(LIB).c include/$(LIB).h
	gcc -o bin/$(LIB).o $(INC) -c src/$(LIB).c

clean:
	rm bin/*.o

wipe:
	rm bin/*