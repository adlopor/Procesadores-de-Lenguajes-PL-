/**************************** analizador_lexico.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
/* 
	
	flex nombre.l
	gcc -g lex.yy.c -lfl -o nombre.exe 
	
	
	
*/

#include <stdio.h>
#include "analizador_lexico.h"   /* declaracion de los componentes lexicos o tokens */

%}

/* Definiciones regulares */

espacio		[ \t\n]
espacios	{espacio}+
letra		[a-zA-Z]
digito		[0-9]

identificador	{letra}(({letra}|{numero}|_{0,1})*({letra}|{numero}))?
numero		{digito}+(\.{digito}+)?(E[+\-]?{digito}+)?
cadena		"'"([^']|"\\\'")*"'"?

comentario_unilineal \#.*

comentario_multilineal "(*"(.|\n)*"*)"
/***** Zona de las reglas *****/
%%

{comentario_unilineal}				{printf("\n Comentario una línea: %s --> token %d\n",yytext,COMENTARIO_UNILINEAL);}

{comentario_multilineal}				{printf("\n Comentario multilineal: %s --> token %d\n",yytext,COMENTARIO_MULTILINEAL);}	

(?i:inicio)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,INICIO);}

(?i:fin)			{printf("\n Palabra reservada: %s --> token %d\n", yytext,FIN);}
		
(?i:mod)			{printf("\n Palabra reservada: %s --> token %d\n", yytext,MOD);}

(?i:leer)			{printf("\n Palabra reservada: %s --> token %d\n", yytext,LEER);}

(?i:escribir)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,ESCRIBIR);}

(?i:si)			{printf("\n Palabra reservada: %s --> token %d\n", yytext,SI);}

(?i:entonces)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,ENTONCES);}

(?i:si_no)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,SI_NO);}

(?i:fin_si)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,FIN_SI);}

(?i:mientras)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,MIENTRAS);}

(?i:hacer)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,HACER);}

(?i:fin_mientras)	{printf("\n Palabra reservada: %s --> token %d\n", yytext,FIN_MIENTRAS);}

(?i:repetir)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,REPETIR);}

(?i:hasta_que)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,HASTA_QUE);}

(?i:para)			{printf("\n Palabra reservada: %s --> token %d\n", yytext,PARA);}

(?i:desde)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,DESDE);}

(?i:hasta)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,HASTA);}

(?i:paso)			{printf("\n Palabra reservada: %s --> token %d\n", yytext,PASO);}

(?i:fin_para)		{printf("\n Palabra reservada: %s --> token %d\n", yytext,FIN_PARA);}



"="             	{printf("\n Operador de asignación: %s --> token %d\n",yytext,ASIGNACION);}

"+"             	{printf("\n Operador aritmético: %s --> token %d\n",yytext,SUMA);}

"-"             	{printf("\n Operador aritmético: %s --> token %d\n",yytext,RESTA);}

"*"             	{printf("\n Operador aritmético: %s --> token %d\n",yytext,PRODUCTO);}

"/"             	{printf("\n Operador aritmético: %s --> token %d\n",yytext,DIVISION);}

"__mod"             	{printf("\n Operador aritmético: %s --> token %d\n",yytext,MODULO);}

"**"             	{printf("\n Operador aritmético: %s --> token %d\n",yytext,POTENCIA);}

"||"             	{printf("\n Operador alfanumérico: %s --> token %d\n",yytext,CONCATENACION);}

"<"             	{printf("\n Operador relacional de números y cadenas: %s --> token %d\n",yytext,MENOR_QUE);}

"<="             	{printf("\n Operador relacional de números y cadenas: %s --> token %d\n",yytext,MENOR_IGUAL_QUE);}

">"             	{printf("\n Operador relacional de números y cadenas: %s --> token %d\n",yytext,MAYOR_QUE);}

">="             	{printf("\n Operador relacional de números y cadenas: %s --> token %d\n",yytext,MAYOR_IGUAL_QUE);}

"=="             	{printf("\n Operador relacional de números y cadenas: %s --> token %d\n",yytext,IGUAL);}

"<>"             	{printf("\n Operador relacional de números y cadenas: %s --> token %d\n",yytext,DISTINTO);}

"\.o\."            	{printf("\n Operador lógico: %s --> token %d\n",yytext,DISYUNCION_LOGICA);}

"\.y\."            	{printf("\n Operador lógico: %s --> token %d\n",yytext,CONJUNCION_LOGICA);}

"\.no\."           	{printf("\n Operador lógico: %s --> token %d\n",yytext,NEGACION_LOGICA);}

";"             	{printf("\n Otro componente léxico: %s --> token %d\n",yytext,FIN_SENTENCIA);}

"("             	{printf("\n Otro componente léxico: %s --> token %d\n",yytext,PARENTESIS_IZQUIERDO);}

")"             	{printf("\n Otro componente léxico: %s --> token %d\n",yytext,PARENTESIS_DERECHO);}




{identificador}	{printf("identificador = %s\n", yytext);}

{cadena}			{ 
					
                           /* Se ha reconocido una cadena */
					printf("\t Cadena reconocida = ");
					
					for (int i=1;i<(strlen(yytext)-1);i++){
							printf("%c",yytext[i]);
					}
					
					printf("\n");
					
				}
				    




%%


/***** Zona de funciones auxiliares *****/
extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{ 
	
	switch(argc)
	{
		case 2:
			yyin=fopen(argv[1],"r");
			break;
		
		default:
			printf("Debe de haber introducido mal los argumentos. \nPista:\n%s registro.txt p42loora@uco.es\n -------------------\nOtra opción:\n%s registro.txt p42loora@uco.es 03-04-2017\n",argv[0],argv[0]);
			printf("\nError en el swtich. Saliendo del programa...\n");
    			exit(-1);
    			
	}
	

	yylex();

}
