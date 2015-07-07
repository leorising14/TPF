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
#include "createfiles.h"

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

miestado* quitarestado(int num_of_block_to_del,miestado *lista){
    
    if(lista == NULL)
    {
        printf("Actualmente no hay estados!");
        return(NULL);
    }
    
    miestado *recorrer=NULL; 
    miestado *anterior=NULL;
    int i=num_of_block_to_del;
    
    if(num_of_block_to_del==0){
      recorrer=lista;
      lista=lista->next;
      free(recorrer->name);
      free(recorrer);
      recorrer=lista;
      if(lista != NULL){                                            //en el caso de que solo este presente el primer estado
        for(i=0;(recorrer->next)!=NULL;recorrer=recorrer->next){
            recorrer->cont=i;
            i++;
        }
      recorrer->cont=i;
      }
      return(lista);
    }else{
      recorrer=lista;
      anterior=lista;
      for (;(recorrer->cont)<(num_of_block_to_del-1);recorrer=recorrer->next){}
      anterior=recorrer;
      recorrer=recorrer->next;  
      anterior->next=recorrer->next;
      for(i=num_of_block_to_del-1;(anterior->next)!=NULL; anterior=anterior->next){
        anterior->cont=i;
        i++;
      }
    anterior->cont=i;               //seteo el contador en el ultimo que no es considerado
    free(recorrer->name);
    free(recorrer);
    return(lista);
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

mifuncion* quitarfuncion(int num_of_block_to_del,mifuncion *lista){
    
    if(lista == NULL)
    {
        printf("Actualmente no hay estados!");
        return(NULL);
    }
    
    mifuncion *recorrer=NULL; 
    mifuncion *anterior=NULL;
    int i=num_of_block_to_del;
    
    if(num_of_block_to_del==0){
      recorrer=lista;
      lista=lista->next;
      free(recorrer->name);
      free(recorrer->event);
      free(recorrer);
      recorrer=lista;
      if(lista != NULL){                                            //en el caso de que solo este presente el primer estado
      for(i=0;(recorrer->next)!=NULL;recorrer=recorrer->next){
         recorrer->cont=i;
         i++;
      }
      recorrer->cont=i;
      }
      return(lista);
    }else{
      recorrer=lista;
      anterior=lista;
      for (;(recorrer->cont)<(num_of_block_to_del-1);recorrer=recorrer->next){}
      anterior=recorrer;
      recorrer=recorrer->next;  
      anterior->next=recorrer->next;
      for(i=num_of_block_to_del-1;(anterior->next)!=NULL; anterior=anterior->next){
        anterior->cont=i;
        i++;
      }
    anterior->cont=i;               //seteo el contador en el ultimo que no es considerado
    free(recorrer->name);
    free(recorrer->event);
    free(recorrer);
    return(lista);
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
