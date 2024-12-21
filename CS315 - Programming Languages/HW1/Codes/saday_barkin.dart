void main() {
  //1) Initialize
  var grades = {'Barkin': 95, 'Ahmet': 65, 'Ayse': 78, 'Dilruba': 100};
  
  //2) Get the value for a given key
  print(grades['Barkin']);
  
  //3) Add a new element
  grades['Artun'] = 90;
  
  //4) Remove an element
  grades.remove('Ahmet');
  
  //5) Modify the value of an existing element
  grades['Barkin'] = 100;
  
  //6) Search for the existence of a key
  print(grades.containsKey('Barkin'));//Should print "true"
  print(grades.containsKey('Ahmet'));//Should print "false"
  
  // 7)Search for the existence of a value
  print(grades.containsValue(30));//Should print "false"
  print(grades.containsValue(78));//Should print "true"
  
  //8) Loop through an associative array
  //Declaring function
  void foo(lst){
    lst.forEach((k, v) => print("$k: $v"));
  }
  
  //Calling foo
  foo(grades);
}