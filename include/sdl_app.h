#ifndef KAOSTETRIS_SDLAPP
#define KAOSTETRIS_SDLAPP

#include <projectg.h>

class sdl_app : public event_handler {
public:
  sdl_app() {scr = NULL;}
  virtual ~sdl_app() {if (scr) delete scr;}
  virtual void on_idle();

protected:
  /** Initialize the SDL components.
   * @param caption Caption (title) of the window.
   * @param width Width of the window in pixels.
   * @param height Height of the window in pixels.
   * @return true if succesfull, else false. */
  bool init_sdl(std::string caption, int width, int height);

  /** Screen handle. */
  main_canvas* scr;
};

#endif
