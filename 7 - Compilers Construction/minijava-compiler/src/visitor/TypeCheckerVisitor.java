package visitor;

import java.util.ArrayList;

import syntaxtree.*;
import symboltable.*;

public class TypeCheckerVisitor extends TypeDepthFirstVisitor {

	private Table table;
	private boolean err;
	private ArrayList<String> error;
	
	public TypeCheckerVisitor(Table t, boolean be, ArrayList<String> e)
	{
		table = t;
		err = be;
		error = e;
	}
	
	public boolean getError()
    {
    	return err;    	
    }
	
	@Override
	public TType visit(TProgram n) {
		n.m.accept(this);
	    for ( int i = 0; i < n.cl.size(); i++ ) {
	        n.cl.elementAt(i).accept(this);
	    }
	    return null;
	  }
	
	@Override
	public TType visit(TMainClass n) {
		table.beginScope();
	    n.i1.accept(this);
	    n.i2.accept(this);
	    n.s.accept(this);	    
	    table.endScope();
	    return null;
	  }
  
	@Override
	public TType visit(TClassDeclSimple n) {
		table.beginScope();
		n.i.accept(this);
        for(int i = 0; i < n.vl.size(); i++){
                n.vl.elementAt(i).accept(this);
        }
        for(int i = 0; i < n.ml.size(); i++){
                n.ml.elementAt(i).accept(this);
        }
        table.endScope();
        return null;
	}

	@Override
	public TType visit(TClassDeclExtends n) {
		table.beginScope();
		n.i.accept(this);
	    n.j.accept(this);
	    for ( int i = 0; i < n.vl.size(); i++ ) {
	        n.vl.elementAt(i).accept(this);
	    }
	    for ( int i = 0; i < n.ml.size(); i++ ) {
	        n.ml.elementAt(i).accept(this);
	    }	    
	    table.endScope();
	    return null;	    		
	}

	@Override
	public TType visit(TVarDecl n) {
		 Symbol s = Symbol.symbol(n.i.s);
		 TType type = (TType)table.get(s);
		 
		 if(!(type instanceof TTypeIntegerArray) && !(type instanceof TTypeInteger) && !(type instanceof TTypeBoolean) && (type == null)){
             error.add("TypeChecking error: The type of " + s.toString() + " is undeclared");
         	 err = true;                 
         }
         return null;
	}

	@Override
	public TType visit(TMethodDecl n) {
		table.beginScope();
		Symbol s = Symbol.symbol(n.i.s);
		n.t.accept(this);
		Class<TType> type = (Class<TType>)table.get(s);
	    n.i.accept(this);
	    if(!(n.t instanceof TTypeIntegerArray) && !(n.t instanceof TTypeInteger) && !(n.t instanceof TTypeBoolean) && (type == null)){
	    	error.add("TypeChecking error: Invalid return type for " + s.toString());
        	err = true;
	    }
	    for ( int i = 0; i < n.fl.size(); i++ ) {
	        n.fl.elementAt(i).accept(this);
	    }
	    for ( int i = 0; i < n.vl.size(); i++ ) {
	        n.vl.elementAt(i).accept(this);
	    }
	    for ( int i = 0; i < n.sl.size(); i++ ) {
	        n.sl.elementAt(i).accept(this);
	    }
	    n.e.accept(this);	    
        return null;
	}

	@Override
	public TType visit(TFormal n) {
		n.t.accept(this);
	    n.i.accept(this);
	    Symbol s = Symbol.symbol(n.i.s);
		TType type = (TType)table.get(s);
		        
		if(!(type instanceof TTypeIntegerArray) && !(type instanceof TTypeInteger) && !(type instanceof TTypeBoolean) && (type == null)){
            error.add("TypeChecking error: The type of " + s.toString() + " is undeclared");
            err = true;                 
        }
	    return null;
	}
	

	@Override
	public TType visit(TStatementBlock n) {
		for ( int i = 0; i < n.sl.size(); i++ ) {
	        n.sl.elementAt(i).accept(this);
	    }
	    return null;
	}

	@Override
	public TType visit(TStatementIf n) {
		n.e.accept(this);
	    n.s1.accept(this);
	    n.s2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TStatementWhile n) {
		n.e.accept(this);
	    n.s.accept(this);
	    return null;
	}

	@Override
	public TType visit(TStatementPrint n) {
		n.e.accept(this);
	    return null;
	}

	@Override
	public TType visit(TStatementAssign n) {
		n.i.accept(this);
		Symbol s = Symbol.symbol(n.i.s);
		TType type = (TType)table.get(s);
		        
		if(!(type instanceof TTypeIntegerArray) && !(type instanceof TTypeInteger) && !(type instanceof TTypeBoolean) && (type == null)){
            error.add("TypeChecking error: The variable " + s.toString() + " is undeclared");
            err = true;                 
        }
	    n.e.accept(this);
		return null;
	}

	@Override
	public TType visit(TStatementArrayAssign n) {
		n.i.accept(this);
		Symbol s = Symbol.symbol(n.i.s);
		TType type = (TType)table.get(s);
		        
		if(!(type instanceof TTypeIntegerArray) && !(type instanceof TTypeInteger) && !(type instanceof TTypeBoolean) && (type == null)){
            error.add("TypeChecking error: The variable " + s.toString() + " is undeclared");
            err = true;                 
        }
	    n.e1.accept(this);
	    n.e2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpOpAnd n) {
		n.e1.accept(this);
	    n.e2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpOpLessThan n) {
		n.e1.accept(this);
	    n.e2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpOpPlus n) {
	    n.e1.accept(this);
	    n.e2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpOpMinus n) {
	    n.e1.accept(this);
	    n.e2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpOpTimes n) {
	    n.e1.accept(this);
	    n.e2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpArrayLookup n) {
	    n.e1.accept(this);
	    n.e2.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpArrayLength n) {
	    n.e.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpCall n) {
	    n.e.accept(this);
	    n.i.accept(this);
	    for ( int i = 0; i < n.el.size(); i++ ) {
	        n.el.elementAt(i).accept(this);
	    }
	    return null;
	}

	@Override
	public TType visit(TExpIntegerLiteral n) {
		return null;
	}

	@Override
	public TType visit(TExpTrue n) {
		return null;
	}

	@Override
	public TType visit(TExpFalse n) {
		return null;
	}

	@Override
	public TType visit(TExpId n) {
		return null;
	}

	@Override
	public TType visit(TExpThis n) {
		return null;
	}

	@Override
	public TType visit(TExpNewArray n) {
	    n.e.accept(this);
	    return null;
	}

	@Override
	public TType visit(TExpNewObject n) {
		return null;
	}

	@Override
	public TType visit(TExpNot n) {
	    n.e.accept(this);
		return null;
	}

	@Override
	public TType visit(TIdentifier n) {
		return null;
	}


}
