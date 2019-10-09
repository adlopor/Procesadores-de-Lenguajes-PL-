/**************************** cifradoCesar.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
/*	
	flex nombre.l
	gcc -g lex.yy.c -lfl -o nombre.exe 
	
	Ejemplo:
	./cifradoCesar 3 entrada.txt salida.txt
	
*/

int N,x;	       // 0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26
char vectorMinusculas[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n',L'ñ','o','p','q','r','s','t','u','v','w','x','y','z'};
char vectorMayusculas[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N',L'Ñ','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

%}

/* Definiciones regulares */

minuscula [a-z]
mayuscula [A-Z]


/***** Zona de las reglas *****/
%%
Ñ	{
		fprintf(yyout,"%c",vectorMayusculas[((14+N)%27)]);		
	}

ñ	{
		fprintf(yyout,"%c",vectorMinusculas[((14+N)%27)]);		
	}
	
{minuscula}	{
		
			char c=yytext[0];
			x=c-97;
			if(x>=14){x++;}
			x=(x+N)%27;
			fprintf(yyout,"%c",vectorMinusculas[x]);
		}
		
{mayuscula}	{
			char c=yytext[0];
			x=c-65;
			if(x>=14){x++;}
			x=(x+N)%27;
			fprintf(yyout,"%c",vectorMayusculas[x]);
		}

.		{ ECHO; /* Se muestra por pantalla, pero no se indica nada */ }

%%
/***** Zona de funciones auxiliares *****/
extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{ 
	
	switch(argc)
	{
		case 3
		case 4:
			yyin=fopen(argv[2],"r");
			yyout=fopen(argv[3],"w");
			N=atoi(argv[1]);
			break;
		
		default:
			printf("Debe de haber introducido mal los argumentos. \nPista:\n%s N entrada.txt salida.txt\n",argv[0]);
			printf("\nError en el swtich. Saliendo del programa...\n");
    			exit(-1);
    			
	}
	

	yylex();
 
}
