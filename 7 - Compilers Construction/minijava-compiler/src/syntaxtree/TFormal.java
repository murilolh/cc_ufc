package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TFormal {
  public TType t;
  public TIdentifier i;
 
  public TFormal(TType at, TIdentifier ai) {
    t=at; i=ai;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
