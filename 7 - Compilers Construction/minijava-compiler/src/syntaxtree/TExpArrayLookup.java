package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TExpArrayLookup extends TExp {
  public TExp e1,e2;
  
  public TExpArrayLookup(TExp ae1, TExp ae2) { 
    e1=ae1; e2=ae2;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
