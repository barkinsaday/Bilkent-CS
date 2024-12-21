import cs1.SimpleURLReader;
/* @author: Barkýn Saday
 * @date: 210.10.2020
 * @Project: CS102_Lab02
*/
//Part B
public class MySimpleURLReader extends SimpleURLReader
{
   //properities
   String url = "";
   
   //consturactors
   MySimpleURLReader( String e_url )
   {
      super( e_url );
      url = e_url;
   }
   
   //methods
   
   public String getURL()
   {
      return this.url;
   }
   
   public String getName()
   {
      String url_Name = "";
      char stop = '/';
      boolean done = false;
      for( int i = url.length()-1; i >= 0 && !done; i-- )
      {
         if( url.charAt(i) == stop )
         {
            url_Name = url.substring( i+1 ); 
            done = true;
         }
      }
      return url_Name; 
   }
   
   public int getNumberOfCSSLinks()
   {
      String temp = super.getPageContents();
      int result = 0;
      String css = "stylesheet";
      for( int i = 0; i < temp.length() - 10; i++)
      {
         if( temp.substring(i, i+10).equals( css ))
            result = result + 1;
      }
      return result;
   }
}//end class