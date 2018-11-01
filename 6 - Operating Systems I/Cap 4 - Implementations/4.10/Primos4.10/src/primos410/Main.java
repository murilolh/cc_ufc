package primos410;

import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException{
        System.out.println("Digite o numero n: ");        
        Scanner s = new Scanner( System.in );  
        int n = s.nextInt();  
        Thread runner = new Primo(n);        
        runner.start();
    }
}
