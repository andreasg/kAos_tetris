#ifndef KAOSTETRIS_FIGURE
#define KAOSTETRIS_FIGURE

/* used for random gen. */
#include <cstdlib>
#include <ctime>

#include "block.h"

enum direction {left, right};

/** Abstract figure. */
class figure {
public:
  /** Default constructor.
   * @param pos Initial position.
   * @param col Color for the figure.
   * @param rotation_states How many different rotation-states the figure will have. */
  figure(point pos, canvas* pic, int rotation_states);
  /** Destructor. */
  virtual ~figure();

  /** Rotate the figure.
   * @param dir Can be left or right. */
  virtual void rotate(direction dir);
  /** Move the figure in a direction the distance of a default block width. */
  void move(direction dir);
  /** Make the pice fall the distance of a block-height. */
  void fall() {pos += point(0, figure::BLOCK_HEIGHT);}
  /** Move the figure upwards the length of a default block height. */
  void unfall() {pos += point(0, -figure::BLOCK_HEIGHT);}

  /** Draws the figure to a canvas.
   * @param dest The canvas to draw to. */
  void draw(canvas* dest);

  /** Returns a array of block-pointers.
   * @return Array of blocks in figure, length of array is BLOCKS
   * @see BLOCKS */
  point* get_blocks() {return poss;}
  block* get_block() {return _block;}

  /** Get the position of the figure. */
  point get_pos() {return pos;}
  /** Set the position of the figure. */
  void set_pos(point pos) {this->pos = pos;}

  /** Number of blocks in a figure. In tetris this is always four. */
  static const int BLOCKS = 4;
  /** Default width of a block. */
  static int BLOCK_WIDTH;
  /** Default height of a block. */
  static int BLOCK_HEIGHT;
  /** Color of the different figures. */
  static color T_COLOR, S_COLOR, Z_COLOR, L_COLOR, O_COLOR, J_COLOR, I_COLOR;

protected:
  /** Pointer to the block. */
  block* _block;
  /** Position of the blocks in figure-local-coord. */
  point poss[4];

  /** Rotation state.
   * Overload this to configure how the figure will appear. */
  virtual void pos_one() {}
  /** @see pos_one() */
  virtual void pos_two() {}
  /** @see pos_one() */
  virtual void pos_three() {}
  /** @see pos_one() */
  virtual void pos_four() {}

private:
  /** How many rotation states the figure has. */
  int rotation_states;
  /** Current rotation state. */
  int current_rotation;
  /** Position of the figure. */
  point pos;
};


class T : public figure {
  /* Rotation states:
    #O## #O## #### ##O#
    OOO# #OO# #OOO #OO#
    #### #O## ##O# ##O#
  */
public:
  T(canvas* b) : figure(point(0,0), b,4) {pos_one();}
  ~T(){}

private:
  void pos_one();
  void pos_two();
  void pos_three();
  void pos_four();
};


class Z : public figure {
  /* Rotation states:
    OO## #O##
    #OO# OO##
    #### O###
  */
public:
  Z(canvas* b) : figure(point(0,0), b,2) {pos_one();}
  ~Z(){}
private:
  void pos_one();
  void pos_two();
};


class S : public figure {
  /* Rotation states:
    #OO# O###
    OO## OO##
    #### #O##
  */
public:
  S(canvas* b) : figure(point(0,0), b, 2) {pos_one();}
  ~S(){}
private:
  void pos_one();
  void pos_two();
};

class O : public figure {
  /* Rotation states.
     #OO#
     #OO#
     ####
  */
public:
  O(canvas* b) : figure(point(0,0),b,1) {pos_one();}
  ~O(){};
private:
  void pos_one();
};

class I : public figure {
  /* Rotation states.
    #O## ####
    #O## ####
    #O## OOOO
    #O## ####
  */
public:
  I(canvas* b) : figure(point(0,0),b,2) {pos_one();}
  ~I(){};
private:
  void pos_one();
  void pos_two();
};

class J : public figure {
  /* Rotation states:
    ##O# #### #OO# ####
    ##O# #O## #O## #OOO
    #OO# #OOO #O## ###O
  */
public:
  J(canvas* b) : figure(point(0,0), b,4) {pos_one();}
  ~J(){};
private:
  void pos_one();
  void pos_two();
  void pos_three();
  void pos_four();
};

class L : public figure {
  /* Rotation states.
    #O## #### #OO# ####
    #O## #OOO ##O# ##O#
    #OO# #O## ##O# OOO#
  */
public:
  L(canvas* b) : figure(point(0,0),b,4) {pos_one();}
  ~L() {};
private:
  void pos_one();
  void pos_two();
  void pos_three();
  void pos_four();
};
#endif
