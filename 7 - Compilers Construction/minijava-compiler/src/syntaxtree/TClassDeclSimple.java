package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TClassDeclSimple extends TClassDecl {
  public TIdentifier i;
  public TVarDeclList vl;  
  public TMethodDeclList ml;
 
  public TClassDeclSimple(TIdentifier ai, TVarDeclList avl, TMethodDeclList aml) {
    i=ai; vl=avl; ml=aml;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
