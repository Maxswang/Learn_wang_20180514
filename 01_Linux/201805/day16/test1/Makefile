objects = main.o kbd.o command.o display.o \
		  insert.o search.o files.o utils.o

edit:$(objects)
	cc -o edit $(objects)

$(objects):defs.h
kdb.o command.o files.o : command.h
display.o insert.o search.o files.o : buffer.h
.PHONY: clean
clean:
	-rm edit main.o kddb.o command.o display.o \
		insert.o search.o files.o utils.o
