package analise_lexica;

import javacc.*;
import java.io.*;
import java.util.*;

public class Lexer {
        
	private Grammar gm;
	private ArrayList<Token> token;
	        
	public Lexer(InputStream is)
	{
		gm = new Grammar(is);
		token = new ArrayList<Token>();   
	}
	        
	public InputStream analize(ArrayList<String> error) throws ParseException,Exception
	{
		Token tok = new Token();        //Instância do token a ser verificado
		String arq = "";                        //String que guarda o conteúdos do arquivo sem os SKIP's e os ERROS
	    do
	    {
	    	tok = gm.getToken();            //Obtém um token
	                                              
	        if(tok.kind == 52)//Caso seja um erro lexico
	        {
	        	String erro = "";
	            erro = erro + ("Lexical Error: Encountered \"");
	            erro = erro + tok.image;
	            erro = erro + "\" at line " + tok.beginLine + ", column " + tok.beginColumn;
	            error.add(erro);        //Insere o erro na lista de erros
	        }
	        else
	        {
	        	token.add(tok);                          //Adiciona o token à lista de tokens
	            arq = arq + " " + tok.image; //Adiciona o token ao novo arquivo
	        }
	    }
	    while(tok.kind != 0);                   //Enquanto nao encontrar o EOF  
	                                
	    return new ByteArrayInputStream(arq.getBytes("UTF-8")); //Retorna o inputStream com o conteúdo do novo arquivo
	}       
	        
	public void printTokens() throws Exception
	{
		for(int i =0; i < token.size(); i++)
		{
			String tipo = gm.token_source.tokenImage[token.get(i).kind];
	        if((token.get(i).kind == 49) || (token.get(i).kind == 50)) //Impressao para ID ou NUM
	        	System.out.print(tipo + "(" + token.get(i).image + ") ");                               
	        else
	            System.out.print("<" + token.get(i).image.toUpperCase() + "> ");
	    }
	}
}