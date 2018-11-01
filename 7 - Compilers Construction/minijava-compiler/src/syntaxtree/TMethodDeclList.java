package syntaxtree;

import java.util.Vector;

public class TMethodDeclList {
   private Vector list;

   public TMethodDeclList() {
      list = new Vector();
   }

   public void addElement(TMethodDecl n) {
      list.addElement(n);
   }

   public TMethodDecl elementAt(int i)  { 
      return (TMethodDecl)list.elementAt(i); 
   }

   public int size() { 
      return list.size(); 
   }
}
