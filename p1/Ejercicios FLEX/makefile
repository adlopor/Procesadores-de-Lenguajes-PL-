# Si se desea generar ejemplo0.exe entonces teclear 
#             make
#
# Si se desea generar otro "ejemplo" entonces teclear 
#            make FUENTE=ejemplo

FUENTE = ejemplo0

CFLAGS = -g  # para depurar

##
$(FUENTE).exe: lex.yy.c
	gcc $(CFLAGS) lex.yy.c -lfl -o $(FUENTE).exe;\
        rm -f lex.yy.c

lex.yy.c: $(FUENTE).l
	flex $(FUENTE).l

clean:
	rm -f lex.yy.c *.exe
