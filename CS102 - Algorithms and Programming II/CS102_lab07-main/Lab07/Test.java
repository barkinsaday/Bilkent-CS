/*
 * @author: Barkýn Saday
 * @date: 22.12.2020
 * @project: CS102 Lab7
 */
public class Test
{
   public static void main(String args[] )
   {
      SimpleLinkedList test = new SimpleLinkedList();
      
      test.addToTail("Hi");
      test.addToTail("Merhaba");
      test.addToTail("Hallo");
      test.addToTail("Bonjour");
      test.addToTail("Hola!!!");
      
      System.out.println( test.toString() );
      System.out.println(test.removeFromHead());   
   }
}//end class