package visitor;

import syntaxtree.*;

public class TypeDepthFirstVisitor implements TypeVisitor {

  // TMainClass m;
  // TClassDeclList cl;
  public TType visit(TProgram n) {
    n.m.accept(this);
    for ( int i = 0; i < n.cl.size(); i++ ) {
        n.cl.elementAt(i).accept(this);
    }
    return null;
  }
  
  // TIdentifier i1,i2;
  // TStatement s;
  public TType visit(TMainClass n) {
    n.i1.accept(this);
    n.i2.accept(this);
    n.s.accept(this);
    return null;
  }
  
  // TIdentifier i;
  // TVarDeclList vl;
  // TMethodDeclList ml;
  public TType visit(TClassDeclSimple n) {
    n.i.accept(this);
    for ( int i = 0; i < n.vl.size(); i++ ) {
        n.vl.elementAt(i).accept(this);
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        n.ml.elementAt(i).accept(this);
    }
    return null;
  }
 
  // TIdentifier i;
  // TIdentifier j;
  // TVarDeclList vl;
  // TMethodDeclList ml;
  public TType visit(TClassDeclExtends n) {
    n.i.accept(this);
    n.j.accept(this);
    for ( int i = 0; i < n.vl.size(); i++ ) {
        n.vl.elementAt(i).accept(this);
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        n.ml.elementAt(i).accept(this);
    }
    return null;
  }

  // TType t;
  // TIdentifier i;
  public TType visit(TVarDecl n) {
    n.t.accept(this);
    n.i.accept(this);
    return null;
  }

  // TType t;
  // TIdentifier i;
  // TFormalList fl;
  // TVarDeclList vl;
  // Statements sl;
  // TExp e;
  public TType visit(TMethodDecl n) {
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
    return null;
  }

  // TType t;
  // TIdentifier i;
  public TType visit(TFormal n) {
    n.t.accept(this);
    n.i.accept(this);
    return null;
  }

  public TType visit(TTypeIntegerArray n) {
    return null;
  }

  public TType visit(TTypeBoolean n) {
    return null;
  }

  public TType visit(TTypeInteger n) {
    return null;
  }

  // String s;
  public TType visit(TTypeIdentifier n) {
    return null;
  }

  // Statements sl;
  public TType visit(TStatementBlock n) {
    for ( int i = 0; i < n.sl.size(); i++ ) {
        n.sl.elementAt(i).accept(this);
    }
    return null;
  }

  // TExp e;
  // TStatement s1,s2;
  public TType visit(TStatementIf n) {
    n.e.accept(this);
    n.s1.accept(this);
    n.s2.accept(this);
    return null;
  }

  // TExp e;
  // TStatement s;
  public TType visit(TStatementWhile n) {
    n.e.accept(this);
    n.s.accept(this);
    return null;
  }

  // TExp e;
  public TType visit(TStatementPrint n) {
    n.e.accept(this);
    return null;
  }
  
  // TIdentifier i;
  // TExp e;
  public TType visit(TStatementAssign n) {
    n.i.accept(this);
    n.e.accept(this);
    return null;
  }

  // TIdentifier i;
  // TExp e1,e2;
  public TType visit(TStatementArrayAssign n) {
    n.i.accept(this);
    n.e1.accept(this);
    n.e2.accept(this);
    return null;
  }

  // TExp e1,e2;
  public TType visit(TExpOpAnd n) {
    n.e1.accept(this);
    n.e2.accept(this);
    return null;
  }

  // TExp e1,e2;
  public TType visit(TExpOpLessThan n) {
    n.e1.accept(this);
    n.e2.accept(this);
    return null;
  }

  // TExp e1,e2;
  public TType visit(TExpOpPlus n) {
    n.e1.accept(this);
    n.e2.accept(this);
    return null;
  }

  // TExp e1,e2;
  public TType visit(TExpOpMinus n) {
    n.e1.accept(this);
    n.e2.accept(this);
    return null;
  }

  // TExp e1,e2;
  public TType visit(TExpOpTimes n) {
    n.e1.accept(this);
    n.e2.accept(this);
    return null;
  }

  // TExp e1,e2;
  public TType visit(TExpArrayLookup n) {
    n.e1.accept(this);
    n.e2.accept(this);
    return null;
  }

  // TExp e;
  public TType visit(TExpArrayLength n) {
    n.e.accept(this);
    return null;
  }

  // TExp e;
  // TIdentifier i;
  // TExpList el;
  public TType visit(TExpCall n) {
    n.e.accept(this);
    n.i.accept(this);
    for ( int i = 0; i < n.el.size(); i++ ) {
        n.el.elementAt(i).accept(this);
    }
    return null;
  }

  // int i;
  public TType visit(TExpIntegerLiteral n) {
    return null;
  }

  public TType visit(TExpTrue n) {
    return null;
  }

  public TType visit(TExpFalse n) {
    return null;
  }

  // String s;
  public TType visit(TExpId n) {
    return null;
  }

  public TType visit(TExpThis n) {
    return null;
  }

  // TExp e;
  public TType visit(TExpNewArray n) {
    n.e.accept(this);
    return null;
  }

  // TIdentifier i;
  public TType visit(TExpNewObject n) {
    return null;
  }

  // TExp e;
  public TType visit(TExpNot n) {
    n.e.accept(this);
    return null;
  }

  // String s;
  public TType visit(TIdentifier n) {
    return null;
  }
}
