#ifndef KAOSTETRIS_WORLD
#define KAOSTETRIS_WORLD

#include <list>

#include "figure.h"
#include "figure_factory.h"

class world {
public:
  /** Default constructor.
    * @param w Width of the world in blocks.
    * @param h Height of the world in blocks.
    */
  world(int w, int h);
  virtual ~world();

  /** Updates the world. Checks for complete rows, and 
   *  moves the current figure downward.
   * @return false if game over. */
  bool update();

  /** Blit the world to a canvas.
   * @param dest Destination canvas. */
  void draw(canvas* dest);

  /** Moves the figure one square to the right. */
  void move_right();
  /** Moves the figure one square to the left. */
  void move_left();
  /** Rotates the figure right. */
  void rotate_right();
  /** Rotates the figure left. */
  void rotate_left();
  /** Move pice as far down as possible. */
  void drop_hard();

  /** Get a pointer to the next figure. */
  figure* get_next_figure() {return _next_figure;}

  int get_recently_cleared_rows();

private:

  /** Locks the current figure to the grid. */
  void lock_current_figure();

  /** Collapse the column from start_row one block. */
  void collapse_column(const int column, const int start_row);

  /** Removes all full rows, and collapses the columns. */
  void clear_full_rows();

  /** Sets current figure to the next figure and generates a new next figure.
   * @return true if able to create the new figure, false if there were no 
   *         game-space to do so (game over). */
  bool next_figure();

  /** Return true of the fig is colliding with anything in the world. */
  bool colliding(figure* fig);

  /** width and height of the world in blocks. */
  int _width, _height;

  int cleared_rows;

  /** The figure currently falling. */
  figure* _current_figure;
  figure* _next_figure;

  /** All the blocks that land in the world. */
  block*** _blocks;
};

#endif
