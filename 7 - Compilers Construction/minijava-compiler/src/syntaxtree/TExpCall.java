package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TExpCall extends TExp {
  public TExp e;
  public TIdentifier i;
  public TExpList el;
  
  public TExpCall(TExp ae, TIdentifier ai, TExpList ael) {
    e=ae; i=ai; el=ael;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
