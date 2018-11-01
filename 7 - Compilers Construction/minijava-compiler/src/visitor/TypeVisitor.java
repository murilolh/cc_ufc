package visitor;

import syntaxtree.*;

public interface TypeVisitor {
  public TType visit(TProgram n);
  public TType visit(TMainClass n);
  public TType visit(TClassDeclSimple n);
  public TType visit(TClassDeclExtends n);
  public TType visit(TVarDecl n);
  public TType visit(TMethodDecl n);
  public TType visit(TFormal n);
  public TType visit(TTypeIntegerArray n);
  public TType visit(TTypeBoolean n);
  public TType visit(TTypeInteger n);
  public TType visit(TTypeIdentifier n);
  public TType visit(TStatementBlock n);
  public TType visit(TStatementIf n);
  public TType visit(TStatementWhile n);
  public TType visit(TStatementPrint n);
  public TType visit(TStatementAssign n);
  public TType visit(TStatementArrayAssign n);
  public TType visit(TExpOpAnd n);
  public TType visit(TExpOpLessThan n);
  public TType visit(TExpOpPlus n);
  public TType visit(TExpOpMinus n);
  public TType visit(TExpOpTimes n);
  public TType visit(TExpArrayLookup n);
  public TType visit(TExpArrayLength n);
  public TType visit(TExpCall n);
  public TType visit(TExpIntegerLiteral n);
  public TType visit(TExpTrue n);
  public TType visit(TExpFalse n);
  public TType visit(TExpId n);
  public TType visit(TExpThis n);
  public TType visit(TExpNewArray n);
  public TType visit(TExpNewObject n);
  public TType visit(TExpNot n);
  public TType visit(TIdentifier n);
}
