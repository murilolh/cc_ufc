package syntaxtree;

import java.util.Vector;

public class TFormalList {
   private Vector list;

   public TFormalList() {
      list = new Vector();
   }

   public void addElement(TFormal n) {
      list.addElement(n);
   }

   public TFormal elementAt(int i)  { 
      return (TFormal)list.elementAt(i); 
   }

   public int size() { 
      return list.size(); 
   }
}
