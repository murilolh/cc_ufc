package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TTypeIdentifier extends TType {
  public String s;

  public TTypeIdentifier(String as) {
    s=as;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
