/*
 * @author: Barkýn Saday
 * @date: 22.12.2020
 * @project: CS102 Lab7
*/
public class SimpleQueue 
{
   private SimpleLinkedList queue;
   
   public SimpleQueue()
   {
      queue = new SimpleLinkedList();
   }
   
     public SimpleQueue(SimpleLinkedList queue)
   {
      this.queue = queue;
   }
   
   public void enqueue(String data)
   {
      queue.addToTail(data);
   }
   
   public void dequeue()
   {
      queue.removeFromHead();
   }
   
   public SimpleLinkedList getQueue()
   {
      return queue;
   }
}