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

#endif	/* ARRDINAMICO_H */

