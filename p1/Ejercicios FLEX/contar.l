/**************************** contar.l ***********************************/
/***** Zona de las declaraciones o definiciones *****/
%{
/* 
	
	flex nombre.l
	gcc -g lex.yy.c -lfl -o nombre.exe 
	
	* Contar cuántos accesos ha realizado un usuario.
	Ejemplo:
	./contar registro.txt i32lusaf@uco.es
	
	* Contar cuántos trabajos accesos ha realizado un usuario en un día concreto.
	Ejemplo:
	./contar registro.txt i32lusaf@uco.es 15-3-2018
	
*/


char usuario[50];
char fecha[50];
int acceso=0;
%}

/* Definiciones regulares */




/***** Zona de las reglas *****/
%%


.+	{//Recorre todo el fichero linea a linea con yytext

		//No se ha introducido la fecha
		if( strlen(fecha)==0 )
		{
			//Si esta en la línea el usuario se suma 1 al contador
			if( strstr(yytext,usuario) != NULL )
				acceso++;
		}
		//Si se ha introducido la fecha
		else
		{
			//Si esta en la línea el usuario y la fecha se suma 1 al contador
			if( (strstr(yytext,usuario) != NULL) && (strstr(yytext,fecha) != NULL) )
				acceso++;
		}
	}

%%

/***** Zona de funciones auxiliares *****/
extern FILE *yyin, *yyout;
void main(int argc, char *argv[])
{ 
	
	switch(argc)
	{
		case 3:
			yyin=fopen(argv[1],"r");
			strcpy(usuario,argv[2]);
			strcpy(fecha,"");
			break;
		case 4:
			yyin=fopen(argv[1],"r");
			strcpy(usuario,argv[2]);
			strcpy(fecha,argv[3]);
			break;
		
		default:
			printf("Debe de haber introducido mal los argumentos. \nPista:\n%s registro.txt p42loora@uco.es\n -------------------\nOtra opción:\n%s registro.txt p42loora@uco.es 03-04-2017\n",argv[0],argv[0]);
			printf("\nError en el swtich. Saliendo del programa...\n");
    			exit(-1);
    			
	}
	

	yylex();
 	fclose(yyin);
 	printf("Se ha contabilizado que el número de apariciones es: %d\n",acceso);
}
