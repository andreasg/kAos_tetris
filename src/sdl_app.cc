#include "sdl_app.h"

bool sdl_app::init_sdl(std::string caption, int width, int height) {
  /* Init Subsystems */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) == -1) {
    std::cout << "failed to init SDL";
    return false;
  } else {
    atexit(SDL_Quit);
  }

  /* Init fonts */
  if (TTF_Init()==-1) {
    std::cout << "TTF_Init: " <<  TTF_GetError() << "\n";
    return false;
  } else {
    control::font = TTF_OpenFont("data/consola.ttf", 12);
    if (control::font == NULL) {
      std::cout << "faled to load font\n";
      std::cout << SDL_GetError();
      return false;
    }
  }
  
  /* Set window properties and get screen handle.*/
  window_width = width;
  window_height = height;
  scr = new main_canvas(window_width, window_height, 0, SDL_ANYFORMAT);
  if (scr->get_surface() == NULL) {
    std::cout << "failed to set videomode\n";
    return false;
  } else {
    SDL_WM_SetCaption(caption.c_str(), NULL);
  }
  return true;
}


void sdl_app::on_idle() {
  SDL_WaitEvent(NULL);
}
