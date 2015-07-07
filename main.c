/*
/* 
/
/	TRABAJO PRÁCTICO FINAL: Generador de máquinas de estados	/
/
/*
Grupo Nº 2:
	Gabriel Cufaro
	Leandro Luo
	Bernardo Michel
	Agustín De Ruschi
 * 
 * https://github.com/leorising14/TPF.git
 * 
 Created on 6 de junio de 2015, 17:23
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <conio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "arrdinamico.h"
#include "createfiles.h"
#include "allegrogetchar.h"

const float FPS = 60;
const int SCREEN_W = 1000;                                  //tamaño de la pantalla
const int SCREEN_H = 700;
const int IMG_SIZE = 92;                                    //tamaño de la imagen que representa los estados
const int BUTTON_SIZE_W = 250;                              //el tamaño de los botones, si se quiere usar otros botones, basta con cambiar las dos constantes
const int BUTTON_SIZE_H = 54;
const int BUTTONS_COLUMN = 725;                             //me define en que columna pongo los botones
const int BUTTON1_FILE = 50;                                //constantes que me definen en que filas pongo los botones
const int BUTTON2_FILE = 130;
const int BUTTON3_FILE = 210;
const int BUTTON4_FILE = 300;
const int BUTTON5_FILE = 380;
const int BUTTON6_FILE = 460;
const int BUTTON_MAKEFILE_FILE = 570;
const int ARROW_WIDTH = 30;                                 //para cambiar el tamaño de la flecha en las lineas de transiciones
const int ARROW_HEIGHT = 20;

int main(int argc, char **argv){
 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP *nuevoestado = NULL;                      //creo los punteros a las imagenes correspondientes a los botones
   ALLEGRO_BITMAP *nuevatransicion = NULL;
   ALLEGRO_BITMAP *nuevafuncion = NULL;
   ALLEGRO_BITMAP *borrarestado = NULL;
   ALLEGRO_BITMAP *borrartransicion = NULL;
   ALLEGRO_BITMAP *borrarfuncion = NULL;
   ALLEGRO_BITMAP *makefile = NULL;
   ALLEGRO_BITMAP *arrow = NULL;
   ALLEGRO_BITMAP *info = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   
   bool redraw = true;
   bool doexit = false;

   char mimensaje1[]={"Ingrese el nombre del estado"}; //strings que uso para mostrar mensajes en pantalla y escribir
   char mimensaje2[]={"Ingrese el nombre del evento "};
   char mimensaje3[]={"Ingrese el nombre de la funcion "};
   char mimensaje4[]={"Ingrese el nombre del estado de salida "};
   char mimensaje5[]={"Ingrese el nombre del estado de llegada "};
   char mimensaje6[]={"Ingrese el nombre del evento a borrar "};
   char mimensaje7[]={"Ingrese el nombre del estado a borrar "};
   char textbox[]={"Aqui se veran las acciones "};

   
   char* strfun;
   char* string1;
   char* string2;
   char* string3;

   int mousestate = 0;              //me define si el mouse esta presionado o no
   int newstate = 0;
   int newtransicion = 0;
   int origentransicion = -1;       //pongo en valor default ya que se puede confundir con el estado 0
   int destinotransicion = -1;
   int newfunction = 0;
   int erasestate = 0;
   int erasetransicion = 0;
   int erasefunction = 0;
   int newmakefile = 0;
   int openinfo = 0;
   
   int xf=0;                          //Variables que me simplifican MUCHISIMO dibujar las lineas, los splines y las flechas
   int xi=0;
   int yf=0;
   int yi=0;
   int px1=0;                         //coordenadas que uso para las flechas
   int py1=0;
   int px2=0;
   int py2=0;
   
   int var=0;                       //contadores varios
   int n=0;
   int i=0;

   int contadordeestados=0;
   int contadordefunciones=0;
   int estadoactual=0;
   miestado* listadeestados = NULL;
   mifuncion* listadetransiciones = NULL;

   if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "No se pudo inicializar allegro!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   
   const ALLEGRO_COLOR MYRED = al_map_rgb(255, 0, 0);               //en el caso de que se quiera cambiar el color de la pantalla y de las lineas
   const ALLEGRO_COLOR MYWHITE = al_map_rgb(255, 255, 255);
   const ALLEGRO_COLOR MYBLACK = al_map_rgb(0, 0, 0);
   const ALLEGRO_COLOR MYBLUE = al_map_rgb(0, 0, 255);
   const ALLEGRO_COLOR MYLIGHTGREEN = al_map_rgb(0, 255, 0);
   
   ALLEGRO_COLOR myArrowColor = MYBLUE;                                //defino el color de flecha que voy a utilizar
   
   if(!al_install_keyboard()) {
    fprintf(stderr, "No se pudo inicializar el teclado!\n");
    return -1;
   }
 
   if(!al_init_image_addon()) {       //IMPORTANTÍSIMO!!!!!!!!!!
        al_show_native_message_box(display, "Error", "Error", "No se pudo inicializar al_init_image_addon!", 
                              NULL, ALLEGRO_MESSAGEBOX_ERROR);
     return 0;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "No se pudo crear el timer!\n");
      return -1;
   }
   
   if(!al_install_mouse()){
      fprintf(stderr, "No se pudo inicializar el mouse!\n");
      return -1;
   }
   
   al_init_font_addon(); // initialize the font addon
   
   if(!al_init_ttf_addon()){
      fprintf(stderr, "No se pudo inicializar el addon de ttf!\n");
      return -1;
   }
   
   display = al_create_display(SCREEN_W,SCREEN_H);
   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "No se pudo inicializar el display!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
 
   nuevoestado = al_load_bitmap("nuevoestado.png");                 //cargo las imágenes de los botones correspondientes
   nuevafuncion = al_load_bitmap("nuevafuncion.png");
   nuevatransicion = al_load_bitmap("nuevatransicion.png");
   borrarestado = al_load_bitmap("borrarestado.png");
   borrarfuncion = al_load_bitmap("borrarfuncion.png");
   borrartransicion = al_load_bitmap("borrartransicion.png");
   makefile = al_load_bitmap("makefile.png");
   arrow = al_load_bitmap("arrow.png");
   info = al_load_bitmap("info.png");
   
   if(!nuevoestado || !nuevafuncion || !nuevatransicion || !borrarestado || !borrarfuncion || !borrartransicion || !makefile || !arrow || !info) {
      fprintf(stderr, "No se pudieron crear los bitmaps!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   ALLEGRO_FONT *font = al_load_ttf_font("serif.ttf",20,0);  
 
   if (!font){
      fprintf(stderr, "Could not load 'serif.ttf'.\n");
      return -1;
   }
   
   al_set_target_bitmap(al_get_backbuffer(display));            //creo el buffer en donde voy a poner los eventos del display, del timer, del mouse y del teclado
   
   event_queue = al_create_event_queue();
   
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source()); //meti los tres eventos en la misma cola

   al_register_event_source(event_queue, al_get_mouse_event_source());
    
   al_init_primitives_addon();                                             //inicializo el addon de primitivas de lo contrario no voy a poder dibujar las flechas

   al_clear_to_color(MYWHITE);                                              //pongo la pantalla en blanco
 
   al_flip_display(); 
 
   al_start_timer(timer); //arranco con el timer
 
    while(1)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
     
      if(ev.type == ALLEGRO_EVENT_TIMER) {
         redraw = true;//redibujo cuando toca el timer
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {     //en el caso de que haga click, puede pasar que el usuario quiera mover un estado, o usar la botonera
       
       for(n=0;n<contadordeestados;n++){        //para mover todas las bolitas de estado que estan en la pantallas
            if(((ev.mouse.x)<(leerestado(n,listadeestados)->estado_x+IMG_SIZE)) && (((ev.mouse.y)<(leerestado(n,listadeestados)->estado_y+IMG_SIZE))) 
               && ((leerestado(n,listadeestados)->estado_x)<ev.mouse.x) && ((leerestado(n,listadeestados)->estado_y)<ev.mouse.y)){
                    mousestate = 1;
                    estadoactual = n;
                    if((newtransicion == 1) || (erasetransicion == 1))
                    {
                        if(origentransicion == -1)
                        {
                            origentransicion = n;
                        }else{
                            destinotransicion = n; 
                        }                       
                    }
            }  
       }
       
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON1_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON1_FILE)<ev.mouse.y)){  //me fijo si se apreto algun boton
            newstate = 1;
       }
       
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON2_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON2_FILE)<ev.mouse.y)){
            newtransicion = 1;
       }
       
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON3_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON3_FILE)<ev.mouse.y)){
            newfunction = 1;
       }
       
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON4_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON4_FILE)<ev.mouse.y)){
            erasestate = 1;
            printf("El estado actual es: %d \n",estadoactual); //debug
       }

       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON5_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON5_FILE)<ev.mouse.y)){
            erasetransicion = 1;
       }

       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON6_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON6_FILE)<ev.mouse.y)){
            erasefunction = 1;
       }       
       
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON_MAKEFILE_FILE+BUTTON_SIZE_H+30))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON_MAKEFILE_FILE)<ev.mouse.y)){
            newmakefile = 1;
       }     
       
       if(((ev.mouse.x)<(SCREEN_W-80+50)) && (((ev.mouse.y)<(53))) && ((SCREEN_W-80)<ev.mouse.x) && ((3)<ev.mouse.y)){
            openinfo = 1;
       } 
       
      }else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
          mousestate = 0;
      }else if((mousestate == 1)){
          //printf("El mouse esta en: %d\n",ev.mouse.x);        //Para pruebas
          if((((ev.mouse.x)<7.5*IMG_SIZE))&&((ev.mouse.y)<SCREEN_H-IMG_SIZE)&&((ev.mouse.x)>IMG_SIZE/2)&&((ev.mouse.y)>IMG_SIZE/2)){        //si el mouse esta dentro de la pantalla, procedo a mover
            leerestado(estadoactual,listadeestados)->estado_x = (ev.mouse.x)-IMG_SIZE/2;                                                    //muevo mi bolita de acuerdo al mouse
            leerestado(estadoactual,listadeestados)->estado_y = (ev.mouse.y)-IMG_SIZE/2;
          }
          
      }else if(ev.type == ALLEGRO_EVENT_KEY_UP){                //me fijo si aprete X para salir del programa
          switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;              
          }
      }else if((newstate == 1)){        //en el caso de que se haya apretado el boton de agregar estado
          
          printf("Agregue estado\n");
          var=1;                        //esto es para que luego no dibuje cuando se ejecute el programa

          agregarestado(&listadeestados);           //agrego un estado e inicializo los campos correspondientes
          (leerestado(contadordeestados,listadeestados))->estado_x = SCREEN_W / 2.0 - IMG_SIZE / 2.0;
          (leerestado(contadordeestados,listadeestados))->estado_y = SCREEN_H / 2.0 - IMG_SIZE / 2.0;
          (leerestado(contadordeestados,listadeestados))->estadoimg = al_load_bitmap("estado1.png");
          (leerestado(contadordeestados,listadeestados))->cont = contadordeestados;
          leerestado(contadordeestados,listadeestados)->check = 0;
          
          if(!(leerestado(contadordeestados,listadeestados))->estadoimg){   //si no se encuentra la imagen del puntero, mando un mensaje de error
            fprintf(stderr, "No se pudo crear el bitmap!\n");
            al_destroy_display(display);
            al_destroy_timer(timer);
            return -1;
          }
          
          printf("Ingrese el nombre del estado: "); //mensaje1
          strfun = (char *) getcharallegro(display,font,mimensaje1);
/*
          for(n=0;(strfun[n] = getchar())!='\n';n++){};
          strfun[n]='\0';
*/
          
          char* p2char=(char*)malloc(20);
          strcpy(p2char,strfun);
          leerestado(contadordeestados,listadeestados)->name=p2char;
          
    //      for(n=0;n<contadordeestados+1;n++)
    //          printf("%s\n",leerestado(n,listadeestados)->name );
          
          contadordeestados++;
          newstate=0;                                       //para que se ejecute una sola vez cuando presione el boton
          strcpy(textbox,"Agregue estado");
      }else if((newtransicion == 1) && (origentransicion != -1) && (destinotransicion != -1)){         //en el caso de que se haya apretado el boton de agregar transicion, y se hayan apretado los dos estados a unir
          printf("Aregue transicion\n");
          printf("El origen de la transicion es: %d\n", origentransicion);
          printf("El destino de la transicion es: %d\n", destinotransicion);
          
          (leerestado(origentransicion,listadeestados)->check)++;
          (leerestado(destinotransicion,listadeestados)->check)++;
          
          agregarfuncion(&listadetransiciones);
          leerfuncion(contadordefunciones,listadetransiciones)->origin = origentransicion;
          leerfuncion(contadordefunciones,listadetransiciones)->destiny = destinotransicion;
          leerfuncion(contadordefunciones,listadetransiciones)->cont = contadordefunciones;
          
          printf("Ingrese el nombre del evento: "); //mensaje2
         
          strfun = (char *) getcharallegro(display,font,mimensaje2);
          char* p2char=(char*)malloc(20);
          strcpy(p2char,strfun);
          leerfuncion(contadordefunciones,listadetransiciones)->event=p2char;
          
          newtransicion = 0;                                       //para que se ejecute una sola vez cuando presione el boton
          origentransicion = -1;                                    //vuelvo al valor default de origen y destino
          destinotransicion = -1;
          contadordefunciones++;
          
          strcpy(textbox,"Agregue transicion");
      }else if((newfunction == 1)){        //en el caso de que se haya apretado el boton de agregar funcion
          printf("Agregue funcion\n");
          printf("Ingrese el nombre de la funcion: ");           
          strfun = (char *) getcharallegro(display,font,mimensaje3);
          
          printf("Ingrese el nombre del estado de salida: ");           
          string1 = (char *)getcharallegro(display,font,mimensaje4);
          
          printf("Ingrese el nombre del estado de llegada: ");           

          string2 = (char *) getcharallegro(display,font,mimensaje5);
          
          for(n=0;n<contadordefunciones;n++){
              //printf("%d\n",strcmp(string1,leerestado((leerfuncion(n,listadetransiciones)->origin),listadeestados)->name));
              //printf("%d\n",strcmp(string2,leerestado((leerfuncion(n,listadetransiciones)->destiny),listadeestados)->name));
              if(strcmp(string1,leerestado((leerfuncion(n,listadetransiciones)->origin),listadeestados)->name)==0){
                  if(strcmp(string2,leerestado((leerfuncion(n,listadetransiciones)->destiny),listadeestados)->name)==0)
                  {
                    char* p2char2=(char*)malloc(20);
                    strcpy(p2char2,strfun);
                    leerfuncion(n,listadetransiciones)->name = p2char2;
                    printf("Su funcion es: %s\n",leerfuncion(n,listadetransiciones)->name);
                  }
                  strcpy(textbox,"Agregue funcion");                  
              }else{
                  printf("No se pudo crear la función porque no hay coincidencia con los nombres de los estados");
                  strcpy(textbox,"No se pudo crear la función porque no hay coincidencia con los nombres de los estados");               
              }
          }

          newfunction = 0;                                       //para que se ejecute una sola vez cuando presione el boton

      }else if((erasestate == 1)){        //en el caso de que se haya apretado el boton de borrar estado
          printf("Borre estado \n");
          
          string1 = (char *)getcharallegro(display,font,mimensaje7);
          
          for(n=0;n<contadordeestados;n++){
              if(strcmp((leerestado(n,listadeestados)->name), string1) == 0){
                  
                listadeestados=quitarestado(n,listadeestados);  //me regresa el puntero nuevo de listadeestados (esto por si se elimina el primer estado)
                n=contadordeestados;
              }
          }
          
          for(n=0;n<contadordefunciones;n++){
              if((leerfuncion(n,listadetransiciones)->origin == estadoactual) || (leerfuncion(n,listadetransiciones)->destiny == estadoactual)){
               for(i=0;i<contadordefunciones;i++){
                  if((leerfuncion(i,listadetransiciones)->origin > estadoactual)){      //si borre un estado, tengo que disminuir el contador de origen y destino en las transiciones
                    leerfuncion(i,listadetransiciones)->origin--;
                  }
                  if((leerfuncion(i,listadetransiciones)->destiny > estadoactual)){
                    leerfuncion(i,listadetransiciones)->destiny--;
                  }
               }
              listadetransiciones = quitarfuncion(n,listadetransiciones);
              n--;
              contadordefunciones--;
              }                  
          }

          contadordeestados--;                                  //como se borro un estado, tengo uno menos!
          erasestate = 0;                                       //para que se ejecute una sola vez cuando presione el boton
          strcpy(textbox,"Borre estado");
      }else if((erasetransicion == 1) && (origentransicion != -1) && (destinotransicion != -1)){        //en el caso de que se haya apretado el boton de borrar transicion
          printf("Borre transicion \n");
          
          printf("Ingrese el nombre del evento a borrar: ");
          strfun = (char *) getcharallegro(display,font, mimensaje6);
          
          (leerestado(origentransicion,listadeestados)->check)++;
          (leerestado(destinotransicion,listadeestados)->check)--;
          
          i=contadordefunciones;
          for(n=0;n<contadordefunciones;n++){
              if(((leerfuncion(n,listadetransiciones)->origin)==origentransicion) && ((leerfuncion(n,listadetransiciones)->destiny)==destinotransicion) && ((strcmp(strfun,leerfuncion(n,listadetransiciones)->event))==0)){
                listadetransiciones=quitarfuncion(n,listadetransiciones);    
                n--;
                contadordefunciones--;
              }
          }
          
          if(i==contadordefunciones){
              printf("Ud selecciono dos estados que no tienen transicion entre si, o un evento invalido. Intentelo nuevamente \n");
              strcpy(textbox,"Ud selecciono dos estados que no tienen transicion entre si, o un evento invalido. Intentelo nuevamente");
          }else{          
              strcpy(textbox,"Borre transicion"); 
          }
    
          erasetransicion = 0;                                       //para que se ejecute una sola vez cuando presione el boton
          origentransicion = -1;                                    //vuelvo al valor default de origen y destino
          destinotransicion = -1;
      }else if((erasefunction == 1)){        //en el caso de que se haya apretado el boton de borrar funcion
          printf("Borre funcion \n");
          
          
          printf("Ingrese el nombre del estado de salida: ");           
          string1 = (char *) getcharallegro(display,font, mimensaje4);
          printf("Ingrese el nombre del estado de llegada: ");           
          string2 = (char *) getcharallegro(display,font, mimensaje5);
          printf("Ingrese el nombre del evento: ");
          string3 = (char *) getcharallegro(display,font, mimensaje2);
          
          for(n=0;n<contadordefunciones;n++){
              //printf("%d\n",strcmp(string1,leerestado((leerfuncion(n,listadetransiciones)->origin),listadeestados)->name));
              //printf("%d\n",strcmp(string2,leerestado((leerfuncion(n,listadetransiciones)->destiny),listadeestados)->name));
              if(strcmp(string1,leerestado((leerfuncion(n,listadetransiciones)->origin),listadeestados)->name)==0){
                  if(strcmp(string2,leerestado((leerfuncion(n,listadetransiciones)->destiny),listadeestados)->name)==0)
                  {
                    if(strcmp(string3,(leerfuncion(n,listadetransiciones)->event))==0)
                    {
                       (leerfuncion(n,listadetransiciones)->name)=NULL;
                    }
                  }
              }
          }
          
          erasefunction = 0;                                       //para que se ejecute una sola vez cuando presione el boton
          strcpy(textbox,"Borre funcion");   
      }else if((newmakefile == 1)){        //en el caso de que se haya apretado el boton de hacer makefile
          printf("Se esta por generar el makefile! \n");
          i=0;
          for(n=0;n<contadordeestados;n++){
              if((leerestado(n,listadeestados)->check)==0){
                  i=1;
              }
          }
          if(i==0){
            createfsm(listadeestados, listadetransiciones, contadordeestados, contadordefunciones);
            createmakefile(listadeestados, listadetransiciones, contadordeestados, contadordefunciones);
            printf("Disfrute de su maquina de estados personalizada. \n");
            strcpy(textbox,"Se ha generado el makefile");
          }else{
             strcpy(textbox,"No ha conectado todos los estados, intente de nuevo.");
          }
          newmakefile = 0;                                       //para que se ejecute una sola vez cuando presione el boton

      }else if(openinfo == 1){
          printf("Abriendo las instrucciones \n");     
          openinfo = 0;
          openinstructions(display, font);
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false; //cando ya dibuje, espero de nuevo al timer
 
         al_clear_to_color(MYWHITE);
         
         if(contadordefunciones>0){                             //dibujo las transiciones y las flechas
                 for(n=0;n<contadordefunciones;n++){
                     xi=(leerestado(leerfuncion(n,listadetransiciones)->origin,listadeestados))->estado_x+IMG_SIZE/2;   //defino las coordenadas (¡centrales!) de los estados de origen y destino
                     yi=(leerestado(leerfuncion(n,listadetransiciones)->origin,listadeestados))->estado_y+IMG_SIZE/2;
                     xf=(leerestado(leerfuncion(n,listadetransiciones)->destiny,listadeestados))->estado_x+IMG_SIZE/2;
                     yf=(leerestado(leerfuncion(n,listadetransiciones)->destiny,listadeestados))->estado_y+IMG_SIZE/2;
                     px1=xf-((IMG_SIZE-10)/2)*cos(atan2((yf-yi),(xf-xi)));           //punto en la periferia del globito que coincide con la linea de union entre globitos
                     py1=yf-((IMG_SIZE-10)/2)*sin(atan2((yf-yi),(xf-xi)));
                     px2=xf-(((IMG_SIZE-10)/2)+ARROW_WIDTH)*cos(atan2((yf-yi),(xf-xi)));      //punto del otro extremo de la flecha
                     py2=yf-(((IMG_SIZE-10)/2)+ARROW_WIDTH)*sin(atan2((yf-yi),(xf-xi)));
                     al_draw_line(xi,yi,xf,yf,myArrowColor,4);
                     al_draw_filled_triangle(px1,py1,px2,py2,px2-10*cos(-M_PI_2+atan2((yf-yi),(xf-xi))),py2-ARROW_HEIGHT/2*sin(-M_PI_2+atan2((yf-yi),(xf-xi))),myArrowColor);  //dibujo la flecha mediante dos triangulos
                     al_draw_filled_triangle(px1,py1,px2,py2,px2+10*cos(-M_PI_2+atan2((yf-yi),(xf-xi))),py2+ARROW_HEIGHT/2*sin(-M_PI_2+atan2((yf-yi),(xf-xi))),myArrowColor);
                     if((leerfuncion(n,listadetransiciones)->name) != NULL)
                     al_draw_text(font,MYBLACK,(xi+xf)/2,(yi+yf)/2,ALLEGRO_ALIGN_CENTER,leerfuncion(n,listadetransiciones)->name);
                     al_draw_text(font,MYBLACK,px1,py1+40,ALLEGRO_ALIGN_LEFT,leerfuncion(n,listadetransiciones)->event);
             }
          } 
         
         if(var==1)
         {
             for(n=0;n<contadordeestados;n++){          //dibujo todos los estados en la pantalla: en el caso que dos estados se superpongan, tiene prioridad el mas recientemente creado para mostrarse ya que fue el ultimo en dibujarse (lo mismo se aplica para moverlo)
                al_draw_bitmap(leerestado(n,listadeestados)->estadoimg, leerestado(n,listadeestados)->estado_x, leerestado(n,listadeestados)->estado_y, 0);
                al_draw_text(font,MYWHITE,leerestado(n,listadeestados)->estado_x+IMG_SIZE/2, leerestado(n,listadeestados)->estado_y+IMG_SIZE/2-10, ALLEGRO_ALIGN_CENTER, leerestado(n,listadeestados)->name);
             } 
         }
 
         al_draw_bitmap(nuevoestado, BUTTONS_COLUMN, BUTTON1_FILE, 0);          //dibujo todos los botones
         al_draw_bitmap(nuevatransicion, BUTTONS_COLUMN, BUTTON2_FILE, 0);
         al_draw_bitmap(nuevafuncion, BUTTONS_COLUMN, BUTTON3_FILE, 0);
         al_draw_bitmap(borrarestado, BUTTONS_COLUMN, BUTTON4_FILE, 0);
         al_draw_bitmap(borrartransicion, BUTTONS_COLUMN, BUTTON5_FILE, 0);
         al_draw_bitmap(borrarfuncion, BUTTONS_COLUMN, BUTTON6_FILE, 0);         
         al_draw_bitmap(makefile, BUTTONS_COLUMN, BUTTON_MAKEFILE_FILE, 0);
         al_draw_bitmap(info, SCREEN_W-80, 3, 0);
         
         al_draw_text(font, MYBLACK, 30, SCREEN_H-40, ALLEGRO_ALIGN_LEFT, textbox);
         
         //al_draw_spline(spline,al_map_rgb(255,0,0),2);
         
/*       //grilla (opcional)
         for(n=(IMG_SIZE)/2;n<(SCREEN_W-BUTTON_SIZE_W);n=n+IMG_SIZE)
         {
           al_draw_line(n,0,n,7.5*IMG_SIZE,MYLIGHTGREEN,2);             
         }
         
         for(n=(IMG_SIZE)/2;n<SCREEN_H;n=n+IMG_SIZE)
         {
           al_draw_line(0,n,7.5*IMG_SIZE,n,MYLIGHTGREEN,2);             
         }
*/

         al_flip_display();     //pongo todo los dibujos en pantalla
      }
   }

   for(n=0;n<contadordeestados;n++){                                    //libero todos los recursos usados por todos los bitmaps, la fuente, etc...
        al_destroy_bitmap(leerestado(n,listadeestados)->estadoimg);
   }
   al_destroy_font(font);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

