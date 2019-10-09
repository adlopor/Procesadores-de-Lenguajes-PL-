/**************************** ejemplo1.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripcion:

    	El analizador léxico convierte la letras mayúsculas en minúsculas,
	elimina blancos al final de la línea y sustituye una serie de blancos
	por uno solo.
   */
%}

/***** Zona de las reglas *****/
%%
[A-Z]		putchar(yytext[0]+'a'-'A');
[ ]+$           ;
[ ]+		putchar(' ');
%%


/***** Zona de funciones auxiliares *****/

/*** no hay funciones auxiliares ***/
