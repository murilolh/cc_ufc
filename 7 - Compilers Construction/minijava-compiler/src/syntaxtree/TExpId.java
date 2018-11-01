package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TExpId extends TExp {
  public String s;
  public TExpId(String as) { 
    s=as;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
