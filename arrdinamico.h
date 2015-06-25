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
    miestado *next;
};

void agregarestado(miestado** p2state);
void quitarestado(miestado** p2state);
miestado* leerestado(int numofstate, miestado *p2state);
miestado* ultimoestado(miestado *p2state);

void delblock(int num_of_block_to_del,miestado *lista);
#endif	/* ARRDINAMICO_H */

