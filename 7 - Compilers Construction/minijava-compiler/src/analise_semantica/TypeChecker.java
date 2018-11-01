package analise_semantica;

import javacc.*;
import visitor.*;

import java.io.*;
import java.util.*;
import syntaxtree.*;
import symboltable.*;

public class TypeChecker {
	
	private Table st;
	private boolean err;
	private TProgram tree;

	public TypeChecker(TProgram at)
	{
		tree = at;
		st = new Table();
		err = false;
	}
	
	public void perform(ArrayList<String> error)
	{
		SymbolTableVisitor stv = new SymbolTableVisitor();
		st = stv.buildSymbolTable(tree);
		TypeCheckerVisitor tcv = new TypeCheckerVisitor(st, err, error);
		tcv.visit(tree);
		err = tcv.getError();
		return;		
	}
	
	public void printResult()
	{
		if(!err)
			System.out.println("OK");
		else
			System.out.println("Ocorreram erros na checagem de tipos!");		
	}

}
