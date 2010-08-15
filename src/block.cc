
#include "world.h"

void block::draw(canvas* dest, point offset) {
  if (!dest || !_block_canvas) {
    std::cout << "block::render: got NULL\n";
    return;
  }
  rect dst = rect(r) + offset;
  rect clip = _block_canvas->get_clip_rect();
  dest->blit(dst, *_block_canvas, clip);
}

canvas* block::create_block(color col, int width, int height) {
  canvas *c = canvas::create_rgb_compatible(SDL_ANYFORMAT, width, height);
  if (!c) {
    std::cout << "block::create_block: failed to create canvas!";
    exit(1);
  }

  /* draw a frame (1px in width) */
  rect clip = c->get_clip_rect();
  color bg(200,210, 230);
  c->fill_rect(clip, bg); 
  clip.shrink(1,1);
  c->fill_rect(clip, col);
  
  return c;
}
