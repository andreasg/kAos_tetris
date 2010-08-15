#include "figure_factory.h"

bool figure_factory::rand_init = false;

canvas* figure_factory::t_block = NULL;
canvas* figure_factory::s_block = NULL;
canvas* figure_factory::z_block = NULL;
canvas* figure_factory::l_block = NULL;
canvas* figure_factory::o_block = NULL;
canvas* figure_factory::j_block = NULL;
canvas* figure_factory::i_block = NULL;


void figure_factory::init_figures() {
  figure_factory::t_block = canvas::load_bmp_compatible("data/purple.bmp");   //block::create_block(figure::T_COLOR, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
  figure_factory::s_block = canvas::load_bmp_compatible("data/red.bmp");    //block::create_block(figure::S_COLOR, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
  figure_factory::z_block = canvas::load_bmp_compatible("data/green.bmp");//block::create_block(figure::Z_COLOR, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
  figure_factory::l_block = canvas::load_bmp_compatible("data/dark_blue.bmp");//block::create_block(figure::L_COLOR, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
  figure_factory::o_block = canvas::load_bmp_compatible("data/yellow.bmp");   //block::create_block(figure::O_COLOR, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
  figure_factory::j_block = canvas::load_bmp_compatible("data/orange.bmp");   //block::create_block(figure::J_COLOR, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
  figure_factory::i_block = canvas::load_bmp_compatible("data/blue.bmp");     //block::create_block(figure::I_COLOR, figure::BLOCK_WIDTH, figure::BLOCK_HEIGHT);
}


void figure_factory::deinit_figures() {
  if(figure_factory::t_block) delete figure_factory::t_block;
  if(figure_factory::s_block) delete figure_factory::s_block;
  if(figure_factory::z_block) delete figure_factory::z_block;
  if(figure_factory::l_block) delete figure_factory::l_block;
  if(figure_factory::o_block) delete figure_factory::o_block;
  if(figure_factory::j_block) delete figure_factory::j_block;
  if(figure_factory::i_block) delete figure_factory::i_block;
}

figure* figure_factory::random_figure() {
  if (!figure_factory::rand_init) {
    std::srand((unsigned)time(0));
    figure_factory::rand_init = true;
  }

  int random = std::rand() % 7;
  if (random == 0) return figure_factory::create_i_figure();
  else if (random == 1) return figure_factory::create_z_figure();
  else if (random == 2) return figure_factory::create_s_figure();
  else if (random == 3) return figure_factory::create_l_figure();
  else if (random == 4) return figure_factory::create_j_figure();
  else if (random == 5) return figure_factory::create_o_figure();
  else if (random == 6)return  figure_factory::create_t_figure();
  return NULL;
}
