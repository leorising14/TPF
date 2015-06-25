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