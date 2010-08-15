#ifndef KAOSTETRIS_TETRISGAME
#define KAOSTETRIS_TETRISGAME

#include <iostream>

#include "sdl_app.h"
#include "world.h"
#include "tetris_ui.h"

class tetris_game : public sdl_app {
public:
  tetris_game();
  virtual ~tetris_game();

  /** Update game logic and blit to screen. */
  void update();

  bool on_init(int argc, char *argv[]);
  void on_key_down(SDLKey k, SDLMod m, Uint16 unicode);
  virtual bool filter_event(SDL_Event* e);
  virtual bool on_message(msgid msg, void *param1, void *param2, void *param3, void *param4);

private:
  /** Create a new game. */
  void new_game();
  void close_game();
  /** Makes the current figure fall. */
  void update_game();
  /** Shortens the delay between update_game() calls.
   * @see update_game() */
  void increase_fall_speed();
  /** Increse the delay between update_game() calls.
   * @see update_game() */
  void decrease_fall_speed();
  /** Controls the pause status of the game. */
  void set_paused(bool paused) {this->paused = paused;}

  /** Small class to control the fps of the application. */
  class app_timer : public timer {
  public:
    /** Simply call the main applicatons update function. */
    void on_timer() { 
      static_cast<tetris_game*>(application::get_application())->update();
    }
  };
  
  /** Controls when the current figure is dropped. */
  int fall_time;
  /** Counter for when to drop the current figure. */
  int fall_ticks;

  /** Initial fall time for a new tetris game. */
  static const int INIT_FALL_TIME = 20; /* about one drop per second...*/

  /** Game paused status. */
  bool paused;

  bool freeze;
  /** Main menu */
  main_menu* ui;
  /** HUD */
  hud* _hud;
  /** The 'real' game. */
  world* game;
  /** Canvas to draw tetris on. */
  canvas* game_canvas;
  canvas* preview_figure_canvas;
  
  /** Update timer. Controls the fps. */
  app_timer app_clock;

  int _score;
  int _old_score;
  int _lines;
  int _level;

  void update_level();
  void update_preview();
};

#endif
