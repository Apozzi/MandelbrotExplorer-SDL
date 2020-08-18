#ifndef IOCURSOR
#define IOCURSOR

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class IoCursor {
	private:

   public:
   	  // Posicao do mouse
      static Point* position;
      // Posicao do ultimo clique
	  static Point* lastClickPosition;
	  // estado
	  static int state;
	  // estado anterior
	  static int previousState;
	  // scroll
	  static int scroll;

      IoCursor() {
		  position = new Point(0,0);
		  lastClickPosition = new Point(0,0);
		  scroll = 0;
      }
      void defineCursorStateByEvent(SDL_Event e) {
	      if (e.type == SDL_MOUSEMOTION){
		    position->setX(e.motion.x);
			position->setY(e.motion.y);
	      } else
		  if (e.type == SDL_MOUSEBUTTONDOWN){
		    lastClickPosition->setX(e.motion.x);
			lastClickPosition->setY(e.motion.y);
			state = e.button.state;
	      } else
		  if (e.type == SDL_MOUSEBUTTONUP){
		    state = e.button.state;
	      } else
		  if(e.type == SDL_MOUSEWHEEL)
    	  {
			 scroll += e.wheel.y;
		  }
      }

      static int getX() {
	      return position->getX();
      }

	  static int getY() {
	      return position->getY();
      }

	  static int getScroll() {
	      return scroll;
      }

	  static int clicked() {
		  bool stateClicked = (state == SDL_PRESSED) && (previousState != state);
		  previousState = state;
	      return stateClicked;
      }

	 ~IoCursor() { 
       delete position;
       delete lastClickPosition;
     }

};


#endif
