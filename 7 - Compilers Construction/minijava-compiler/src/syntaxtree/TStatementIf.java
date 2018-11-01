package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TStatementIf extends TStatement {
  public TExp e;
  public TStatement s1,s2;

  public TStatementIf(TExp ae, TStatement as1, TStatement as2) {
    e=ae; s1=as1; s2=as2;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}

