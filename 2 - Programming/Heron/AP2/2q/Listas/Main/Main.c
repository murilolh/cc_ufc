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
      }                                  //Verifica��o de Lista vazia
      b = (struct Info*)malloc(sizeof(struct Info)); 
      b->info = (int*)malloc(sizeof(int)); 
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);  
      l = Cons(b ,l);                     //Inser��o 1 em l
      b = (struct Info*)malloc(sizeof(struct Info));  
      b->info = (int*)malloc(sizeof(int)); 
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                   //Inser��o 2 em l
      if(IsEmpty(l))
      {
         printf("\nError: List Empty\n");
         getch();
      } 
      else 
           printf("\nList don't Empty\n");  //Verifica��o de Lista vazia
      b = (struct Info*)malloc(sizeof(struct Info)); 
      b->info = (int*)malloc(sizeof(int));
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                   //Inser��o 3 em l
      b = (struct Info*)malloc(sizeof(struct Info));  
      b->info = (int*)malloc(sizeof(int));
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                  //Inser��o 4 em l
      printf("\n\nRemove Key: ");
      scanf("%d", &c);    
      l = Rem(c, l);                    //Remo��o 1 em l
      printf("\n\nRemove Key: ");
      scanf("%d", &c);    
      l = Rem(c, l);                    //Remo��o 2 em l       
      b = (struct Info*)malloc(sizeof(struct Info));  
      b->info = (int*)malloc(sizeof(int));
      printf("\n\nInsert Key: ");
      scanf("%d", &b->Key);    
      printf("\nInsert Info: ");
      scanf("%d", &b->info);    
      l = Cons(b ,l);                    //Inser��o 5 em l
      printf("\n\nLevel 1 -> Sucess!\n");getch(); 
      l2 = Head(l);                     //Head 1 em l2
      l3 = Tail(l);                     //Tail 1 em l3     
      l4 = Tail(l);                     //Tail 2 em l4
      printf("\n\nRemove Key: ");
      scanf("%d", &c);    
      l = Rem(c, l);                    //Remo��o 3 em l       
      printf("\n\nRemove Key: ");
      scanf("%d", &c);        
      l3 = Rem(c, l3);                  //Remo��o 4 em l3      
      printf("\n\nRemove Key: ");
      scanf("%d", &c);        
      l3 = Rem(c, l3);                  //Remo��o 5 em l3      
      printf("\n\nRemove Key: ");
      scanf("%d", &c);       
      l4 = Rem(c, l4);                  //Remo��o 6 em l4        
      printf("\n\nRemove Key: ");
      scanf("%d", &c);
      l = Rem(c, l);                    //Remo��o 7 em l       
      getch();
      system("cls");
}

