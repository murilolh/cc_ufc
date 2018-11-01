package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TTypeInteger extends TType {
	
  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
