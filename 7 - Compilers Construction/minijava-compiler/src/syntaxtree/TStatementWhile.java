package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TStatementWhile extends TStatement {
  public TExp e;
  public TStatement s;

  public TStatementWhile(TExp ae, TStatement as) {
    e=ae; s=as; 
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}

