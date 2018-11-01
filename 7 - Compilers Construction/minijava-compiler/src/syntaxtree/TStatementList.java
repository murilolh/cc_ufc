package syntaxtree;

import java.util.Vector;

public class TStatementList {
   private Vector list;

   public TStatementList() {
      list = new Vector();
   }

   public void addElement(TStatement n) {
      list.addElement(n);
   }

   public TStatement elementAt(int i)  { 
      return (TStatement)list.elementAt(i); 
   }

   public int size() { 
      return list.size(); 
   }
}
