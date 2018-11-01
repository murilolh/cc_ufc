package visitor;

import syntaxtree.*;

public class PrettyPrintVisitor implements Visitor {

  // TMainClass m;
  // TClassDeclList cl;
  public void visit(TProgram n) {
    n.m.accept(this);
    for ( int i = 0; i < n.cl.size(); i++ ) {
        System.out.println();
        n.cl.elementAt(i).accept(this);
    }
  }
  
  // TIdentifier i1,i2;
  // TStatement s;
  public void visit(TMainClass n) {
    System.out.print("class ");
    n.i1.accept(this);
    System.out.println(" {");
    System.out.print("  public static void main (String [] ");
    n.i2.accept(this);
    System.out.println(") {");
    System.out.print("    ");
    n.s.accept(this);
    System.out.println("  }");
    System.out.println("}");
  }

  // TIdentifier i;
  // TVarDeclList vl;
  // TMethodDeclList ml;
  public void visit(TClassDeclSimple n) {
    System.out.print("class ");
    n.i.accept(this);
    System.out.println(" { ");
    for ( int i = 0; i < n.vl.size(); i++ ) {
        System.out.print("  ");
        n.vl.elementAt(i).accept(this);
        if ( i+1 < n.vl.size() ) { System.out.println(); }
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        System.out.println();
        n.ml.elementAt(i).accept(this);
    }
    System.out.println();
    System.out.println("}");
  }
 
  // TIdentifier i;
  // TIdentifier j;
  // TVarDeclList vl;
  // TMethodDeclList ml;
  public void visit(TClassDeclExtends n) {
    System.out.print("class ");
    n.i.accept(this);
    System.out.println(" extends ");
    n.j.accept(this);
    System.out.println(" { ");
    for ( int i = 0; i < n.vl.size(); i++ ) {
        System.out.print("  ");
        n.vl.elementAt(i).accept(this);
        if ( i+1 < n.vl.size() ) { System.out.println(); }
    }
    for ( int i = 0; i < n.ml.size(); i++ ) {
        System.out.println();
        n.ml.elementAt(i).accept(this);
    }
    System.out.println();
    System.out.println("}");
  }

  // TType t;
  // TIdentifier i;
  public void visit(TVarDecl n) {
    n.t.accept(this);
    System.out.print(" ");
    n.i.accept(this);
    System.out.print(";");
  }

  // TType t;
  // TIdentifier i;
  // TFormalList fl;
  // TVarDeclList vl;
  // Statements sl;
  // TExp e;
  public void visit(TMethodDecl n) {
    System.out.print("  public ");
    n.t.accept(this);
    System.out.print(" ");
    n.i.accept(this);
    System.out.print(" (");
    for ( int i = 0; i < n.fl.size(); i++ ) {
        n.fl.elementAt(i).accept(this);
        if (i+1 < n.fl.size()) { System.out.print(", "); }
    }
    System.out.println(") { ");
    for ( int i = 0; i < n.vl.size(); i++ ) {
        System.out.print("    ");
        n.vl.elementAt(i).accept(this);
        System.out.println("");
    }
    for ( int i = 0; i < n.sl.size(); i++ ) {
        System.out.print("    ");
        n.sl.elementAt(i).accept(this);
        if ( i < n.sl.size() ) { System.out.println(""); }
    }
    System.out.print("    return ");
    n.e.accept(this);
    System.out.println(";");
    System.out.print("  }");
  }

  // TType t;
  // TIdentifier i;
  public void visit(TFormal n) {
    n.t.accept(this);
    System.out.print(" ");
    n.i.accept(this);
  }

  public void visit(TTypeIntegerArray n) {
    System.out.print("int []");
  }

  public void visit(TTypeBoolean n) {
    System.out.print("boolean");
  }

  public void visit(TTypeInteger n) {
    System.out.print("int");
  }

  // String s;
  public void visit(TTypeIdentifier n) {
    System.out.print(n.s);
  }

  // Statements sl;
  public void visit(TStatementBlock n) {
    System.out.println("{ ");
    for ( int i = 0; i < n.sl.size(); i++ ) {
        System.out.print("      ");
        n.sl.elementAt(i).accept(this);
        System.out.println();
    }
    System.out.print("    } ");
  }

  // TExp e;
  // TStatement s1,s2;
  public void visit(TStatementIf n) {
    System.out.print("if (");
    n.e.accept(this);
    System.out.println(") ");
    System.out.print("    ");
    n.s1.accept(this);
    System.out.println();
    System.out.print("    else ");
    n.s2.accept(this);
  }

  // TExp e;
  // TStatement s;
  public void visit(TStatementWhile n) {
    System.out.print("while (");
    n.e.accept(this);
    System.out.print(") ");
    n.s.accept(this);
  }

  // TExp e;
  public void visit(TStatementPrint n) {
    System.out.print("System.out.println(");
    n.e.accept(this);
    System.out.print(");");
  }
  
  // TIdentifier i;
  // TExp e;
  public void visit(TStatementAssign n) {
    n.i.accept(this);
    System.out.print(" = ");
    n.e.accept(this);
    System.out.print(";");
  }

  // TIdentifier i;
  // TExp e1,e2;
  public void visit(TStatementArrayAssign n) {
    n.i.accept(this);
    System.out.print("[");
    n.e1.accept(this);
    System.out.print("] = ");
    n.e2.accept(this);
    System.out.print(";");
  }

  // TExp e1,e2;
  public void visit(TExpOpAnd n) {
    System.out.print("(");
    n.e1.accept(this);
    System.out.print(" && ");
    n.e2.accept(this);
    System.out.print(")");
  }

  // TExp e1,e2;
  public void visit(TExpOpLessThan n) {
    System.out.print("(");
    n.e1.accept(this);
    System.out.print(" < ");
    n.e2.accept(this);
    System.out.print(")");
  }

  // TExp e1,e2;
  public void visit(TExpOpPlus n) {
    System.out.print("(");
    n.e1.accept(this);
    System.out.print(" + ");
    n.e2.accept(this);
    System.out.print(")");
  }

  // TExp e1,e2;
  public void visit(TExpOpMinus n) {
    System.out.print("(");
    n.e1.accept(this);
    System.out.print(" - ");
    n.e2.accept(this);
    System.out.print(")");
  }

  // TExp e1,e2;
  public void visit(TExpOpTimes n) {
    System.out.print("(");
    n.e1.accept(this);
    System.out.print(" * ");
    n.e2.accept(this);
    System.out.print(")");
  }

  // TExp e1,e2;
  public void visit(TExpArrayLookup n) {
    n.e1.accept(this);
    System.out.print("[");
    n.e2.accept(this);
    System.out.print("]");
  }

  // TExp e;
  public void visit(TExpArrayLength n) {
    n.e.accept(this);
    System.out.print(".length");
  }

  // TExp e;
  // TIdentifier i;
  // TExpList el;
  public void visit(TExpCall n) {
    n.e.accept(this);
    System.out.print(".");
    n.i.accept(this);
    System.out.print("(");
    for ( int i = 0; i < n.el.size(); i++ ) {
        n.el.elementAt(i).accept(this);
        if ( i+1 < n.el.size() ) { System.out.print(", "); }
    }
    System.out.print(")");
  }

  // int i;
  public void visit(TExpIntegerLiteral n) {
    System.out.print(n.i);
  }

  public void visit(TExpTrue n) {
    System.out.print("true");
  }

  public void visit(TExpFalse n) {
    System.out.print("false");
  }

  // String s;
  public void visit(TExpId n) {
    System.out.print(n.s);
  }

  public void visit(TExpThis n) {
    System.out.print("this");
  }

  // TExp e;
  public void visit(TExpNewArray n) {
    System.out.print("new int [");
    n.e.accept(this);
    System.out.print("]");
  }

  // TIdentifier i;
  public void visit(TExpNewObject n) {
    System.out.print("new ");
    System.out.print(n.i.s);
    System.out.print("()");
  }

  // TExp e;
  public void visit(TExpNot n) {
    System.out.print("!");
    n.e.accept(this);
  }

  // String s;
  public void visit(TIdentifier n) {
    System.out.print(n.s);
  }
}
