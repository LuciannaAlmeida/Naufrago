/*
  EP4 - Laboratório de Programação     09/06/2010
  
  Integrantes:
  Lucianna Thomaz Almeida      5893802  
  Lucas Rodrigues Colucci      6920251
  Cindy de Albuquerque         4954631
*/

#include "visualizacao_grafica.h"

/* Opção para inicializar a animação com valores padrão. */
void inicializa_janela_padrao(){
  incicializa_janela(RESOLUCAO_VERTICAL, RESOLUCAO_HORIZONTAL);
}

/* Opção para inicializar a animação com valores definidos pelo usuário. */
/* void incicializa_animacao(int bits_cores_grafico, int resolucao_horizontal, int resolucao_vertical){ */
void incicializa_janela(int resolucao_horizontal, int resolucao_vertical){
  int sucesso;
  int bits_cores_grafico;
  
  /*Inicializa o Allegro, o teclado, o mouse e os temporizadores*/
  allegro_init();
  install_keyboard();
  set_keyboard_rate(DELAY, REPEAT);
  install_mouse();
  install_timer();
  
  
  /* guarda a quantidade de cores que a maquina do usuario suporta */
  bits_cores_grafico = desktop_color_depth();
  
  /* se retornou zero, usar 32 bits de cor */
  if(bits_cores_grafico == 0) bits_cores_grafico = 32;
  
  /*determina o número de bits de cores a ser usado pelos graficos*/
  set_color_depth(bits_cores_grafico);
  
  
  /*inicialização do modo grafico*/
  sucesso = set_gfx_mode(GFX_AUTODETECT, resolucao_vertical, resolucao_horizontal, VIRTUAL_VERTICAL, VIRTUAL_HORIZONTAL);
  if ( sucesso != 0 ){
    printf ("Erro ao inicializar o modo gráfico. Encerrando o programa.\n");
    exit (-1);
  }
  
  /* cria um titulo para a janela do jogo */
  set_window_title("Naufrago"); 
}

void desenha_passageiro(BITMAP *destino, int y, int x){
  /*void circlefill(BITMAP *bmp, int x, int y, int  radius, int color); */
  /*int makecol(int  r, int g, int b); */
  circlefill(destino, x, y, RAIO_PASSAGEIRO, makecol(0, 255, 0)); /*green circle*/
}

void desenha_colisao(BITMAP *destino, int y, int x){
  /*void circlefill(BITMAP *bmp, int x, int y, int  radius, int color); */
  /*int makecol(int  r, int g, int b); */
  circlefill(destino, x, y, RAIO_PASSAGEIRO, makecol(255, 0, 0)); /*red circle*/
}

void desenha_coral(BITMAP *destino, int y, int x){
  /*void circlefill(BITMAP *bmp, int x, int y, int  radius, int color); */
  /*int makecol(int r, int g, int b); */
  circlefill(destino, x, y, RAIO_CORAL, makecol(255, 100, 50)); /* circle*/
}

void desenha_asimov(BITMAP *destino, int y1, int x1, int y2, int x2){
  /*void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color); */
  /*int makecol(int r, int g, int b); */
  /* rectfill(destino, x1, y1, x2, y2, makecol(0, 0, 0)); */ /* retangulo */
  BITMAP *asimov = load_bitmap("navio.bmp", NULL);
  draw_sprite(destino, asimov, x1, y1);
}

void desenha_botes(BITMAP *destino, Bote botes[]){
  /*void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color); */
  /*int makecol(int r, int g, int b); */
  int x, y;
  
  if(!bote_afundou(0)){
    /* desenha bote 0 */
    x = botes[0].coordenada_x;
    y = botes[0].coordenada_y;
    triangle(destino, (x - ALTURA_BOTE/3), y, (x + ALTURA_BOTE/3), y, x, (y - ALTURA_BOTE), makecol(100, 15, 20));
  }
  if(!bote_afundou(1)){
    /* desenha bote 1 */
    x = botes[1].coordenada_x;
    y = botes[1].coordenada_y;
    triangle(destino, (x - ALTURA_BOTE/3), y, (x + ALTURA_BOTE/3), y, x, (y - ALTURA_BOTE), makecol(20, 80, 40));
  }
}
