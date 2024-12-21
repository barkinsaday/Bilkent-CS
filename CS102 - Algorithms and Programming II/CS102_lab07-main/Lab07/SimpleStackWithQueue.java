/*
 * @author: Barkýn Saday
 * @date: 22.12.2020
 * @project: CS102 Lab7
*/
public class SimpleStackWithQueue
{
   SimpleQueue q1;
   SimpleQueue q2;
   
   public SimpleStackWithQueue()
   {
      q1 = new SimpleQueue();
      q2 = new SimpleQueue();
   }
   
   public SimpleStackWithQueue( SimpleLinkedList q1, SimpleLinkedList q2)
   {
      this.q1 = new SimpleQueue( q1);
      this.q2 = new SimpleQueue( q1);
   }
   
   public void push(String data)
   {
      SimpleLinkedList list1 = q1.getQueue();
      SimpleLinkedList list2 = q2.getQueue();
      q2.enqueue(data);
      
      while( list1.isEmpty() != true )
      {
         list2.addToTail( list1.getData());//pushes the head data to q2
         list1.removeFromHead();// removes the head from q2 so the data is updated 
      }
   }
   
   public String toString()
   {
      SimpleLinkedList list1 = q1.getQueue();
      SimpleLinkedList list2 = q2.getQueue();
      String str_q1 = "";
      String str_q2 = "";
      String result = "";
      
      Node temp = list1.getHead();
      
      //for q1
      if(temp == null)
         str_q1 = "empty";
      else
      {
         while(temp.getNext() != null)
         {
            str_q1 = str_q1 + temp.getData() + ", ";
            temp = temp.getNext();
         }
         str_q1 = str_q1 + temp.getData();
      }
      
      //for q2
      temp = list2.getHead();
      if(temp == null)
         str_q2 = "empty";
      else
      {
         while(temp.getNext() != null)
         {
            str_q2 = str_q2 + temp.getData() + ", ";
            temp = temp.getNext();
         }
         str_q2 = str_q2 + temp.getData();
      }
      
      result = "Queue1: " + str_q1 +"\n" + "Queue2: " + str_q2;
      return result;
   }
}//end class