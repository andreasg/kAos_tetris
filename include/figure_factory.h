#ifndef KAOSTETRIS_FIGUREFACTORY
#define KAOSTETRIS_FIGUREFACTORY

#include <projectg.h>
#include "figure.h"

class figure_factory {
public:
  static void init_figures();
  static void deinit_figures();
  static figure* create_t_figure() {return new T(figure_factory::t_block);}
  static figure* create_o_figure() {return new O(figure_factory::o_block);}
  static figure* create_i_figure() {return new I(figure_factory::i_block);}
  static figure* create_j_figure() {return new J(figure_factory::j_block);}
  static figure* create_l_figure() {return new L(figure_factory::l_block);}
  static figure* create_z_figure() {return new Z(figure_factory::z_block);}
  static figure* create_s_figure() {return new S(figure_factory::s_block);}

  /** Provides a random figure. */
  static figure* random_figure();

private:
  static canvas* t_block;
  static canvas* s_block;
  static canvas* z_block;
  static canvas* l_block;
  static canvas* o_block;
  static canvas* j_block;
  static canvas* i_block;

  /** Flag to check if the random number generator has been initialized. */
  static bool rand_init;
};

#endif
