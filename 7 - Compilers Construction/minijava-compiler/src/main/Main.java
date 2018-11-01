/* Classe principal de teste do compilador */
package main;

import javacc.*;
import syntaxtree.*;
import java.io.*;
import java.util.*;
import analise_lexica.*;
import analise_sintatica.*;
import analise_semantica.*;

public class Main {
	public static void main(String [] args) throws ParseException, Exception
	{
		ArrayList<String> error	= new ArrayList<String>(); //ArrayList que guarda os erros encontrados
				
		Textfile arquivo = new Textfile();
		InputStream original = arquivo.getFile(); //Faz o InputStream receber o conteúdo do arquivo
		InputStream modAl;						  //InputStrem retornado pelo Lexer, sem os Skips e os erros léxicos
		TProgram tree;
				
		System.out.println("----- ANÁLISE LÉXICA -----");
		Lexer al = new Lexer(original);		      //Instancia o analisador léxico
		modAl = al.analize(error);		    	  //Faz a análise léxica
		al.printTokens();				 	      //Imprime a lista de tokens obtida
		System.out.println("\nfim ANÁLISE LÉXICA");
		
		System.out.println("----- ANÁLISE SINTÁTICA -----");
		Parser as = new Parser(modAl);  	      //Instancia o analisador sintático
		tree = as.analize(error);	 	          //Faz a análise sintática
		as.printResult();				 	      //Imprime o resultado da análise
		System.out.println("fim ANÁLISE SINTÁTICA");
		
		System.out.println("----- CHECAGEM DE TIPOS -----");
		TypeChecker tc = new TypeChecker(tree);   //Instancia o type checker
		tc.perform(error);	 	    		      //Faz a checagem de tipos 
		tc.printResult();				 	      //Imprime o resultado da análise
		System.out.println("fim CHECAGEM DE TIPOS");
		
		if(!error.isEmpty())	//Imprime a lista de erros encontrados durante o processo
		{	
			System.out.println("\n----- ERROS -----");
			for(int i =0; i < error.size(); i++)  
				System.out.println(error.get(i));
		}
	}	
}