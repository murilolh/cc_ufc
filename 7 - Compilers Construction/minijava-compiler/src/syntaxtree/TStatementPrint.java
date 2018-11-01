package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TStatementPrint extends TStatement {
  public TExp e;

  public TStatementPrint(TExp ae) {
    e=ae; 
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
