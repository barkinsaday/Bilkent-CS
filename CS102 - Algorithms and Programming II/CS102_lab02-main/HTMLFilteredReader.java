/* @author: Barkýn Saday
 * @date: 210.10.2020
 * @Project: CS102_Lab02
*/
//Part D
public class HTMLFilteredReader extends MySimpleURLReader
{
   //properities
   String url = "";
   
   //consturactors
   HTMLFilteredReader( String e_url)
   {
      super(e_url);
      url = e_url;
   }
   
   //methods
   public String getPageContents()
   {
      int first_sign = 0;
      boolean first_check = false; // check if first '<' is find
         
      String filtered_Content = "";
      String str = super.getPageContents();
      
      int index_1 = 0; //index of '>'
      int index_2 = 0; //index of '<'
      //int last_index = 0;
      for( int i = 0; i < str.length() && !first_check; i++)
      {
         if(str.charAt(i) == '<')
         {
            first_sign = i;
            first_check = true; // first '<' is found
         }
      }
      
      filtered_Content = str.substring( 0, first_sign );//takes the part before the first '<' sign
      
      boolean check_1 = false; //true when new '>' is found on index_1  +1
      boolean check_2 = false; // true when new '<' is found on index_2  0
 
      for( int i = first_sign+1; i < str.length(); i++) //takes the parts between '>' and '<'
      {
         if( str.charAt(i) == '>' )
         {
            index_1 = i;
            check_1 = true;
         }
         
         if( str.charAt(i) == '<' )
         {
            index_2 = i;
            check_2 = true;
         }
         
         if( check_1 == true && check_2 == true)
         {
            filtered_Content = filtered_Content + str.substring( index_1 + 1, index_2 );
            check_1 = false;
            check_2 = false;
         }
      }
      
      if( str.length()-1 != index_1) //takes the part after the last part '>' if there are any
      {
         filtered_Content = filtered_Content + str.substring( index_1 + 1, str.length());
      }
      
      return filtered_Content;
   }
   
   public String getUnfilteredContent()
   {
      return super.getPageContents();
   }
}//end class