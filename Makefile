MAIN := main
LIB_A := crr
LIB_B := option
APP := crr
INC := -I include

bin/$(APP): bin/$(MAIN).o bin/$(LIB_A).o bin/$(LIB_B).o
	gcc -o bin/$(APP) bin/$(MAIN).o bin/$(LIB_A).o bin/$(LIB_B).o -lm

bin/$(MAIN).o: src/$(MAIN).c include/$(LIB_A).h
	gcc -o bin/$(MAIN).o $(INC) -c src/$(MAIN).c

bin/$(LIB_A).o: src/$(LIB_A).c include/$(LIB_A).h
	gcc -o bin/$(LIB_A).o $(INC) -c src/$(LIB_A).c

bin/$(LIB_B).o: src/$(LIB_B).c include/$(LIB_B).h
	gcc -o bin/$(LIB_B).o $(INC) -c src/$(LIB_B).c

clean:
	rm bin/*.o

wipe:
	rm bin/*