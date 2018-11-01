package primos410;

public class Primo extends Thread{

    int numero;

    public Primo(int n) {
        numero = n;
    }

    public void run(){
        int i,j,p;
        System.out.println("Numero passado: " + numero);
        System.out.print("\nSEQUENCIA DE PRIMOS: ");
        p=0;
        for(i=1;i<=numero;i++){
            for(j=2;j<i;j++){
                if (i%j == 0){
                    p=1;
                    break;
                }
            }
            if (p==0)
                System.out.print(i + " ");
            p=0;
        }
        System.out.println("\n\n----FIM DA THREAD------");    
    }
}
