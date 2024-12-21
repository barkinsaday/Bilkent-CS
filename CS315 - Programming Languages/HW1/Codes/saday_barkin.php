<!DOCTYPE html>
<html>
<body>

<?php
echo "<br>";
#1) Initialize
$grades = array("Barkin" => 95, "Ahmet" => 65, "Ayse" => 78, "Dilruba" => 100);

#2) Get the value for a given key
echo "Barkin's grade is $grades[Barkin]";
echo "<br>";

#3) Add a new element
$grades['Artun'] = 90;

#4) Remove an element
unset($grades['Ahmet']);

#5) Modify the value of an existing element
$grades['Barkin'] = 100;

#6) Search for the existence of a key
if(array_key_exists('Barkin', $grades)){
	echo "Barkin is in grades";
    echo "<br>";
}    

else{
	echo "Barkin is not in grades";
    echo "<br>";
}    
    
if(array_key_exists('Ahmet', $grades)){
	echo "Ahmet is in grades";
    echo "<br>";
}    

else{
	echo "Ahmet is not in grades";
    echo "<br>";
}    

#7) Search for the existence of a value
$x = 78;
$y = 30;
$is_x = "No";
$is_y = "No";
foreach($grades as $key => $val){
	if($val == $x)
    	$is_x = "Yes";
    if($val == $y)
    	$is_y = "Yes";
}
echo "Is $x in grades: $is_x";
echo "<br>";
echo "Is $y in grades: $is_y";
echo "<br>";

#8) Loop through an associative array
function foo($lst){
	foreach($lst as $key => $val){
		echo "Key: $key, Value: $val";
    	echo "<br>";
	}
}
foo($grades);
?>

</body>
</html>