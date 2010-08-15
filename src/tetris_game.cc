
#include "tetris_game.h"

tetris_game::tetris_game() : sdl_app() {
  ui = NULL;
  game = NULL;
  game_canvas = NULL;
  preview_figure_canvas = NULL;
  paused = true;
  fall_time = tetris_game::INIT_FALL_TIME;
  fall_ticks = 0;
  freeze = false;
  _lines = _score = _level = 0;
}


tetris_game::~tetris_game() {
  app_clock.stop();
  figure_factory::deinit_figures();
  if (game)                  delete game;
  if (ui)                    delete ui;
  if (_hud)                   delete _hud;
  if (game_canvas)           delete game_canvas;
  if (preview_figure_canvas) delete preview_figure_canvas;
}


bool tetris_game::on_init(int argc, char **argv) {
  /* sdl */
  if (init_sdl("kAos tetris", 640, 660)==false) {
    std::cout << argv[0] << "\n";
    exit(1);
  }

  /* load the figure graphics. */
  figure_factory::init_figures();

  /* init the canvas to draw the game on. */
  game_canvas = canvas::create_rgb_compatible(SDL_ANYFORMAT, 320, 640);

  /* where the 'next pice' will be shown. */
  preview_figure_canvas = canvas::create_rgb_compatible(SDL_ANYFORMAT, 128,128);
    
  /* the main menu */
  ui = new main_menu(this, window_width, window_height);
  ui->init();
  ui->set_hidden(false);

  /* init HUD */
  _hud = new hud(NULL, point(340, 10), preview_figure_canvas);

  /* fps timer */
  app_clock.set_interval(2); // 60 fps
  app_clock.start();

  return true;
}


void tetris_game::update_game() {
  if (!paused && freeze==false && game != NULL) {
    if (game->update() == false) { /* game over man */
      paused = true;
      freeze = true;
      paused = true;
      
    } else {
        if (!freeze) {
        int rows = game->get_recently_cleared_rows();
        _lines += rows;
        _score += rows * rows * 100;
        update_level();
        _hud->update_labels(_score, _level, _lines);
      }
    }
  }
}


void tetris_game::decrease_fall_speed() {
  fall_time += 1;
}


void tetris_game::increase_fall_speed() {
  fall_time -= 1;
  if (fall_time < 0) fall_time = 0;
}


void tetris_game::update_preview() {
  if (!preview_figure_canvas) return;
  rect fill_rect = preview_figure_canvas->get_clip_rect();
  preview_figure_canvas->fill_rect(fill_rect, control::default_bg_color);
  if (game && game->get_next_figure()) {
    game->get_next_figure()->draw(preview_figure_canvas);
  }
}

void tetris_game::update_level() {
  if ((double(_score) / (double)_old_score) >= 2.0) {
    _old_score = _score;
    _level++;
    increase_fall_speed();
  }
}




void tetris_game::update() {
  if (fall_ticks > fall_time) {
    update_game();
    fall_ticks = 0;
  } else {
    fall_ticks ++;
  }

  if (game && game_canvas && _hud && !paused) {
    rect clip = game_canvas->get_clip_rect();
    clip.shrink(-1,-1);

	rect bg_rect = scr->get_clip_rect();
	color bg_color(60,70,80);
	color frame_color(255,255,255);
    scr->fill_rect(bg_rect, bg_color);
	
	rect frame_r = clip + point(10,10);
	scr->fill_rect(frame_r, frame_color);

    game->draw(game_canvas);
	rect game_dest = game_canvas->get_clip_rect() + point(10,10);
	rect game_clip = game_canvas->get_clip_rect();
    scr->blit(game_dest, *game_canvas, game_clip);

    update_preview();
    _hud->set_hidden(false);
    _hud->draw();
	rect hud_dest = _hud->get_dimensions();
	rect hud_clip = _hud->get_canvas()->get_clip_rect();
    scr->blit(hud_dest, *_hud->get_canvas(), hud_clip);
    //scr->blit(preview_figure_canvas->get_clip_rect()+point(360, 10), *preview_figure_canvas, preview_figure_canvas->get_clip_rect());
  }

  if (ui!=NULL && ui->get_hidden() == false) {
	rect ui_clip = ui->get_canvas()->get_clip_rect();
	rect ui_dimen = ui->get_dimensions();
	ui->draw();
    scr->blit(ui_dimen, *ui->get_canvas(), ui_clip);
  }
  scr->flip(); 
}


bool tetris_game::filter_event(SDL_Event* e) {
  if (ui->get_hidden() == false) return ui->filter_event(e);
  else return false;
}


void tetris_game::on_key_down(SDLKey k, SDLMod m, Uint16 unicode) {
  if (freeze) {
    close_game();
    paused = true;
    ui->set_hidden(false);
    return;
  }
  if (k == SDLK_ESCAPE || k == SDLK_q) {
    paused = true;
    ui->set_hidden(false);
  } 
  else if (k == SDLK_PAUSE || k == SDLK_p) paused = !paused;
  else if (paused==false && freeze==false) { /* game keys */
    if (!game) return;
    if      (k == SDLK_RIGHT) game->move_right();
    else if (k == SDLK_LEFT)  game->move_left();
    else if (k == SDLK_UP)    game->rotate_right();
    else if (k == SDLK_DOWN)  game->rotate_left();
    else if (k == SDLK_SPACE) game->drop_hard();
    /* else if (k == SDLK_PLUS  || k == SDLK_2) increase_fall_speed(); */
    /* else if (k == SDLK_MINUS || k == SDLK_1) decrease_fall_speed(); */
  }
}


void tetris_game::new_game() {
  if (game) delete game;
  game = new world(10, 20);
  fall_time = tetris_game::INIT_FALL_TIME;
  fall_ticks = 0;
  _score = 0;
  _level = 0;
  _lines = 0;
  freeze = false;
  _old_score = 250;
  ui->set_hidden(true);
  paused = false;
}

void tetris_game::close_game() {
  delete game;
  game = NULL;
  ui->set_hidden(false);
}


bool tetris_game::on_message(msgid msg, void *param1, void *param2, void *param3, void *param4) {
  if (msg == main_menu::msg_resume_game) {
    if (game) {
      ui->set_hidden(true);
      paused = false;
    }
  } else if (msg == main_menu::msg_new_game) {
    new_game();
  } else if (msg == main_menu::msg_exit_game) {
    on_message(msgid_exit_application,0,0,0,0);
    return true;
  }
  return application::on_message(msg, param1, param2, param3, param4);
}


int main(int argc, char *argv[]) {
  tetris_game g;
  return tetris_game::exec(argc, argv);
}
