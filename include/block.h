#ifndef KAOSTETRIS_BLOCK
#define KAOSTETRIS_BLOCK

#include <projectg.h>

class block : public rect {
public:
  block(canvas* c, int width, int height) : rect(0,0,width,height) {_block_canvas = c;}
  block(canvas* c) : rect(0,0,c->get_w(), c->get_h()) {_block_canvas = c;}

   /** Render the block to a canvas.
   * @param dest The destination canvas. */
  void draw(canvas* dest, point offset=point(0,0));

  /** Get the position of the block. */
  point get_pos() {return point(r.x, r.y);}

  /** Set the position of the block. */
  void set_pos(point pos) {r.x = pos.get_x(); r.y=pos.get_y();}

  /** Get a pointer to the block's canvas. */
  canvas* get_canvas() {return _block_canvas;}

  /** Move the block up the length of it's height. */
  void move_up() {r.y -= r.h;}
  /** Move the block down the length of it's height. */
  void move_down() {r.y += r.h;}
  /** Move the block right the length of it's width. */
  void move_right() {r.x += r.w;}
  /** Move the block left the length of it's width. */
  void move_left() {r.x -= r.w;}
  
  /** Draws a block picture to a canvas.
   * @param col The color of the block. It's frame will be a darker shade of this color. 
   * @return A pointer to the canvas. */
  static canvas* create_block(color col, int width, int height);

private:
  /** Canvas of the block. */
  canvas* _block_canvas;
  /** Shade offset for the frame. */
  static const int FRAME_SHADE_OFFSET = 30;
};

#endif
