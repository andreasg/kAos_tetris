
#include "figure.h"

/** Default width of a block. */
int figure::BLOCK_WIDTH = 32;
/** Default height of a block. */
int figure::BLOCK_HEIGHT = 32;

/** Figure colors taken from Wikipedia. */
color figure::T_COLOR = color(170, 0, 255);
color figure::S_COLOR = color(0,255,0);
color figure::Z_COLOR = color(255,0,0);
color figure::L_COLOR = color(255, 165, 0);
color figure::O_COLOR = color(255,255,0);
color figure::J_COLOR = color(0,0,255);
color figure::I_COLOR = color(0,255,255);


figure::figure(point pos, canvas* pic, int rotation_states) {
  _block = new block(pic, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
  current_rotation = 0;
  this->pos = pos;
  this->rotation_states = rotation_states;
}


figure::~figure() {
  if (_block) delete _block;
}


void figure::rotate(direction dir) {
  // update the current rotation state
  if (dir == right) {
    if (current_rotation + 1 >= rotation_states) {
      current_rotation = 0;
    } else {
      current_rotation++;
    }
  } else if (dir == left) {
    if (current_rotation - 1 < 0) {
      current_rotation = rotation_states-1;
    } else {
      current_rotation--;
    }
  }
  
  /* move the pices to according to state */
  if (current_rotation == 0) pos_one();
  else if (current_rotation == 1) pos_two();
  else if (current_rotation == 2) pos_three();
  else if (current_rotation == 3) pos_four();
}


void figure::draw(canvas* dest) {
  if (!dest) return;

  for (int i=0; i<4; i++) {
    _block->draw(dest, pos+poss[i]);
  }
}


void figure::move(direction dir) {
  if (dir == left)
    pos += point(-figure::BLOCK_WIDTH, 0);
  else if (dir == right)
    pos += point(figure::BLOCK_WIDTH, 0);
}


void T::pos_one() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(0*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
}

void T::pos_two() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void T::pos_three() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[1] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[3] = point(3*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
}

void T::pos_four() {
  poss[0] = point(2*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void Z::pos_one() {
  poss[0] = point(0*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
}

void Z::pos_two() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(0*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(0*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void S::pos_one() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(2*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[2] = point(0*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
}

void S::pos_two() {
  poss[0] = point(0*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(0*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void O::pos_one() {
  poss[0] = point(0*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(0*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[3] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
}

void I::pos_one() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[3] = point(1*figure::BLOCK_WIDTH, 3*figure::BLOCK_HEIGHT);
}

void I::pos_two() {
  poss[0] = point(0*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[3] = point(3*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void J::pos_one() {
  poss[0] = point(2*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[3] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void J::pos_two() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[3] = point(3*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void J::pos_three() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(2*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void J::pos_four() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[1] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(3*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(3*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void L::pos_one() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[2] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[3] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void L::pos_two() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(3*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
}

void L::pos_three() {
  poss[0] = point(1*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[1] = point(2*figure::BLOCK_WIDTH, 0*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
  poss[3] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
}

void L::pos_four() {
  poss[0] = point(0*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[1] = point(1*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[2] = point(2*figure::BLOCK_WIDTH, 2*figure::BLOCK_HEIGHT);
  poss[3] = point(2*figure::BLOCK_WIDTH, 1*figure::BLOCK_HEIGHT);
}
