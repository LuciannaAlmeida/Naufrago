#include "colisoes.h"

int distancia_quadratica_entre_centros(naufrago elemento_A, naufrago elemento_B){
  int distancia_abcissa = elemento_A.coordenada_x - elemento_B.coordenada_x;
  int distancia_ordenada = elemento_A.coordenada_y - elemento_B.coordenada_y;
  
  return (distancia_abcissa*distancia_abcissa) + (distancia_ordenada*distancia_ordenada);
}

int distancia_quadratica_minima_entre_centros(int raio1, int raio2){
  int distancia_minima = raio1+raio2;
  return distancia_minima*distancia_minima; 
}

/* Inverte direcao que esta sendo seguida */
int inverte_direcao(int direcao_antiga){
  switch(direcao_antiga){
  case 0:
	return 7;
  case 1:
	return 6;
  case 2:
	return 5;
  case 3:
	return 4;
  case 4:
	return 3;
  case 5:
	return 2;
  case 6:
	return 1;		
  case 7:
	return 0;
  }
  return direcao_antiga;
}

/* Troca vetor velocidade do passageiro A com o B */
void troca_vetor_velocidade_dos_passageiros(naufrago *passageiros, int id_A, int id_B){
  int direcao_aux;
  int velocidade_aux;
  velocidade_aux = passageiros[id_A].modulo_velocidade;
  direcao_aux = passageiros[id_A].direcao;

  passageiros[id_A].modulo_velocidade = passageiros[id_B].modulo_velocidade;
  passageiros[id_A].direcao = passageiros[id_B].direcao;

  passageiros[id_B].modulo_velocidade = velocidade_aux;
  passageiros[id_B].direcao = direcao_aux;
}

/* Inverte a direcao do vetor velocidade de um dos elementos depois troca os vetores dos passageiros */
void troca_vetor_velocidade_de_passageiros_com_mesma_direcao(naufrago *passageiros, int id_A, int id_B){
  if(passageiros[id_A].modulo_velocidade < passageiros[id_B].modulo_velocidade)
	passageiros[id_A].direcao = inverte_direcao(passageiros[id_A].direcao);
  else
	passageiros[id_B].direcao = inverte_direcao(passageiros[id_B].direcao);
  /* Funcao que troca o vetor velocidade dos elementos */
  troca_vetor_velocidade_dos_passageiros(passageiros, id_A, id_B);
}


/* Verifica se 2 passageiros colidiram */
int colidiram(naufrago passageiro_A, naufrago passageiro_B){
  /* if(passageiro_A.coordenada_x == passageiro_B.coordenada_x && */
  /* 	 passageiro_A.coordenada_y == passageiro_B.coordenada_y  ) */
  int raio = RAIO_PASSAGEIRO;
  int distancia = distancia_quadratica_entre_centros(passageiro_A, passageiro_B);
  int distancia_minima = distancia_quadratica_minima_entre_centros(raio, raio);

  if (distancia <= distancia_minima){
    printf("distancia entre centros - %d         distancia minima - %d\n", distancia, distancia_minima);
    printf("passageiro_A.coordenada_x %d passageiro_A.coordenada_y %d \n" 
	   "passageiro_B.coordenada_x %d passageiro_B.coordenada_y %d \n"
	   "passageiro_A.direcao %d  passageiro_B.direcao %d\n"
	   "passageiro_A.id %d passageiro_B.id %d\n\n",
	   passageiro_A.coordenada_x , passageiro_A.coordenada_y ,   
	   passageiro_B.coordenada_x , passageiro_B.coordenada_y ,
	   passageiro_A.direcao,  passageiro_B.direcao,
	   passageiro_A.id, passageiro_B.id);
    
    return 1;
  }
  return 0;
}


/* Inverte a direcao dos passageiros que colidiram */
void trata_colisao_entre_passageiros(naufrago *passageiros, int qtd_passageiros){
  int i, j, numero_colisoes, passageiro_colidido = 0;
  
  for(i = 0; i < qtd_passageiros; i++){
    
    /* Verifica com quantos passageiros o passageiro i colidiu */
    for(j = 0, numero_colisoes = 0; j < qtd_passageiros; j++)
      if(i != j && colidiram(passageiros[i], passageiros[j])){
	passageiro_colidido = j;
	numero_colisoes++;
      }
    
    if(numero_colisoes >= 1){
      /* Verifica se o passageiro colidiu com apenas um outro passageiro */
      if(numero_colisoes == 1 && i < j){
	if(passageiros[i].direcao == passageiros[j].direcao)
	  troca_vetor_velocidade_de_passageiros_com_mesma_direcao(passageiros, i, j);
	else
	  troca_vetor_velocidade_dos_passageiros(passageiros, i, passageiro_colidido);
      }
      
      /* Inverte a direcao do passageiro no caso de ter ocorrido alguma colisao (numero_colisoes > 1) */
      else if(numero_colisoes > 1)
	passageiros[i].direcao = inverte_direcao(passageiros[i].direcao);
      
      /* Marca no passageiro que ocorreu colisao */
      passageiros[i].houve_colisao = 1;
    }
  }
}


int distancia_quadratica_entre_coral_e_naufrago(naufrago passageiro, posicao_do_coral coral){
  int distancia_abcissa = passageiro.coordenada_x - coral.x;
  int distancia_ordenada = passageiro.coordenada_y - coral.y;
  
  return (distancia_abcissa*distancia_abcissa) + (distancia_ordenada*distancia_ordenada);

}

int colidiu_com_coral(naufrago passageiro, posicao_do_coral coral){
  int distancia = distancia_quadratica_entre_coral_e_naufrago(passageiro, coral);
  int distancia_minima = distancia_quadratica_minima_entre_centros(RAIO_PASSAGEIRO, RAIO_CORAL);
  
  if(distancia < distancia_minima)
    return 1;
  return 0;
}

void trata_colisao_com_coral(naufrago* passageiros, int qtd_passageiros){
  int i, j;
  
  for(i = 0; i < qtd_passageiros; i++){
    for(j = 0; j< 3; j++){
      if(colidiu_com_coral(passageiros[i], vetor_posicao_dos_corais[j]))
	 passageiros[i].direcao = inverte_direcao(passageiros[i].direcao);
	 }
    }
  }


