package visitor;

import symboltable.*;
import syntaxtree.*;

public class SymbolTableVisitor implements Visitor{

	private Table table;
    
    public Table buildSymbolTable(TProgram program){
            table = new Table();
            visit(program);
            return table;
    }   
    
    public void visit(TProgram n) {
        n.m.accept(this);
        for(int i =0; i< n.cl.size(); i++){
                n.cl.elementAt(i).accept(this);
        }

    }

	public void visit(TMainClass n) {
	        Symbol clas = Symbol.symbol(n.i1.s);
	        table.put(clas, clas.getClass());
	        clas = Symbol.symbol(n.i2.s);
	        table.put(clas, clas.getClass());
	        n.s.accept(this);
	        //table.beginScope();
	        //table.endScope();
	}
	
	public void visit(TClassDeclSimple n) {
	        Symbol clas = Symbol.symbol(n.i.s);
	        table.put(clas, clas.getClass());
	        //table.beginScope();
	        for(int i = 0; i < n.vl.size(); i++){
	                n.vl.elementAt(i).accept(this);
	        }
	        for(int j = 0; j < n.ml.size(); j++){
	                n.ml.elementAt(j).accept(this);
	        }
	        //table.endScope();
	}
	
	public void visit(TClassDeclExtends n) {
	        Symbol clas = Symbol.symbol(n.i.s);
	        table.put(clas, clas.getClass());
	        //table.beginScope();
	        for(int i = 0; i < n.vl.size(); i++){
	                n.vl.elementAt(i).accept(this);
	        }
	        for(int j = 0; j < n.ml.size(); j++){
	                n.ml.elementAt(j).accept(this);
	        }
	        //table.endScope();
	}
	
	public void visit(TVarDecl n) {		
	        table.put(Symbol.symbol(n.i.s), n.t);	        
	}
	
	public void visit(TMethodDecl n) {
	        Symbol name = Symbol.symbol(n.i.s);
	        table.put(name, name.getClass());
	        //table.beginScope();
	        for ( int i = 0; i < n.fl.size(); i++ ) {
	            n.fl.elementAt(i).accept(this);
	        }
	        for ( int i = 0; i < n.vl.size(); i++ ) {
	            n.vl.elementAt(i).accept(this);
	        }
	        for ( int i = 0; i < n.sl.size(); i++ ) {
	            n.sl.elementAt(i).accept(this);
	        }
	        //table.endScope();
	}

	@Override
	public void visit(TFormal n) {
		table.put(Symbol.symbol(n.i.s), n.t);
	}

	@Override
	public void visit(TTypeIntegerArray n) {
		
	}

	@Override
	public void visit(TTypeBoolean n) {
		
	}

	@Override
	public void visit(TTypeInteger n) {
		
	}

	@Override
	public void visit(TTypeIdentifier n) {
		
	}

	@Override
	public void visit(TStatementBlock n) {
			
	}

	@Override
	public void visit(TStatementIf n) {
			
	}

	@Override
	public void visit(TStatementWhile n) {
			
	}

	@Override
	public void visit(TStatementPrint n) {
				
	}

	@Override
	public void visit(TStatementAssign n) {
		
	}

	@Override
	public void visit(TStatementArrayAssign n) {
		
	}

	@Override
	public void visit(TExpOpAnd n) {
		
	}

	@Override
	public void visit(TExpOpLessThan n) {
		
	}

	@Override
	public void visit(TExpOpPlus n) {
		
	}

	@Override
	public void visit(TExpOpMinus n) {
		
	}

	@Override
	public void visit(TExpOpTimes n) {
		
	}

	@Override
	public void visit(TExpArrayLookup n) {
		
	}

	@Override
	public void visit(TExpArrayLength n) {
		
	}

	@Override
	public void visit(TExpCall n) {
		
	}

	@Override
	public void visit(TExpIntegerLiteral n) {
		
	}

	@Override
	public void visit(TExpTrue n) {
		
	}

	@Override
	public void visit(TExpFalse n) {
		
	}

	@Override
	public void visit(TExpId n) {
		
	}

	@Override
	public void visit(TExpThis n) {
		
	}

	@Override
	public void visit(TExpNewArray n) {
		
	}

	@Override
	public void visit(TExpNewObject n) {
		
	}

	@Override
	public void visit(TExpNot n) {
		
	}

	@Override
	public void visit(TIdentifier n) {
	
	}
    	
}
