CC = gcc
LEX = flex
YACC = bison
CFLAGS = -Wall -g -Wno-unused-function -Wno-implicit-function-declaration
TARGET = mycc
OBJS = parser.tab.o lex.yy.o compiler.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lfl

parser.tab.c parser.tab.h: parser.y
	$(YACC) -d parser.y

lex.yy.c: scanner.l parser.tab.h
	$(LEX) scanner.l

compiler.o: compiler.c compiler.h parser.tab.h
	$(CC) $(CFLAGS) -c compiler.c

main.o: main.c compiler.h parser.tab.h
	$(CC) $(CFLAGS) -c main.c

parser.tab.o: parser.tab.c compiler.h
	$(CC) $(CFLAGS) -c parser.tab.c

lex.yy.o: lex.yy.c compiler.h parser.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	rm -f $(OBJS) lex.yy.c parser.tab.c parser.tab.h $(TARGET)

test: $(TARGET)
	./$(TARGET) -p samples/test1.c
	@echo ""
	./$(TARGET) -s samples/test1.c
	@echo ""
	./$(TARGET) -i samples/test1.c

.PHONY: all clean test
