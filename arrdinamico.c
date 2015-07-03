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

int createfsm(miestado* p2e, mifuncion* p2f, int cantestados, int cantfunciones)
{
        FILE* p2table;   // pointers to file

   if ((p2table= fopen("./Output/fsmtable.c", "w+"))
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
                    fprintf(p2table, "\t{""%s"",%s,%s},\n",recorrer_fun->event, leerestado(recorrer_fun->destiny,p2e)->name, recorrer_fun->name);
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

   if ((p2makefile= fopen("./Output/makefile", "w+"))
	   == NULL)
   {
	  printf("Cannot open input file.\n");
	  return -1;
   }
   
   int i;
   mifuncion* recorrer_fun=p2f;
        
   fprintf(p2makefile, "makefile: main.c fsm.c fsm.h fsmtable.c contador.c contador.h termlib.c termlib.h");
   for(i=0; i<cantfunciones; i++)
   {
       fprintf(p2makefile, "%s.c ", recorrer_fun->name);
       recorrer_fun=recorrer_fun->next;
   }
   
   fprintf(p2makefile, "\n\tgcc -o ppal ppal.c fsm.c ");
   recorrer_fun=p2f;
   for(i=0; i<cantfunciones; i++)
   {
       fprintf(p2makefile, "%s.c ", recorrer_fun->name);
       recorrer_fun=recorrer_fun->next;
   }
   
   fclose(p2makefile);
   return 0;
}




//Recibir un string que seria lo que pasa por terminal externa y el puntero la primer elemento del arreglo dinamico de funciones
//
//Devuelve puntero a mifuncion que coincide con el nombre o NULL si no hay concidencia

/*
mifuncion* getfun(char argv[],mifuncion* header){
	FILE* p2file=fopen("testfunciones.txt","r+");//Hay que cambiar el nombre del archivo
	if (p2file== NULL)
	{
		fprintf(stderr, "Cannot open input file.\n");
		return NULL;
   	}
	mifuncion* recorrer=header;
	int i;
	int running=1;
	char str_fun[20];	//al finalizar va a ser el nombre de la funcion que pasas por linea de comando (si esta correctamente escrita)
	char c;
	
	while(running)
	{
		for(i=0;i<=strlen(argv[]);i++)
		{
			if((c=fgetc(p2file))==EOF)
				running=0;
			else if((argv[i])==c)
			{
				*(str_fun+i)=c;
			}					//Motor de búsqueda.
			else break;
		}
		if (!strcmp(argv[],str_fun))
		{
			
			running=0;
		}
	}
	
	fclose(p2file);

	if (!strcmp(argv[1],str_fun))
	{
		printf("%s\n",str_fun);		//Testeo
	}
	else {printf("no hay concidencia\n");	//Testeo
		return NULL;}
	
	

	//Ahora quiero relacionar el nombre de la funcion que coincide con lo que pasas por la terminal externa con el nombre de la función//

	for (i=0;recorrer->next!=NULL;recorrer=recorrer->next)
            {
                if(!strcmp(recorrer->name,str_fun))
                   return recorrer;
            }
}
*/
