/**************************** sustituir.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
/* Descripcion:

	* Codifica un analizador que:
	
		-Reemplace una palabra por otra en un fichero de entrada.
		
		-Al final, se debe contar el número de palabras sustituidas.
		
	*Ejemplo:
	
		./sustituir.exe fichero.txt antigua nueva
	
*/


char antigua[50],nueva[50];

%}

/* Definiciones regulares */

caracter [a-zA-Z]
palabra {caracter}+
basura [^{palabra}]


/***** Zona de las reglas *****/
%%
{palabra}	{strcmp(yytext,antigua)==0?fprintf(yyout,"%s",nueva):fprintf(yyout,"%s",yytext);}/***** Si es igual al imprimir en el fichero cambia la palabra, en caso contrario la imprime tal y como estaba en el fichero originalmente. *****/

{basura}	{fprintf(yyout,"%s", yytext);}/***** Todo lo que no sea una palabra (espacios, signos de puntuación/exclamación/interrogacción, etc.) Se imprime tal y como venía en el fichero. *****/


%%
/***** Zona de funciones auxiliares *****/
extern FILE *yyin, *yyout;
int main(int argc, char *argv[])
{ 
	
	switch(argc)
	{
		case 4:
			yyin=fopen(argv[1],"r");
			yyout=fopen("ficheroaux.txt","w");
			strcpy(nueva,argv[3]);
			break;
		
		default:
			printf("Debe de haber introducido mal los argumentos. \nPista:\n%s fichero.txt antigua nueva\n",argv[0]);
			printf("\nError en el swtich. Saliendo del programa...\n");
    			exit(-1);
    			
	}
	

	yylex();
	
	remove(argv[1]);
	rename("ficheroaux.txt",argv[1]);
	
return 0;
}
