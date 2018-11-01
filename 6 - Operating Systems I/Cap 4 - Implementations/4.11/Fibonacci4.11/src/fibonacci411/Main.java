package fibonacci411;

import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException{
        int i;
        System.out.println("Digite o numero n: ");        
        Scanner s = new Scanner( System.in );  
        int n = s.nextInt();  
        Integer[] fib;
        Fibonacci runner = new Fibonacci(n);
        runner.start();
        fib = runner.getf();
        while (runner.isAlive()){}
        for(i=0;i<n;i++)
            System.out.print(fib[i] + " ");
    }
}