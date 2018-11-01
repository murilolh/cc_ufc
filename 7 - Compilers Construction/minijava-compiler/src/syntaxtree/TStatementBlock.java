package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TStatementBlock extends TStatement {
  public TStatementList sl;

  public TStatementBlock(TStatementList asl) {
    sl=asl;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}

