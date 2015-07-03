
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include "arrdinamico.h"
#include "createfiles.h"

int createfsm(miestado* p2e, mifuncion* p2f, int cantestados, int cantfunciones)
{
        FILE* p2table;   // pointers to file

   if ((p2table= fopen("./OUTPUT/fsmtable.c", "w+"))
	   == NULL)
   {
	  printf("Cannot open input file.\n");
	  return -1;
   }
        int i;
        int running=1;
        
        fprintf(p2table, "#include<stdio.h>\n#include\"fsm.h\"\n\n");
        
        miestado *estado_actual=p2e;
        mifuncion* recorrer_fun=p2f;
        
        if(estado_actual==NULL || recorrer_fun==NULL)
        {
            fprintf(stderr, "No es posible hacer la maquina de estados. No se encuentran estados o transiciones existentes.\n");
            return -1;
        }
        
        for(i=0;i<cantestados;i++)
        {
            fprintf(p2table,"extern STATE %s[];\n",estado_actual->name);
            estado_actual=estado_actual->next;
        }
        
        fprintf(p2table, "\n\n");
        estado_actual=p2e;
        
        for(i=0;i<cantfunciones;i++)
        {
            fprintf(p2table,"void %s (void);\n",recorrer_fun->name);
            recorrer_fun=recorrer_fun->next;
        }
        
        fprintf(p2table, "void reset_FSM (void);\n");
        
        fprintf(p2table, "\n\n");
        recorrer_fun=p2f;
        
        while(running)
        {            
            fprintf(p2table,"STATE %s[]=\n{\n",estado_actual->name);
            
            for (i=0;recorrer_fun!=NULL;recorrer_fun=recorrer_fun->next)
            {
                if(recorrer_fun->origin==estado_actual->cont)
                    fprintf(p2table, "\t{\"%s\",%s,%s},\n",recorrer_fun->event, leerestado(recorrer_fun->destiny,p2e)->name, recorrer_fun->name);
            }
	    fprintf(p2table,"\t{FIN_TABLA,%s,reset_FSM}\n};\n\n", leerestado(0, p2e)->name);
            estado_actual=estado_actual->next;
            recorrer_fun=p2f;
            
            if(estado_actual==NULL)
                running=0;
        }
        
        fprintf(p2table, "void reset_FSM (void)\n{\n\tprintf(\"Reset\");\n}\n\n");
        fprintf(p2table, "STATE* FSM_GetInitState(void)\n{\n\treturn (%s);\n}\n", p2e->name);
        fclose(p2table);
        
        return 0;
}

int createmakefile (miestado* p2e, mifuncion* p2f, int cantestados, int cantfunciones)
{
   FILE* p2makefile;   // pointers to file

   if ((p2makefile= fopen("./OUTPUT/makefile", "w+"))
	   == NULL)
   {
	  printf("Cannot open input file.\n");
	  return -1;
   }
   
   int i;   
    mifuncion* recorrer_fun=p2f;
       
   fprintf(p2makefile, "makefile: ppal.c fsm.c fsm.h fsmtable.c contador.c contador.h termlib.c termlib.h ");
    for(i=0; i<cantfunciones; i++)
   {
       fprintf(p2makefile, "%s.c ", recorrer_fun->name);
       recorrer_fun=recorrer_fun->next;
   }
    
        
   
   fprintf(p2makefile, "\n\tgcc -o ppal ppal.c fsm.c fsmtable.c contador.c termlib.c ");
   recorrer_fun=p2f;
   for(i=0; i<cantfunciones; i++)
   {
       fprintf(p2makefile, "%s.c ", recorrer_fun->name);
       recorrer_fun=recorrer_fun->next;
   }
   fclose(p2makefile);
   return 0;
}


