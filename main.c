/* 
 * File:   main.c
 * Author: Gabriel
 *
 * Created on 6 de junio de 2015, 17:23
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
 
#include "arrdinamico.h"

const float FPS = 60;
const int SCREEN_W = 1000;
const int SCREEN_H = 700;
const int IMG_SIZE = 92;
const int BUTTON_SIZE_W = 250;
const int BUTTON_SIZE_H = 54;
const int BUTTONS_COLUMN = 725;
const int BUTTON1_FILE = 50;
const int BUTTON2_FILE = 130;
const int BUTTON3_FILE = 210;
const int BUTTON4_FILE = 300;
const int BUTTON5_FILE = 380;
const int BUTTON6_FILE = 460;
const int BUTTON_MAKEFILE_FILE = 570;

int main(int argc, char **argv){
 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP *nuevoestado = NULL;                      //creo los punteros a las imagenes correspondientes a los botones
   ALLEGRO_BITMAP *nuevatransicion = NULL;
   ALLEGRO_BITMAP *nuevafuncion = NULL;
   ALLEGRO_BITMAP *borrarestado = NULL;
   ALLEGRO_BITMAP *borrartransicion = NULL;
   ALLEGRO_BITMAP *borrarfuncion = NULL;
   ALLEGRO_BITMAP *makefile = NULL;
   ALLEGRO_BITMAP *blankspace = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   int mousestate = 0;
   int newstate = 0;
   int newtransicion = 0;
   int newfunction = 0;
   
   int var=0;
   int n=0;
   int contadordeestados=0;
   int estadoactual=0;
   miestado* listadeestados = NULL;

   if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "No se pudo inicializar allegro!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   
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
   
   if(!al_install_mouse()) {
      fprintf(stderr, "No se pudo inicializar el mouse!\n");
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
   blankspace = al_load_bitmap("blankspace.png");
   
   if(!nuevoestado || !nuevafuncion || !nuevatransicion || !borrarestado || !borrarfuncion || !borrartransicion || !makefile) {
      fprintf(stderr, "No se pudieron crear los bitmaps!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
  

   
   al_set_target_bitmap(al_get_backbuffer(display));
   
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
    
   al_init_primitives_addon();

   al_clear_to_color(al_map_rgb(255,255,255));
 
   al_flip_display(); 
 
   al_start_timer(timer); //no olvidar!!!!!
 
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
      else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
       
       for(n=0;n<contadordeestados;n++){
            if(((ev.mouse.x)<(leerestado(n,listadeestados)->estado_x+IMG_SIZE)) && (((ev.mouse.y)<(leerestado(n,listadeestados)->estado_y+IMG_SIZE))) 
               && ((leerestado(n,listadeestados)->estado_x)<ev.mouse.x) && ((leerestado(n,listadeestados)->estado_y)<ev.mouse.y)){
                mousestate = 1;
                estadoactual = n;
            }
       }
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON1_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON1_FILE)<ev.mouse.y)){
            newstate = 1;
       }
       
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON2_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON2_FILE)<ev.mouse.y)){
            newtransicion = 1;
       }
       
       if(((ev.mouse.x)<(BUTTONS_COLUMN+BUTTON_SIZE_W)) && (((ev.mouse.y)<(BUTTON3_FILE+BUTTON_SIZE_H))) && ((BUTTONS_COLUMN)<ev.mouse.x) && ((BUTTON3_FILE)<ev.mouse.y)){
            newfunction = 1;
       }
       
      }else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
          mousestate = 0;
      }else if((mousestate == 1)){
          //printf("El mouse esta en: %d\n",ev.mouse.x);        //Para pruebas
          
          leerestado(estadoactual,listadeestados)->estado_x = (ev.mouse.x)-IMG_SIZE/2;
          leerestado(estadoactual,listadeestados)->estado_y = (ev.mouse.y)-IMG_SIZE/2;

      }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
          switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;              
          }
      }else if((newstate == 1)){
          printf("Agregue estado\n");
          var=1;

          agregarestado(&listadeestados);
          (leerestado(contadordeestados,listadeestados))->estado_x = SCREEN_W / 2.0 - IMG_SIZE / 2.0;
          (leerestado(contadordeestados,listadeestados))->estado_y = SCREEN_H / 2.0 - IMG_SIZE / 2.0;
          (leerestado(contadordeestados,listadeestados))->estadoimg = al_load_bitmap("estado1.png");

          if(!(leerestado(contadordeestados,listadeestados))->estadoimg){
            fprintf(stderr, "No se pudo crear el bitmap!\n");
            al_destroy_display(display);
            al_destroy_timer(timer);
            return -1;
          }
          
          contadordeestados++;
          newstate=0;          
      }else if((newtransicion == 1)){
          printf("Aregue transicion\n");
      }else if((newfunction == 1)){
          printf("Agregue funcion\n");
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false; //cando ya dibuje, espero de nuevo al timer
 
         al_clear_to_color(al_map_rgb(255,255,255));
         if(var==1)
         {
             for(n=0;n<contadordeestados;n++){
                al_draw_bitmap(leerestado(n,listadeestados)->estadoimg, leerestado(n,listadeestados)->estado_x, leerestado(n,listadeestados)->estado_y, 0);
             } 
         }
         al_draw_bitmap(nuevoestado, BUTTONS_COLUMN, BUTTON1_FILE, 0);
         al_draw_bitmap(nuevatransicion, BUTTONS_COLUMN, BUTTON2_FILE, 0);
         al_draw_bitmap(nuevafuncion, BUTTONS_COLUMN, BUTTON3_FILE, 0);
         al_draw_bitmap(borrarestado, BUTTONS_COLUMN, BUTTON4_FILE, 0);
         al_draw_bitmap(borrartransicion, BUTTONS_COLUMN, BUTTON5_FILE, 0);
         al_draw_bitmap(borrarfuncion, BUTTONS_COLUMN, BUTTON6_FILE, 0);         
         al_draw_bitmap(makefile, BUTTONS_COLUMN, BUTTON_MAKEFILE_FILE, 0);
         
         for(n=(IMG_SIZE)/2;n<(SCREEN_W-BUTTON_SIZE_W);n=n+IMG_SIZE)
         {
           al_draw_line(n,0,n,7.5*IMG_SIZE,al_map_rgb(0,255,0),2);             
         }
         
         for(n=(IMG_SIZE)/2;n<SCREEN_H;n=n+IMG_SIZE)
         {
           al_draw_line(0,n,7.5*IMG_SIZE,n,al_map_rgb(0,255,0),2);             
         }

         al_flip_display();
      }
   }

   for(n=0;n<contadordeestados;n++){
        al_destroy_bitmap(leerestado(n,listadeestados)->estadoimg);
   }
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}

