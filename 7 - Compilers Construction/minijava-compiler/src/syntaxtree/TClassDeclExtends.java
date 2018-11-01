package syntaxtree;
import visitor.TypeVisitor;
import visitor.Visitor;

public class TClassDeclExtends extends TClassDecl {
  public TIdentifier i;
  public TIdentifier j;
  public TVarDeclList vl;  
  public TMethodDeclList ml;
 
  public TClassDeclExtends(TIdentifier ai, TIdentifier aj, 
                  TVarDeclList avl, TMethodDeclList aml) {
    i=ai; j=aj; vl=avl; ml=aml;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public TType accept(TypeVisitor v) {
    return v.visit(this);
  }
}
