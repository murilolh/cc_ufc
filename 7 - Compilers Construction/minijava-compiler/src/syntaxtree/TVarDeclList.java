package syntaxtree;

import java.util.Vector;

public class TVarDeclList {
   private Vector list;

   public TVarDeclList() {
      list = new Vector();
   }

   public void addElement(TVarDecl n) {
      list.addElement(n);
   }

   public TVarDecl elementAt(int i)  { 
      return (TVarDecl)list.elementAt(i); 
   }

   public int size() { 
      return list.size(); 
   }
}
