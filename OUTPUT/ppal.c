#include <stdio.h>

#include "contador.h"   /*Objeto contador usado para contar coincidencias*/
#include "fsm.h"	/*FSM engine*/

#include "termlib.h"    /*Enable the use of getch and getche see termlib.c*/


STATE *p2state=NULL;	/*Used to store FSM state*/



#define FIN_EVENTO  '\n'



int main (void)
{

     	char evento[20];
	char c;
	int n=0;
	p2state=FSM_GetInitState();// Inicializo la FSM con el estado inicial

	while((c = getchar())!= FIN_EVENTO){  //Si hay evento
		evento[n]=c;
		n++;
	}
	p2state=fsm(p2state,evento);      //Se lo paso a la maquina de estados
	

	printf("Total de coincidencias: %d", leer_cont());
  	getchar();
    
}

