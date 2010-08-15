#include "tetris_ui.h"

/** Send on the click of a new_game button. */
msgid main_menu::msg_new_game = message_handler::get_next_msgid();

/** Send on click of a exit_game button. */
msgid main_menu::msg_exit_game = message_handler::get_next_msgid();

/** Send on click of a resume button. */
msgid main_menu::msg_resume_game = message_handler::get_next_msgid();

main_menu::main_menu(application* game, int width, int height) : frame(NULL, rect(0,0,width,height)) {
  this->game = game;
  new_game_button = NULL;
  exit_game_button = NULL;
  resume_button = NULL;
  options_button = NULL;
}

main_menu::~main_menu() {
  if (new_game_button)  delete new_game_button;
  if (exit_game_button) delete exit_game_button;
  if (resume_button)    delete resume_button;
  if (options_button)   delete options_button;
}


bool main_menu::init() {
  rect r = rect(int(get_h()*0.05),int(get_w()*0.1), int(get_w()*0.9), 20);
  point offset = point(0,int(get_h()*0.05));


  new label(this,(r-offset)+point(get_w()/3, 0), "kAos TETRIS");

  new_game_button = new button(this, "new game", r, main_menu::new_game_button_id);

  r += offset;
  resume_button = new button(this, "resume game", r, main_menu::resume_button_id);

  r += offset*2;
  exit_game_button = new button(this, "quit", r, main_menu::exit_game_button_id);

  return true;
}

bool main_menu::on_message(msgid msg, void *param1, void *param2, void *param3, void *param4) {
  if (msg == button::msgid_button_click) {
    switch(int(param1)) {
    case main_menu::new_game_button_id:
      game->on_message(main_menu::msg_new_game, this, 0,0,0);
      return true;
    case main_menu::exit_game_button_id:
      game->on_message(main_menu::msg_exit_game, this, 0,0,0);
      return true;
    case main_menu::resume_button_id:
      game->on_message(main_menu::msg_resume_game, this, 0,0,0);
      return true;
    case main_menu::options_button_id:
      return true;
    default: break;
    }
  }
  return false;
}




hud::hud(frame* parent, point pos, canvas* preview_canvas) \
  : frame(NULL, rect(pos.get_x(), pos.get_y(),290,640)) {
  
  rect dim = rect(10, 10, 150, 20);
  point offset(0, 30);
  new label(this, dim, "next figure:");

  dim += offset*6;
  new label(this, dim, "score:");
  _score_label = new label(this, dim+point(75,0), "");

  dim += offset;
  new label(this, dim, "level:");
  _level_label = new label(this, dim+point(75,0), "");

  dim += offset;
  new label(this, dim, "lines:");
  _lines_label = new label(this, dim+point(75,0), "");

  _preview_canvas = preview_canvas;
}

std::string int_to_string(int n) {
	std::stringstream val;
	val << n;
	return val.str();
	}

void hud::update_labels(int score, int level, int lines) {
  _score_label->set_text(int_to_string(score));
  _level_label->set_text(int_to_string(level));
  _lines_label->set_text(int_to_string(lines));
}

void hud::on_draw() {
  frame::on_draw();
  if (_preview_canvas) {
    rect r = _preview_canvas->get_clip_rect();
	rect dest_r = r+point(150,10);
    get_canvas()->blit(dest_r, *_preview_canvas, r);
  }
}
