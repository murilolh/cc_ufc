package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TMethodDecl {
  public TType t;
  public TIdentifier i;
  public TFormalList fl;
  public TVarDeclList vl;
  public TStatementList sl;
  public TExp e;

  public TMethodDecl(TType at, TIdentifier ai, TFormalList afl, TVarDeclList avl, 
                    TStatementList asl, TExp ae) {
    t=at; i=ai; fl=afl; vl=avl; sl=asl; e=ae;
  }
 
  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
