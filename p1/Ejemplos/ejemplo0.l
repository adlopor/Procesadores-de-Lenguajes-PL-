/**************************** ejemplo0.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{

   /* Descripcion:

	* El analizador lexico reproduce literalmente todo lo que se teclea

   */
%}

/***** Zona de las reglas *****/
%%
.|\n		ECHO; /* ECHO es equivalente a printf("%s",yytext"); */
%%


/***** Zona de funciones auxiliares *****/

/*** no hay funciones auxiliares ***/
