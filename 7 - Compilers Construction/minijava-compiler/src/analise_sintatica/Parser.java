package analise_sintatica;

import javacc.*;
import syntaxtree.*;
import java.io.*;
import java.util.*;

public class Parser {
	
	private Grammar gm;
	private boolean err;
	
	public Parser(InputStream is)
	{
		gm = new Grammar(is);
		err = false;
	}
	
	public TProgram analize(ArrayList<String> error)
	{
		TProgram tree = null;
		try
		{
			tree = gm.Program();			
		}
		catch(ParseException e)
		{
			error.add("Syntatical Error: " + e.getMessage());
			err = true;			
		}
		return tree;
	}	
	
	public void printResult()
	{
		if(!err)
			System.out.println("OK");
		else
			System.out.println("Ocorreram erros sintáticos!");		
	}
}