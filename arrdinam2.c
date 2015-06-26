/* 
 * File:   main.c
 * Author: Gabriel
 *
 * Created on 15 de junio de 2015, 18:49
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arrdinam2.h"

int addstate(float newx, float newy, char* newname, estadoheader *lista)
{
    if(strlen(newname)>=20)
    {
        printf("El nombre asignado tiene mas de 20 caracteres.\n");
        return -1;
    }
    
    miestado *newstate= (miestado*) calloc(1,sizeof(miestado));        //asigno el puntero al nuevo bloque, reservando memoria y haciendo un casteo del puntero
    if(newstate==NULL)
    {
        printf("Error: no hay espacio en memoria.\n");
        return -1;
    }
    
    if(lista->p2first == NULL)   //en caso de que el arreglo este vacio
    {                                     
        lista->p2first=newstate;
        newstate->estado_x=newx;
        newstate->estado_y=newy;
        newstate->next=NULL;
        newstate->prev=NULL;
        strcpy(newstate->name, newname);
        lista->cant=1;
        return 0;
    }
    
    miestado* recorrer=lista->p2first;    
    for(;(recorrer->next)!=NULL;recorrer=recorrer->next);     //recorro el arreglo dinàmico hasta llegar al ultimo elemento
    recorrer->next=newstate;
    newstate->estado_x=newx;
    newstate->estado_y=newy;
    newstate->next=NULL;
    newstate->prev=recorrer;
    strcpy(newstate->name, newname);
    (lista->cant)++;
    return 0;
}


int delstate(float delx, float dely, estadoheader* lista)
{
    miestado* recorrer=lista->p2first;

    for(;recorrer->estado_x!=delx || recorrer->estado_y!=dely;recorrer=recorrer->next)     //sigo recorriendo el arreglo hasta encontrar el estado con esas coordenadas
    {
        if(recorrer->next==NULL)                                                        //me fijo si es el ultimo para evitar seg fault
        {
            printf("No se selecciono un estado.\n");
            return -1;
        }
    }

    (recorrer->prev)->next=recorrer->next;
    (recorrer->next)->prev=recorrer->prev;
    
    free(recorrer);
    
    (lista->cant)--;
    
    return 0;
}

int addfun(float orgx, float orgy, float desx, float desy, char* newname, char* newevent, funcionheader* listaf, estadoheader* lista)
{
    miestado* getorg= lista->p2first;
    for(;getorg->estado_x!=orgx || getorg->estado_y!=orgy;getorg=getorg->next)
    {
        if(getorg->next==NULL)                                                        //me fijo si es el ultimo para evitar seg fault
        {
            printf("No se seleccionaron dos estados correctamente.\n");
            return -1;
        }
    }
    
    miestado* getdes= lista->p2first;
    for(;getdes->estado_x!=desx || getdes->estado_y!=desy;getdes=getdes->next)
    {
        if(getdes->next==NULL)                                                        //me fijo si es el ultimo para evitar seg fault
        {
            printf("No se seleccionaron dos estados correctamente.\n");
            return -1;
        }
    }
    
    
    mifuncion *newfun= (mifuncion*) calloc(1,sizeof(mifuncion));        //asigno el puntero al nuevo bloque, reservando memoria y haciendo un casteo del puntero
    if(newfun==NULL)
    {
        printf("Error: no hay espacio en memoria.\n");
        return -1;
    }
    
    if(listaf->p2first == NULL)   //en caso de que el arreglo este vacio
    {                                     
        lista->p2first=newfun;
        newfun->next=NULL;
        newfun->prev=NULL;
        strcpy(newfun->name, newname);
        strcpy(newfun->event, newevent);
        strcpy(newfun->destino, getdes->name);
        strcpy(newfun->origen, getorg->name);
        listaf->cant=1;
        return 0;
    }
    
    mifuncion* recorrer=lista->p2first;    
    for(;(recorrer->next)!=NULL;recorrer=recorrer->next);     //recorro el arreglo dinàmico hasta llegar al ultimo elemento
    recorrer->next=newfun;
    newfun->next=NULL;
    newfun->prev=recorrer;
    strcpy(newfun->name, newname);
    strcpy(newfun->event, newevent);
    strcpy(newfun->destino, getdes->name);
    strcpy(newfun->origen, getorg->name);
    (lista->cant)++;
    return 0;
}

int delfun(char* orgstate, char* delevent, funcionheader* listaf)
{
    mifuncion* recorrer=listaf->p2first;
    for(;!(strcmp(orgstate, recorrer->origen) || strcmp(delevent, recorrer->event) );recorrer=recorrer->next)
    {
        if(recorrer->next==NULL)                                                        //me fijo si es el ultimo para evitar seg fault
        {
            printf("No existe una transicion con las caracteristicas especificadas.\n");
            return -1;
        }
    }
    
    (recorrer->prev)->next=recorrer->next;
    (recorrer->next)->prev=recorrer->prev;
    
    free(recorrer);
    
    (listaf->cant)--;
    
    return 0;

}