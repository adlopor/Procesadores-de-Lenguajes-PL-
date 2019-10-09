FUENTE = ejemplo44

CFLAGS = -g  # -g: para depurar

##
$(FUENTE).exe: lex.yy.c p44.c
	gcc $(CFLAGS) lex.yy.c p44.c -lfl -o $(FUENTE).exe;\
        rm -f lex.yy.c

lex.yy.c: $(FUENTE).l
	flex $(FUENTE).l

clean:
	rm -f lex.yy.c *.exe
