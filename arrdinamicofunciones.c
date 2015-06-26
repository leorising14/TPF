/* 
 * File:   arrdinamico.c
 * Author: Gabriel
 *
 * Created on 24 de junio de 2015, 17:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "arrdinamicofunciones.h"

/*
 * 
 */

//Recibir un string que seria lo que pasa por terminal externa y el puntero la primer elemento del arreglo dinamico de funciones
//
//Devuelve puntero a mifuncion que coincide con el nombre o NULL si no hay concidencia
/*

mifuncion* getfun(char argv[],mifuncion* header)	
{
	FILE* p2file=fopen("testfunciones.txt","r+");//Hay que cambiar el nombre del archivo
	if (p2file== NULL)
	{
		fprintf(stderr, "Cannot open input file.\n");
		return NULL;
   	}
	mifuncion* recorrer=header;
	int i;
	int running=1;
	char str_fun[20];	//al finalizar va a ser el nombre de la funcion que pasas por linea de comando (si esta correctamente escrita)
	char c;
	
	while(running)
	{
		for(i=0;i<=strlen(argv[]);i++)
		{
			if((c=fgetc(p2file))==EOF)
				running=0;
			else if((argv[i])==c)
			{
				*(str_fun+i)=c;
			}					//Motor de búsqueda.
			else break;
		}
		if (!strcmp(argv[],str_fun))
		{
			
			running=0;
		}
	}
	
	fclose(p2file);

	if (!strcmp(argv[1],str_fun))
	{
		printf("%s\n",str_fun);		//Testeo
	}
	else {printf("no hay concidencia\n");	//Testeo
		return NULL;}
	
	

	//Ahora quiero relacionar el nombre de la funcion que coincide con lo que pasas por la terminal externa con el nombre de la función//

	for (i=0;recorrer->next!=NULL;recorrer=recorrer->next)
            {
                if(!strcmp(recorrer->name,str_fun))
                   return recorrer;
            }
}
*/
