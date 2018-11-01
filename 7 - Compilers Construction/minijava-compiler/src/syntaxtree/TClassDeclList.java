package syntaxtree;

import java.util.Vector;

public class TClassDeclList {
   private Vector list;

   public TClassDeclList() {
      list = new Vector();
   }

   public void addElement(TClassDecl n) {
      list.addElement(n);
   }

   public TClassDecl elementAt(int i)  { 
      return (TClassDecl)list.elementAt(i); 
   }

   public int size() { 
      return list.size(); 
   }
}
