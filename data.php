<?php
include ('connection.php');
$sql_insert = "INSERT INTO data (temperature, humidity, heat_index, nilai_adc, tegangan, arus) VALUES ('".$_GET["temperature"]."', '".$_GET["humidity"]."', '".$_GET["heat_index"]."', '".$_GET["nilai_adc"]."', '".$_GET["tegangan"]."', '".$_GET["arus"]."')";
if(mysqli_query($con,$sql_insert))
{
echo "Done";
mysqli_close($con);
}
else
{
echo "error is ".mysqli_error($con );
}
?>