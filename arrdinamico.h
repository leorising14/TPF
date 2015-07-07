/* 
 * File:   arrdinamico.h
 * Author: Gabriel
 *
 * Created on 23 de junio de 2015, 19:13
 */

#ifndef ARRDINAMICO_H
#define	ARRDINAMICO_H

typedef struct estado miestado;
struct estado{
    float estado_x;
    float estado_y;
    ALLEGRO_BITMAP *estadoimg;
    int cont;
    int check; //chequea si tiene alguna conexion entre otro estado
    char* name;
    miestado *next;
};

typedef struct funcion mifuncion;
struct funcion{
    int origin;
    int destiny;
    int cont;
    char* event;
    char* name;
    mifuncion* next;
    //mifuncion *prev;
};

void agregarestado(miestado** p2state);
miestado* quitarestado(int num_of_block_to_del,miestado *lista);
miestado* leerestado(int numofstate, miestado *p2state);

void agregarfuncion(mifuncion** p2state);
mifuncion* quitarfuncion(int num_of_block_to_del,mifuncion *lista);
mifuncion* leerfuncion(int numofstate, mifuncion *p2state);



//mifuncion* getfun(char argv[],mifuncion* header);
#endif	/* ARRDINAMICO_H */

