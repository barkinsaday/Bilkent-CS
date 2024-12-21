/* @author: Barkýn Saday
 * @date: 210.10.2020
 * @Project: CS102_Lab02
*/
public class WordSearch extends HTMLFilteredReader
{
   //properities
   String url;
   String word;
   int count = 0;
   
   //consturactors
   WordSearch( String e_word, String e_url)
   {
      super(e_url);
      word = e_word;
      url = e_url;
      
      String str = super.getPageContents(); //str = filtered page
      for( int i = 0; i < str.length() - word.length(); i++ )
      {
         if( str.substring(i, i + word.length()).equals( word ) )
         {
            count++;
            System.out.println( "The word: " + word + " was found from indexes between: " + i + "/" + (i + word.length()) );
         }
      }
      if( count == 0 )
         System.out.println( "The word was not found" );
      else
         System.out.println( "The word: " + word + " was found " + count + " many times" );
   }
}//end class