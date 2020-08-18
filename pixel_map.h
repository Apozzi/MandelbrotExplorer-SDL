#ifndef PIXEL_MAP
#define PIXEL_MAP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <math.h>
#include "utils/error_logger.h"
#include <vector>

class PixelMap{
  protected:
    SDL_Texture* texture;
    int texWidth;
    int texHeight;
    std::vector< unsigned char > pixels;
  public:

  PixelMap(int texWidth, int texHeight) : texWidth(texWidth), texHeight(texHeight) {
      pixels = std::vector< unsigned char >( texWidth * texHeight * 4, 0 );
  }

  void init (SDL_Renderer *renderer) {
    texture = SDL_CreateTexture
        (
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        texWidth, texHeight
        );
  }

  void render(SDL_Renderer *renderer) {
    SDL_UpdateTexture
    (
    texture,
    NULL,
    &pixels[0],
    texWidth * 4
    );
    SDL_RenderCopy( renderer, texture, NULL, NULL );
  }

  void putPixel(int x, int y, int r, int g, int b) {
      const unsigned int offset = ( texWidth * 4 * y ) + x * 4;
      pixels[ offset + 0 ] = b % 256;             // b
      pixels[ offset + 1 ] = g % 256;             // g
      pixels[ offset + 2 ] = r % 256;             // r
      pixels[ offset + 3 ] = SDL_ALPHA_OPAQUE;    // a
  }

  void random() {
      for( unsigned int i = 0; i < 1000; i++ )
      {
            this->putPixel(rand() % texWidth, rand() % texHeight, rand(), rand(), rand());
      }
  }


};

#endif
