package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TExpNewObject extends TExp {
  public TIdentifier i;
  
  public TExpNewObject(TIdentifier ai) {
    i=ai;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
