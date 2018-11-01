package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TStatementAssign extends TStatement {
  public TIdentifier i;
  public TExp e;

  public TStatementAssign(TIdentifier ai, TExp ae) {
    i=ai; e=ae; 
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}

