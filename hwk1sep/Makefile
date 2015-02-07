VPATH=./src/
OPATH=./bin/
objects=main.o preop.o lform.o presult.o
source=$(VPATH)main.cpp $(VPATH)preop.cpp $(VPATH)lform.cpp $(VPATH)presult.cpp
CFLAGS = -g -ansi -pedantic -Wall -Werror

all : ls

ls : bin $(objects)
	g++ $(CFLAGS) $(source) -o $(OPATH)ls
bin: 
	mkdir bin

main.o : main.cpp
	g++ $(CFLAGS) -c $(VPATH)main.cpp $(VPATH)ls.h -o $(OPATH)main.o

preop.o : preop.cpp 
	g++ $(CFLAGS) -c $(VPATH)preop.cpp $(VPATH)ls.h -o $(OPATH)preop.o
 
lform.o : lform.cpp
	g++ $(CFLAGS) -c $(VPATH)lform.cpp $(VPATH)ls.h -o $(OPATH)lform.o

presult.o : presult.cpp 
	g++ $(CFLAGS) -c $(VPATH)presult.cpp $(VPATH)ls.h -o $(OPATH)presult.o

clean :
	rm -rf bin
