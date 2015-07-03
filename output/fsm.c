#include <stdio.h>
#include "fsm.h"



STATE* fsm(STATE *p_tabla_estado,char* evento_actual)
{

      printf(" >>%s<<\n ",evento_actual); //just for test (debug)
   	while (p_tabla_estado -> evento != evento_actual		//Recorre las tablas de estado
		   && p_tabla_estado -> evento != FIN_TABLA)
		++p_tabla_estado;
      (*p_tabla_estado -> p_rut_accion) ();          /*rutina de accion corresondiente*/
      p_tabla_estado=p_tabla_estado -> prx_estado;   /*siguiente estado*/


      return(p_tabla_estado);

}



