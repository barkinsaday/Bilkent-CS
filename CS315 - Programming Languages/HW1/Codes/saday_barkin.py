#1) Initialize
grades = {'Barkin': 95, 'Ahmet': 65, 'Ayse': 78, 'Dilruba': 100}

#2) Get Value For a Key (2 different ways)
print(grades['Barkin'])
print(grades.get('Ahmet'))

# 3)Add a New Element
grades['Artun'] = 90

#4) Remove an Element
grades.pop('Ahmet')

#5)Modify the value of an existing element
grades['Barkin'] = 100

#6) Search for the existence of a key
print('Ayse' in grades) #Should print "True"
print('Ahmet' in grades) #Should print "False"

#7) Search for the existence of a value
print(100 in grades.values()) #Should print "True"
print(0 in grades.values()) #Should print "False"

#8) Loop through an associative array (with foo() function)
def foo(lst):
    for i in lst:
        print(i, lst[i])
#Calling foo
foo(grades)