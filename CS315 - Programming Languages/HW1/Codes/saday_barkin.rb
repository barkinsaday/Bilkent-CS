#1) Initialize
grades = {"Barkin" => 95, "Ahmet" => 65, "Ayse" => 78, "Dilruba" => 100}

#2) Get the value for a given key
puts 'Barkins grade is ' + grades['Barkin'].to_s

#3)Add a new element
grades['Artun'] = 90

#4)Remove an element
grades.delete('Ahmet')

#5) Modify the value of an existing element
grades['Barkin'] = 100

#6) Search for the existence of a key
puts grades.key?('Barkin') #Should print "true"
puts grades.key?('Ahmet') #Should print "false"

#7) Search for the existence of a value
puts grades.value?(78) #Should print "true"
puts grades.value?(30) #Should print "false"

#8)Loop through an associative array
def foo(lst)
  lst.each do |k, v|
    puts "Name: #{k}, Grade: #{v}"
  end
end
foo(grades)