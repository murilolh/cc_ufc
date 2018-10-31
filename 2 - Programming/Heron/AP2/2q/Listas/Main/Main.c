//Main.c

#include "../List/List1.h"

struct Info
{
        int Key;
        void *info;
};

int main()
{
      List l, l2, l3, l4;
      struct Info *b; 
      int c;
      l = Empty();
      if(IsEmpty(l))
      {
         printf("\nError: List Empty\n");
         getch();
      }                                  //Verificação de Lista vazia
      b = (struct Info*)malloc(sizeof(struct Info)); 
      b->info = (int*)malloc(sizeof(int)); 
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);  
      l = Cons(b ,l);                     //Inserção 1 em l
      b = (struct Info*)malloc(sizeof(struct Info));  
      b->info = (int*)malloc(sizeof(int)); 
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                   //Inserção 2 em l
      if(IsEmpty(l))
      {
         printf("\nError: List Empty\n");
         getch();
      } 
      else 
           printf("\nList don't Empty\n");  //Verificação de Lista vazia
      b = (struct Info*)malloc(sizeof(struct Info)); 
      b->info = (int*)malloc(sizeof(int));
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                   //Inserção 3 em l
      b = (struct Info*)malloc(sizeof(struct Info));  
      b->info = (int*)malloc(sizeof(int));
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                  //Inserção 4 em l
      printf("\n\nRemove Key: ");
      scanf("%d", &c);    
      l = Rem(c, l);                    //Remoção 1 em l
      printf("\n\nRemove Key: ");
      scanf("%d", &c);    
      l = Rem(c, l);                    //Remoção 2 em l       
      b = (struct Info*)malloc(sizeof(struct Info));  
      b->info = (int*)malloc(sizeof(int));
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                    //Inserção 5 em l
      printf("\n\nLevel 1 -> Sucess!\n");getch(); 
      l2 = Head(l);                     //Head 1 em l2
      l3 = Tail(l);                     //Tail 1 em l3     
      l4 = Tail(l);                     //Tail 2 em l4
      printf("\n\nRemove Key: ");
      scanf("%d", &c);    
      l = Rem(c, l);                    //Remoção 3 em l       
      printf("\n\nRemove Key: ");
      scanf("%d", &c);        
      l3 = Rem(c, l3);                  //Remoção 4 em l3      
      printf("\n\nRemove Key: ");
      scanf("%d", &c);        
      l3 = Rem(c, l3);                  //Remoção 5 em l3      
      printf("\n\nRemove Key: ");
      scanf("%d", &c);       
      l4 = Rem(c, l4);                  //Remoção 6 em l4        
      printf("\n\nRemove Key: ");
      scanf("%d", &c);
      l = Rem(c, l);                    //Remoção 7 em l       
      getch();
      system("cls");
}

