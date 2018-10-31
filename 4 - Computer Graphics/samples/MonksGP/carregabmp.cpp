/* Procedimento de carregar textura de um arquivo BMP
 *
 * Por Rodrigo Moreira Silveira
 */

#define GL_CLAMP_TO_EDGE 0x812F
#include "carregabmp.h"


/*! \brief Função que carrega BMP
 *
 * Esta função só carrega BMP com bpp de 24 e com 1 plano.
 *
 * Baseado nas informações encontradas em:
 * http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt
 *
 * \param nomearq String com o nome do arquivo BMP
 * \param imagem Ponteiro para a estrutura que será alocada alocada
 * \return 1 se não teve problemas e 0 se ocorreu algum erro
 */
int CarregaBMP(const char *nomearq, Imagem *imagem) {
    FILE *arq;
    unsigned long i;
    char temp;

    // Tamanho da imagem em bytes
    unsigned long tam;
    // Numero de planos no BMP, tem que ser 1
    unsigned short int planos;
    // quantos bits por pixel, tem que ser 24
    unsigned short int bpp;

    if ((arq = fopen(nomearq, "rb"))==NULL)
    {
      cerr << "Arquivo " << nomearq << " não encontrado" << endl;
      return 0;
    }

    // vai para onde está a informação de altura/largura no cabeçalho do arquivo
    fseek(arq, 18, SEEK_CUR);

    if ((i = fread(&imagem->tamX, 4, 1, arq)) != 1) {
      cerr << "Erro no arquivo " << nomearq << ", largura inválida." << endl;
      return 0;
    }

    if ((i = fread(&imagem->tamY, 4, 1, arq)) != 1) {
      cerr << "Erro no arquivo " << nomearq << ", altura inválida." << endl;
      return 0;
    }

    // Calcula tam, assumindo que temos 3 bytes por pixel (bpp=24)
    tam = imagem->tamX * imagem->tamY * 3;

    if ((fread(&planos, 2, 1, arq)) != 1) {
      cerr << "Erro no arquivo " << nomearq << ", número de planos inválido." << endl;
      return 0;
    }
    if (planos != 1) {
      cerr << "Erro no arquivo " << nomearq << ", número de planos tem que ser 1." << endl;
      return 0;
    }

    if ((i = fread(&bpp, 2, 1, arq)) != 1) {
      cerr << "Erro no arquivo " << nomearq << ", bbp inválido." << endl;
      return 0;
    }
    if (bpp != 24) {
      cerr << "Erro no arquivo " << nomearq << ", bbp tem que ser 24." << endl;
      return 0;
    }

    // pula o cabeçalho e lê os dados
    fseek(arq, 24, SEEK_CUR);

    imagem->data = (char *) malloc(tam);
    if (imagem->data == NULL) {
      cerr << "Erro na alocação de memória para arquivo de imagem." << endl;
      return 0;
    }

    if ((i = fread(imagem->data, tam, 1, arq)) != 1) {
      cerr << "Erro no arquivo " << nomearq << ", dados inválidos." << endl;
      return 0;
    }

    // Inverte dados das cores (de bgr para rgb)
    for (i=0;i<tam;i+=3) {
      temp = imagem->data[i];
      imagem->data[i] = imagem->data[i+2];
      imagem->data[i+2] = temp;
    }

    return 1;
}

/*! \brief Carrega texturas dos arquivos BMP para memória
 *  \param index Índice da textura na lista do glui
 *  \param onde Variável onde armazanar o "ponteiro" para a textura carregada
 */
void carregaTextura(string arq_nome, GLuint &onde){
  Imagem *ima;

  ima = (Imagem *) malloc(sizeof(Imagem));
  if (ima == NULL) {
    cerr << "Erro ao alocar memoria para textura" << endl;
    exit(0);
  }

  if (!CarregaBMP(arq_nome.c_str(), ima)) {
    exit(1);
  }

  // Deleta a textura anterior se existir
  if (glIsTexture(onde)){
    glDeleteTextures(1, &onde);
  }

  // Cria as texturas
  glGenTextures(1, &onde);

  glBindTexture(GL_TEXTURE_2D, onde);

  // filtro para quando a imagem é maior
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  // filtro para quando a imagem é menor
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

  // Parâmetros da glTexImage2D:
  // Textura 2d, Nivel de detalhe 0 (normal), 3 componentes (rgb), largura da imagem, altura da imagem,
  // borda 0 (normal), dados no formato rgb, tipo dos dados, dados da imagem
  glTexImage2D(GL_TEXTURE_2D, 0, 3, ima->tamX, ima->tamY, 0, GL_RGB, GL_UNSIGNED_BYTE, ima->data);

  free(ima);
}

