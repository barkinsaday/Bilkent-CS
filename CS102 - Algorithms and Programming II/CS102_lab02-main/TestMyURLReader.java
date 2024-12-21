import cs1.SimpleURLReader;
/* @author: Barkýn Saday
 * @date: 210.10.2020
 * @Project: CS102_Lab02
*/
//Part A
public class TestMyURLReader
{
   public static void main(String[] args)
   {
      SimpleURLReader testing_reader = new SimpleURLReader( "http://www.cs.bilkent.edu.tr/~ozturk/cs102/housman.txt" );
      System.out.println( testing_reader.getPageContents() );
      System.out.println( "The number of lines: " + testing_reader.getLineCount());
   }
}