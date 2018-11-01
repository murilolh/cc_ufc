package visitor;

import syntaxtree.*;

public interface Visitor {
  public void visit(TProgram n);
  public void visit(TMainClass n);
  public void visit(TClassDeclSimple n);
  public void visit(TClassDeclExtends n);
  public void visit(TVarDecl n);
  public void visit(TMethodDecl n);
  public void visit(TFormal n);
  public void visit(TTypeIntegerArray n);
  public void visit(TTypeBoolean n);
  public void visit(TTypeInteger n);
  public void visit(TTypeIdentifier n);
  public void visit(TStatementBlock n);
  public void visit(TStatementIf n);
  public void visit(TStatementWhile n);
  public void visit(TStatementPrint n);
  public void visit(TStatementAssign n);
  public void visit(TStatementArrayAssign n);
  public void visit(TExpOpAnd n);
  public void visit(TExpOpLessThan n);
  public void visit(TExpOpPlus n);
  public void visit(TExpOpMinus n);
  public void visit(TExpOpTimes n);
  public void visit(TExpArrayLookup n);
  public void visit(TExpArrayLength n);
  public void visit(TExpCall n);
  public void visit(TExpIntegerLiteral n);
  public void visit(TExpTrue n);
  public void visit(TExpFalse n);
  public void visit(TExpId n);
  public void visit(TExpThis n);
  public void visit(TExpNewArray n);
  public void visit(TExpNewObject n);
  public void visit(TExpNot n);
  public void visit(TIdentifier n);
}
