/*
 * @author: Barkýn Saday
 * @date: 22.12.2020
 * @project: CS102 Lab7
*/
public class SimpleLinkedList
{
   //properities
   private Node head;
   
   //consturactors
   public SimpleLinkedList()
   {
      head = null;
   }
   
   //methods 
   public void addToTail(String data)
   {
      Node newNode = new Node(data);
      Node temp = head;
      if(head == null)
         head = newNode;
      else
      {
         while( temp.getNext() != null)
            temp = temp.getNext();
         temp.setNext(newNode);
      }
   }
   
   public String removeFromHead() {
      if ( !isEmpty()) {
         head = head.getNext();
         return toString();
      }
      else  
         return "List is empty!";
   }
   
   public String toString()
   {
      String result = "";
      int counter = 1;
      Node temp = head;
      if(head == null)
         result = "List is empty";
      else
      {
         while(temp.getNext() != null)
         {
            result = result + " Data " + counter + ": " + temp.getData() + ", ";
            temp = temp.getNext();
            counter++;
         }
         result = result + "Data " + counter + ": " + temp.getData();
      }
      return result;
   }
   
   public Node get(String data)
   {
      Node temp = head;
      while(temp != null)
      {
         if( (temp.getData()).equals(data) )
            return temp;
         temp = temp.getNext();
      }
      return null;
   }
   
   public boolean isEmpty()
   {
      if(head == null)
         return true;
      return false;
   }
   
   public String getData()
   {
      return head.getData();
   }
   
   public Node getHead()
   {
      return head;
   }
}//end class

 /*public void addToHead(Node newNode)
   {
      Node temp = head;
      head = newNode;
      newNode.setNext(temp);
   }*/