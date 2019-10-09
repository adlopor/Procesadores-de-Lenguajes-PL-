/**************************** pink.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
   /* Descripción
 
 	Se muestra el uso de yymore()
      
   */

/*  Variables globals */

%}

/***** Zona de las reglas *****/
%%
hiper 	 yymore();
texto 	 printf("Token = %s",yytext);
mercado  printf("Token = %s",yytext);
.|\n	 ;  /* Se descartan el resto de caracteres */
%%


/***** Zona de funciones auxiliares *****/

 extern FILE *yyin, *yyout;
void  main(int argc, char *argv[])
{
 
 switch(argc)
  {
   case 2:  yyin=fopen(argv[1],"r"); 
            break;
   case 3:  yyin=fopen(argv[1],"r"); 
            yyout=fopen(argv[2],"w"); 
  }
  yylex();

}
