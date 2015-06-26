#ifndef ARRDINAM_H
#define ARRDINAM_H

typedef struct estado miestado;
struct estado{
    float estado_x;
    float estado_y;
    ALLEGRO_BITMAP *estadoimg;
    char name[20];
    miestado *next;
    miestado *prev;
};

typedef struct {
    int cant;
    miestado* p2first;
} estadoheader;

typedef struct funcion mifuncion;
struct funcion{
    char origen[20];
    char destino[20];
    char event[20];
    char name[20];
    mifuncion* next;
    mifuncion *prev;
};

typedef struct {
    int cant;
    mifuncion* p2first;
} funcionheader;

int addstate(float newx, float newy, char* newname, estadoheader *lista);
//addstate agrega un estado con las caracteristicas que le pases

int delstate(float delx, float dely, estadoheader *lista);
//delstate borra el estado que tenga las coordenadas que le pasas, si no hay un estado con esas coordenadas devuelve -1.

int addfun(float orgx, float orgy, float desx, float desy, char* newname, char* newevent, funcionheader* listaf, estadoheader* lista);
//addfun agrega una transicion. recibe coordenadas del estado de salida y de entrada, y el nombre de la funcion y el evento.
//  si no hay un estado en las coordenadas pasadas, devuelve -1.

int delfun(char* orgstate, char* delevent, funcionheader* listaf);
//delfun borra la transicion que sale del estado "orgstate" y tiene como evento "delevent".
//  si no hay una transicion con esas caracteristicas devuelve -1.

#endif
