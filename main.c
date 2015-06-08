/* 
 * File:   main.c
 * Author: Mercedes
 *
 * Created on 6 de junio de 2015, 17:23
 */

#include "stdio.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
 
const float FPS = 60;
const int SCREEN_W = 900;
const int SCREEN_H = 700;
const int BOUNCER_SIZE = 92;


int main(int argc, char **argv){
 
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP  *estado1   = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   float estado1_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float estado1_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;//lo hago aparecer en el medio
   float bouncer_dx = -4.0, bouncer_dy = 4.0; //velocidad de la pelotita
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   int mousestate = 0;
   
   if(!al_init()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   
    if(!al_install_keyboard()) {
   fprintf(stderr, "failed to initialize the keyboard!\n");
    return -1;
 }
 
 if(!al_init_image_addon()) {       //IMPORTANTÍSIMO!!!!!!!!!!
   al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                              NULL, ALLEGRO_MESSAGEBOX_ERROR);
    return 0;
 }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
   
   if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
   
   display = al_create_display(SCREEN_W,SCREEN_H);
   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!", 
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
 
   estado1 = al_load_bitmap("estado1.png");
   if(!estado1) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   
   al_set_target_bitmap(al_get_backbuffer(display));
   
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(estado1);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source()); //meti los tres eventos en la misma cola

   al_register_event_source(event_queue, al_get_mouse_event_source());
 
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
          mousestate = 1;
      }else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
          mousestate = 0;
      }else if(mousestate == 1){
          if(((estado1_x-46)<(ev.mouse.x)<(estado1_x+46)) && ((estado1_y-46)<(ev.mouse.y)<(estado1_y+46))){
          estado1_x = (ev.mouse.x)-46;
          estado1_y = (ev.mouse.y)-46;
          }
      }else if(ev.type == ALLEGRO_EVENT_KEY_UP){
          switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;              
          }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false; //cando ya dibuje, espero de nuevo al timer
 
         al_clear_to_color(al_map_rgb(0,0,0));
 
         al_draw_bitmap(estado1, estado1_x, estado1_y, 0);
 
         al_flip_display();
      }
   }

   
   
   

   al_destroy_bitmap(estado1);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}
