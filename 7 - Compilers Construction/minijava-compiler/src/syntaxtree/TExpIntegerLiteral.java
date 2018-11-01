package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TExpIntegerLiteral extends TExp {
  public int i;

  public TExpIntegerLiteral(int ai) {
    i=ai;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
