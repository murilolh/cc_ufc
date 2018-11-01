package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TExpTrue extends TExp {
  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
