package syntaxtree;

import java.util.Vector;

public class TExpList {
   private Vector list;

   public TExpList() {
      list = new Vector();
   }

   public void addElement(TExp n) {
      list.addElement(n);
   }

   public TExp elementAt(int i)  { 
      return (TExp)list.elementAt(i); 
   }

   public int size() { 
      return list.size(); 
   }
}
