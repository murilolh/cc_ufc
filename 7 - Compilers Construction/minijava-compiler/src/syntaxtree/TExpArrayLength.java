package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TExpArrayLength extends TExp {
  public TExp e;
  
  public TExpArrayLength(TExp ae) {
    e=ae; 
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
