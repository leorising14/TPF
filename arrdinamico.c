/* 
 * File:   arrdinamico.c
 * Author: Gabriel
 *
 * Created on 24 de junio de 2015, 17:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "arrdinamico.h"

/*
 * 
 */

void agregarestado(miestado** p2state) //lista es el  puntero al primer elemento, NO SE PUEDE TOCAR
{
    if((*p2state) == NULL)
    {
        (*p2state) = calloc(1, sizeof(miestado));
        ((*p2state) -> next) = NULL;
    }else
    {
        agregarestado(&((*p2state)->next));
    }
}

void quitarestado(miestado** p2state)
{
    if((*p2state) == NULL)
    {
        printf("Actualmente no hay estados!");
        return;
    }
    
    if(((*p2state)->next) == NULL)
    {
        free(*p2state);
        *p2state = NULL;
        return;
    }
    
    if((((*p2state)->next)->next) == NULL)
    {
        free((*p2state)->next);
        ((*p2state)->next) = NULL;
    }else
    {
        quitarestado(&((*p2state)->next));
    }
}

miestado* leerestado(int numofstate, miestado *p2state)
{
    if(p2state == NULL)
    {
        printf("El estado no existe!");
        return NULL;
    }
    if(numofstate == 0)
    {
        return p2state;
    }else
    {
        return leerestado(numofstate-1,(p2state->next));
    }
}

miestado* ultimoestado(miestado *p2state)
{
    if(p2state == NULL)
    {
        return NULL;
        printf("El estado no existe!");
    }
    if((p2state->next) == NULL)
    {
        return p2state;
    }else
    {
        return ultimoestado(p2state -> next);
    }
}

void delblock(int num_of_block_to_del,miestado *lista){
    int i=num_of_block_to_del;
    miestado *recorrer=lista;
    miestado *anterior=lista;
    if(num_of_block_to_del==0){
        recorrer=(recorrer->next);
        free(recorrer);
    }else{
    for (;(recorrer->cont)<(num_of_block_to_del-1);recorrer=recorrer->next){}
    anterior=recorrer;
    recorrer=recorrer->next;  
    anterior->next=recorrer->next;
    for(i=num_of_block_to_del-1;(anterior->next)!=NULL; anterior=anterior->next){
        anterior->cont=i;
        i++;
    }
    anterior->cont=i;               //seteo el contador en el ultimo que no es considerado
    free(recorrer);
    }
}


//Recibir un string que seria lo que pasa por terminal externa y el puntero la primer elemento del arreglo dinamico de funciones
//
//Devuelve puntero a mifuncion que coincide con el nombre o NULL si no hay concidencia

/*
mifuncion* getfun(char argv[],mifuncion* header){
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

void agregarfuncion(mifuncion** p2state) //lista es el  puntero al primer elemento, NO SE PUEDE TOCAR
{
    if((*p2state) == NULL)
    {
        (*p2state) = calloc(1, sizeof(mifuncion));
        ((*p2state) -> next) = NULL;
    }else
    {
        agregarfuncion(&((*p2state)->next));
    }
}

mifuncion* leerfuncion(int numofstate, mifuncion *p2state)
{
    if(p2state == NULL)
    {
        printf("El estado no existe!");
        return NULL;
    }
    if(numofstate == 0)
    {
        return p2state;
    }else
    {
        return leerfuncion(numofstate-1,(p2state->next));
    }
}

void quitarfuncion(int num_of_block_to_del,mifuncion *lista){
    int i=num_of_block_to_del;
    mifuncion *recorrer=lista;
    mifuncion *anterior=lista;
    if(num_of_block_to_del==0){
        recorrer=(recorrer->next);
        free(recorrer);
    }else{
    for (;(recorrer->cont)<(num_of_block_to_del-1);recorrer=recorrer->next){}
    anterior=recorrer;
    recorrer=recorrer->next;  
    anterior->next=recorrer->next;
    for(i=num_of_block_to_del-1;(anterior->next)!=NULL; anterior=anterior->next){
        anterior->cont=i;
        i++;
    }
    anterior->cont=i;               //seteo el contador en el ultimo que no es considerado
    free(recorrer);
    }
}

int createfsm(miestado* p2e, mifuncion* p2f)
{
        FILE *p2file;   // pointers to file

   if ((p2file= fopen("mqestado.c", "wb"))
	   == NULL)
   {
	  fprintf(stderr, "Cannot open input file.\n");
	  return -1;
   }
        int i;
        int running=1;
        
        miestado *estado_actual=p2e;
        mifuncion* recorrer_fun=p2f;
        
        if(estado_actual==NULL || recorrer_fun==NULL)
        {
            fprintf(stderr, "No es posible hacer la maquina de estados. No se encuentran estados o transiciones existentes.\n");
            return -1;
        }
        
        while(running)
        {            
            fprintf(p2file,"STATE estado_%d[]=\n{\n",estado_actual->cont);
            
            for (i=0;recorrer_fun!=NULL;recorrer_fun=recorrer_fun->next)
            {
                if(recorrer_fun->origin==estado_actual->cont)
                
            }
	    fprintf(p2file,"\t{FIN_TABLA,estado_0,reset_FSM}\n}\n\n");
            estado_actual=estado_actual->next;
            recorrer_fun=p2f;
            
            if(estado_actual==NULL)
                running=0;
        }
        fclose(p2file);
	return 0;
}