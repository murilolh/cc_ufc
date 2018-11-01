package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TStatementArrayAssign extends TStatement {
  public TIdentifier i;
  public TExp e1,e2;

  public TStatementArrayAssign(TIdentifier ai, TExp ae1, TExp ae2) {
    i=ai; e1=ae1; e2=ae2;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }

}

