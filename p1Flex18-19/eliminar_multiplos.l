/**************************** eliminar_multiplos.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
/* Descripcion:

    * Codifica un programa en flex que reciba:
    
		-Un número entero N.
		-El nombre de un fichero compuesto por números enteros.
		-El nombre de un fichero de salida (opcional).
		
	* Muestre por pantalla o almacene en el fichero de salida (en su caso) los números que no sean múltiplos del número N
	
	*Ejemplo:
	
		./eliminar_multiplos 3 numeros.txt salida.txt
		
		-Entrada.txt
	
	1	2	3	4
	5	6	7	8
	9	10	11	12
	
		-Salida.txt
	1	2		4
	5		7	8
		10	11

*/

int N;
 
%}

/* Definiciones regulares */

digito		[0-9]
numero		{digito}+


/***** Zona de las reglas *****/
%%
{numero}	{

		int value = atoi(yytext);
		
		if( value%N != 0 ){
			
					
			fprintf(yyout,"%d",value);	
		}
		
		
}		
.		{ ECHO; /* Se muestra por pantalla, pero no se indica nada */ }


%%
/***** Zona de funciones auxiliares *****/
extern FILE *yyin, *yyout;
int main(int argc, char *argv[])
{ 
	
	switch(argc)
	{
		case 3:
			N = atoi(argv[1]);
			yyin = fopen(argv[2],"r");
			
			break;
			
		case 4:
			N=atoi(argv[1]);
			yyin=fopen(argv[2],"r");
			yyout=fopen(argv[3],"w");  
			
			break;
				
		default:
			printf("Debe de haber introducido mal los argumentos. \nPista:\n%s N entrada.txt salida.txt \n",argv[0]);
			printf("\nError en el switch. Saliendo del programa...\n");
    			exit(-1);
    			
	}
	
	yylex();
	return 0;
}
