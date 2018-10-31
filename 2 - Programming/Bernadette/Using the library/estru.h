#include "estru.c"

//Funções da Lista Estática (Ordenada)
void lste_cria(Lste *Lista);
int lste_vaz(Lste *Lista);
void lste_insul(int x,Lste *Lista);
void lste_ord(Lste *Lista);
void lste_inpos(int x, int p, Lste *Lista);
void lste_remul(Lste *Lista);
void lste_rempos(int p, Lste *Lista);
int lste_print(Lste *Lista);
int lste_busc(int x, Lste *Lista);

//Funções da Lista Dinâmica
Lstd* lstd_cria();
int lstd_vaz(Lstd *Lista);
void lstd_ins(TipoT x,Lstd *Lista);
void lstd_remcom(int x, Lstd *Lista);
int lstd_busc(int x, Lstd *Lista);
void lstd_print(Lstd *Lista);

//Funções da Pilha Estática
Plhe* plhe_cria();
int plhe_vaz (Plhe *Pilha);
void plhe_ins (Plhe *Pilha, int x);
int plhe_rem (Plhe *Pilha);
int plhe_busc (int x , Plhe *Pilha);
int plhe_print (Plhe *Pilha);

//Funções da Pilha Dinâmica
Plhd* plhd_cria();
int plhd_vaz(Plhd *Pilha);
void plhd_ins(TipoT x, Plhd *Pilha);
int plhd_rem (Plhd *Pilha);
int plhd_busc(int x , Plhd *Pilha);
void plhd_print(Plhd *Pilha);

//Funções da Fila Estática (Circular)

//Funções da Fila Dinâmica
Fild* fild_cria();
int fild_vaz(Fild *Fila);
void fild_ins(TipoT x,Fild *Fila);
void fild_rem(Fild *Fila);
int fild_busc(int x, Fild *Fila);
void fild_print(Fild *Fila);
