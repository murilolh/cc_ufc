package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TMainClass {
  public TIdentifier i1,i2;
  public TStatement s;

  public TMainClass(TIdentifier ai1, TIdentifier ai2, TStatement as) {
    i1=ai1; i2=ai2; s=as;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}

