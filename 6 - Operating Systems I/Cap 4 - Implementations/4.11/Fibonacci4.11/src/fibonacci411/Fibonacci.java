package fibonacci411;

public class Fibonacci extends Thread{

    int numero;
    Integer[] fib;

    public Fibonacci(int n) {
        numero = n;        
    }

    public Integer[] getf(){
        return fib;
    }
    
    public void run(){
        int i;
        fib = new Integer[30];
        System.out.println("Numero passado: " + numero);
        fib[0]=0;
        fib[1]=1;
        for(i=2;i<numero;i++)
           fib[i] = fib[i-1] + fib[i-2];
        System.out.println("\n\n----FIM DA THREAD------");    
    }    
}