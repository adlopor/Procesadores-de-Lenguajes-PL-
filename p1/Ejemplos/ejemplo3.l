/**************************** ejemplo3.l ***********************************/

/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:
	El analizador léxico distingue entre verbos, adjetivos, 
	adverbios, artículos,... 
 */


%}

%%

[\t ]+		/* ignora los espacios en blanco */ ;

es |
soy |
eres |
eramos |
era |
ser |
siendo |
sido |
hacer |
hace |
hizo |
puedo |
puede |
podia |
tiene |
tener |
tengo |
tenia |
ir		{ printf("%s: es un verbo\n", yytext); }

muy |
mucho |
bastante |
lentamente |
velozmente 	{ printf("%s: es un adverbio\n", yytext); }

a |
para |
desde |
de |
debajo |
encima |
detras |
entre 		{ printf("%s: es una preposicion\n", yytext); }

si |
entonces |
y |
pero |
o		{ printf("%s: es una conjuncion\n", yytext); }

alto |
bella |
inteligente |
amable |
feliz |
alegre		{ printf("%s: es un adjetivo\n", yytext); }

yo |
tu |
el |
ella |
nosotros |
vosotros |
ellos		{ printf("%s: es un pronombre\n", yytext); }


[a-zA-Z]+ {
	 printf("%s:  No reconocido: puede ser un nombre \n", yytext);
	}

.|\n		{ ECHO; putchar('\n'); /* resto de cadenas */ }

%%

/***** Zona de funciones auxiliares *****/

void main()
{
	yylex();
}
