#ifndef IOKEYS
#define IOKEYS

#include <set>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>

class IoKeys {
   public:
      static std::set<int> keys;
      // Constructor definition
      IoKeys() {
         
      }
      void defineKeyStateByEvent(SDL_Event e) {
	      std::cout << "event_ocurred" << std::endl;
	      if (e.type == SDL_KEYDOWN){
		      int keyEvent = e.key.keysym.sym;
		      std::cout << "event=" + std::to_string(keyEvent) << std::endl; 
  		      keys.insert(keyEvent);
	      }
	      if (e.type == SDL_KEYUP) {
		      int keyEvent = e.key.keysym.sym; 
		      std::cout << "event_up = "+ std::to_string(keyEvent) << std::endl;
		      keys.erase(keyEvent);
	      }
      }
      static bool isKeyPressed(int key) {
	      return keys.find(key) != keys.end();
      }
   private:

};


#endif
