
#include "world.h"

world::world(int w, int h) {
  _width = w;
  _height = h;
  _current_figure = NULL;
  _next_figure = figure_factory::random_figure();

  /** Init the block array. */
  _blocks = new block**[_height];
  for (int i =0; i<_height; i++) {
    _blocks[i] = new block*[_width];
  }
  for (int i=0; i<_height; i++) {
    for (int k=0; k<_width; k++) {
      _blocks[i][k] = NULL;
    }
  }
}


world::~world() {
  if (_current_figure) {
    delete _current_figure;
    _current_figure = NULL;
  }

  if (_next_figure) {
    delete _next_figure;
    _next_figure = NULL;
  }

  for (int i = int(0); i<_height; ++i) {
    for (int k = int(0); k<_width; ++k) {
      if (_blocks[i][k] != NULL) delete _blocks[i][k];
    }
    delete [] _blocks[i];
  }
  delete [] _blocks;
}


void world::collapse_column(const int column, const int start_row) {
  for (int row = start_row; row > 0; row--) {
    /* move the above block down. */
    _blocks[row][column] = _blocks[row-1][column];
    if (_blocks[row][column] != NULL) {
      _blocks[row][column]->move_down();
    }
  }

  /* Since the column has collapsed, topmost element must be NULL. */
  if (_blocks[0][column]) delete _blocks[0][column];
  _blocks[0][column] = NULL;
}

void world::clear_full_rows() {
  cleared_rows = 0;
  for (int row = int(0); row <_height; ++row) {
    bool full = true;
    for (int col = int(0); col<_width; ++col) {
      full = full && (_blocks[row][col] != NULL);
    }
    if (full) {
      cleared_rows ++;
      for (int col=0; col<_width; col++) {
        if (_blocks[row][col] != NULL) {
          delete _blocks[row][col];
          _blocks[row][col] = NULL;
        }
        collapse_column(col, row);
      }
    }
  }
}

bool world::next_figure() {
  if (_current_figure) delete _current_figure;

  _current_figure = _next_figure;
  _current_figure->set_pos(point(_width/2*figure::BLOCK_WIDTH, 0));
  _next_figure = figure_factory::random_figure();

  if (colliding(_current_figure)) {
    delete _current_figure;
    _current_figure = NULL;
    return false;
  }
  return true;
}

bool world::update() {
  if (_current_figure == NULL) { /* no active figure */
    clear_full_rows();
    return next_figure();
  } else { /* we have a falling figure */
    _current_figure->fall();
    if (colliding(_current_figure)) {
      _current_figure->unfall();
      lock_current_figure();
    }
  }
  return true;
}


void world::lock_current_figure() {
  if (!_current_figure) return;

  point* blocks = _current_figure->get_blocks();
  for (int i=0; i<figure::BLOCKS; i++) {
    point pos = blocks[i];
	pos += _current_figure->get_pos();
    /* get the gridcell we are in */
    int x = pos.get_x() / figure::BLOCK_WIDTH;
    int y = pos.get_y() / figure::BLOCK_HEIGHT;
    if (_blocks[y][x] == NULL) {
      _blocks[y][x] = new block(_current_figure->get_block()->get_canvas());
      _blocks[y][x]->set_pos(pos); /* set the block to world coords. */
    }
  }
  _current_figure = NULL;
}


bool world::colliding(figure* fig) {
  if (!fig) return false;

  point* blocks = _current_figure->get_blocks();
  for (int i=0; i<figure::BLOCKS; i++) {
    /* make the blocks local coords into world coords */
    point pos = blocks[i];
	pos += _current_figure->get_pos();

    /* get the gridcell we are in */
    int x = pos.get_x() / figure::BLOCK_WIDTH;
    int y = pos.get_y() / figure::BLOCK_HEIGHT;

    /* check if hitting the ground or a blocked cell */
    if (((y*figure::BLOCK_HEIGHT)+figure::BLOCK_HEIGHT) > _height*figure::BLOCK_HEIGHT || _blocks[y][x] != NULL) {
      return true;
    }

    if (x < 0 || x >= _width) return true;
  }
  return false;
}


void world::draw(canvas* dest) {
  if (!dest) return;

  /* draw background */
  rect background = rect(0,0, _width*figure::BLOCK_WIDTH, _height*figure::BLOCK_HEIGHT);
  dest->fill_rect(background, control::default_bg_color);

  /* draw the blocks laying still. */
  for (int row=0; row<_height; row++) {
    for (int col=0; col<_width; col++) {
      if (_blocks[row][col] != NULL) {
        _blocks[row][col]->draw(dest);
      }
    }
  }

  /* draw current figure. */
  if (_current_figure) {
    _current_figure->draw(dest);
  }
}


void world::move_right() {
  if (!_current_figure) return;
  _current_figure->move(right);
  if (colliding(_current_figure)) move_left();
}

void world::move_left() {
  if (!_current_figure) return;
  _current_figure->move(left);
  if (colliding(_current_figure)) move_right();
}

void world::rotate_right() {
  if (!_current_figure) return;
  _current_figure->rotate(right);
  if (colliding(_current_figure)) rotate_left();
}

void world::rotate_left() {
  if (!_current_figure) return;
  _current_figure->rotate(left);
  if (colliding(_current_figure)) rotate_right();
}

void world::drop_hard() {
  while (_current_figure) update();
}

int world::get_recently_cleared_rows() {
  int out = cleared_rows;
  cleared_rows=0;
  return out;
}
