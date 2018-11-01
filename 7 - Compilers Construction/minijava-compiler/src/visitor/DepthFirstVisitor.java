package visitor;

import syntaxtree.*;

public class DepthFirstVisitor implements Visitor {

  // TMainClass m;
  // TClassDeclList cl;
  public void visit(TProgram n) {
    n.m.accept(this);
    for ( int i = 0; i < n.cl.size(); i++ ) {
        n.cl.elementAt(i).accept(this);
    }
  }
  
  // TIdentifier i1,i2;
  // TStatement s;
  public void visit(TMainClass n) {
    n.i1.accept(this);
    n.i2.accept(this);
    n.s.accept(this);
  }
  
  // TIdentifier i;
  // TVarDeclList vl;
  // TMethodDeclList ml;
  public void visit(TClassDeclSimple n) {
    n.i.accept(this);
    for ( int i = 0; i < n.vl.size(); i++ ) {
        n.vl.elementAt(i).accept(this);
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        n.ml.elementAt(i).accept(this);
    }
  }
 
  // TIdentifier i;
  // TIdentifier j;
  // TVarDeclList vl;
  // TMethodDeclList ml;
  public void visit(TClassDeclExtends n) {
    n.i.accept(this);
    n.j.accept(this);
    for ( int i = 0; i < n.vl.size(); i++ ) {
        n.vl.elementAt(i).accept(this);
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        n.ml.elementAt(i).accept(this);
    }
  }

  // TType t;
  // TIdentifier i;
  public void visit(TVarDecl n) {
    n.t.accept(this);
    n.i.accept(this);
  }

  // TType t;
  // TIdentifier i;
  // TFormalList fl;
  // TVarDeclList vl;
  // Statements sl;
  // TExp e;
  public void visit(TMethodDecl n) {
    n.t.accept(this);
    n.i.accept(this);
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
  }

  // TType t;
  // TIdentifier i;
  public void visit(TFormal n) {
    n.t.accept(this);
    n.i.accept(this);
  }

  public void visit(TTypeIntegerArray n) {
  }

  public void visit(TTypeBoolean n) {
  }

  public void visit(TTypeInteger n) {
  }

  // String s;
  public void visit(TTypeIdentifier n) {
  }

  // Statements sl;
  public void visit(TStatementBlock n) {
    for ( int i = 0; i < n.sl.size(); i++ ) {
        n.sl.elementAt(i).accept(this);
    }
  }

  // TExp e;
  // TStatement s1,s2;
  public void visit(TStatementIf n) {
    n.e.accept(this);
    n.s1.accept(this);
    n.s2.accept(this);
  }

  // TExp e;
  // TStatement s;
  public void visit(TStatementWhile n) {
    n.e.accept(this);
    n.s.accept(this);
  }

  // TExp e;
  public void visit(TStatementPrint n) {
    n.e.accept(this);
  }
  
  // TIdentifier i;
  // TExp e;
  public void visit(TStatementAssign n) {
    n.i.accept(this);
    n.e.accept(this);
  }

  // TIdentifier i;
  // TExp e1,e2;
  public void visit(TStatementArrayAssign n) {
    n.i.accept(this);
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // TExp e1,e2;
  public void visit(TExpOpAnd n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // TExp e1,e2;
  public void visit(TExpOpLessThan n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // TExp e1,e2;
  public void visit(TExpOpPlus n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // TExp e1,e2;
  public void visit(TExpOpMinus n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // TExp e1,e2;
  public void visit(TExpOpTimes n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // TExp e1,e2;
  public void visit(TExpArrayLookup n) {
    n.e1.accept(this);
    n.e2.accept(this);
  }

  // TExp e;
  public void visit(TExpArrayLength n) {
    n.e.accept(this);
  }

  // TExp e;
  // TIdentifier i;
  // TExpList el;
  public void visit(TExpCall n) {
    n.e.accept(this);
    n.i.accept(this);
    for ( int i = 0; i < n.el.size(); i++ ) {
        n.el.elementAt(i).accept(this);
    }
  }

  // int i;
  public void visit(TExpIntegerLiteral n) {
  }

  public void visit(TExpTrue n) {
  }

  public void visit(TExpFalse n) {
  }

  // String s;
  public void visit(TExpId n) {
  }

  public void visit(TExpThis n) {
  }

  // TExp e;
  public void visit(TExpNewArray n) {
    n.e.accept(this);
  }

  // TIdentifier i;
  public void visit(TExpNewObject n) {
  }

  // TExp e;
  public void visit(TExpNot n) {
    n.e.accept(this);
  }

  // String s;
  public void visit(TIdentifier n) {
  }
}
