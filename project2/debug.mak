all: project

project: llist.o user_interface.o
	g++ -o project_debug llist.o user_interface.o

llist.o: llist.cpp record.h llist.h
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c llist.cpp

user_interface.o: user_interface.cpp record.h llist.h
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c user_interface.cpp


clean:
	rm *.o
	rm project_debug

