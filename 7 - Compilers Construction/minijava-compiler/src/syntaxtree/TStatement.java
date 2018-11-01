package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public abstract class TStatement {
  public abstract void accept(Visitor v);
  public abstract TType accept(TypeVisitor v);
}
