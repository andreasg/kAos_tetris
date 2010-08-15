#ifndef KAOSTETRIS_TETRISUI
#define KAOSTETRIS_TETRISUI

#include <projectg.h>
#include <iostream>
#include <sstream>

class main_menu : public frame {
public:

  main_menu(application* game, int width, int height);
  virtual ~main_menu();

  bool init();
  bool on_message(msgid msg, void *param1, void *param2, void *param3, void *param4);


  static msgid msg_new_game;
  static msgid msg_exit_game;
  static msgid msg_resume_game;
private:
  application* game;

  button* new_game_button;
  button* exit_game_button;
  button* resume_button;
  button* options_button;

  static const int new_game_button_id = 0;
  static const int exit_game_button_id = 1;
  static const int resume_button_id = 2;
  static const int options_button_id = 3;
};


class hud : public frame {
public:
  hud(frame *parent, point pos, canvas* preview_canvas);
  void update_labels(int score, int level, int lines);

  virtual void on_draw();
private:
  canvas* _preview_canvas;
  label* _score_label;
  label* _level_label;
  label* _lines_label;
};

#endif
