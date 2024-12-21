use std::collections::HashMap;
fn main() {
    //1) Initialize
    let mut grades: HashMap<&str, i32> = [("Barkin", 95), ("Ahmet", 65), ("Ayse", 78), ("Dilruba", 100)].into_iter().collect();
    
    //2) Get the value for a given key
    println!("Barkin has the grade: {:?}", grades["Barkin"]);
    
    //3) Add a new element
    grades.insert( "Artun", 90 );
    
    //4) Remove an element
    grades.remove("Ahmet");
    
    //5)Modify the value of an existing element
     grades.insert( "Barkin", 100 );
     
     //6) Search for the existence of a key
     println!("{}", grades.contains_key("Barkin")); //Should print "true"
     println!("{}", grades.contains_key("Ahmet")); //Should print "false"
     
     //7) Search for the existence of a value
     let x = 100 as i32;
     let y = 30 as i32;
     
     let bool_x = grades.values().any(|v| v ==  &x );
     let bool_y = grades.values().any(|v| v ==  &y );
     println!("{:?}", bool_x); //Should print "true"
     println!("{:?}", bool_y); //Should print "false"
    
     //8) Loop through an associative array
     for(k, v) in &grades{
        println!("{}: {}", k, v);
     }
}