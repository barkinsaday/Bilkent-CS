--1) Initialize
grades = {['Barkin'] = 95, ['Ahmet'] = 65, ['Ayse'] = 78, ['Dilruba'] = 100}

--2) Get the value for a given key
print(grades["Barkin"])
print(grades.Ahmet)

--3) Add a new element
grades["Artun"] = 90

--4) Remove an element
grades["Ahmet"] = nil

--5) Modify the value of an existing element
grades["Barkin"] = 100

--6) Search for the existence of a key
--Search by iterating over keys
x = 'Barkin'
y = 'Ahmet'
xb = false
yb = false
for k in pairs(grades) do
    if k == x then
        xb = true
    end
    if k == y then
        yb = true
    end
end

print("Is", x, "in grades:", xb)--true
print("Is", y, "in grades:", yb)--false

--7) Search for the existence of a value
val1 = 78
val2 = 30
b_val1 = false
b_val2 = false
for k, v in pairs(grades) do
    if v == val1 then
        b_val1 = true
    end
    if v == val_2 then
        b_val2 = true
    end
end

print("Is", val1, "in grades:", b_val1)--true
print("Is", val2, "in grades:", b_val2)--false

--8) Loop through an associative array
function foo(lst)
    for k, v in pairs(lst) do
    print(k, v)
    end
end
foo(grades)