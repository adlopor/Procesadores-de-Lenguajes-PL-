/**************************** sumar_parametrizado.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
/* Descripcion:

      * Codifica un programa en flex que copie el archivo de entrada en
uno de salida sumando N a todo número positivo que sea múltiplo
de M, donde N y M son dos números pasados como argumentos
desde la línea de órdenes.
	
	flex nombre.l
	gcc -g lex.yy.c -lfl -o nombre.exe 
	
	Ejemplo:
	./sumar_parametrizado.exe Entrada.txt Salida.txt 5 4
*/

int N,M;
 
%}

/* Definiciones regulares */

digito		[0-9]
numero		{digito}+


/***** Zona de las reglas *****/
%%
{numero}	{

		int value = atoi(yytext);
		
		if( value%M == 0 ){
			
			value+=N;
		
			fprintf(yyout,"%d",value);	
		}
		else{
			
			fprintf(yyout,"%d",value);
			
		}
		
}		
.		{ ECHO; /* Se muestra por pantalla, pero no se indica nada */ }


%%
/***** Zona de funciones auxiliares *****/
extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{ 
	
	switch(argc)
	{
		case 5:
			yyin=fopen(argv[1],"r");
			yyout=fopen(argv[2],"w");  
			N=atoi(argv[3]);
			M=atoi(argv[4]);
			break;
				
		default:
			printf("Debe de haber introducido mal los argumentos. \nPista:\n%s entrada.txt salida.txt N M\n",argv[0]);
			printf("\nError en el swtich. Saliendo del programa...\n");
    			exit(-1);
    			
	}
	
	yylex();
}
