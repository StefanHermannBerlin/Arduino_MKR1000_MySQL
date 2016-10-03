<?php

$servername = "dbXXXXXXXXX.db.1and1.com";
$username = "dboXXXXXXXXX";
$password = 'XXXXXXXXXXXXXXXXXXXX';
$dbname = "dbXXXXXXXXX";
$dbtable = "dht001";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 


if ($_GET["value1"]){
	echo "<h3>New Data</h3>";
	echo 'Value1: ' .htmlspecialchars($_GET["value1"]).' Value2: '.htmlspecialchars($_GET["value2"]).'</br>';
	$sql = "INSERT INTO `".$dbtable."` (value1, value2) VALUES ('".$_GET["value1"]."','".$_GET["value2"]."')";
	
	if ($conn->query($sql) === TRUE) {
	    echo "New record created successfully";
	} else {
	    echo "Error: " . $sql . "<br>" . $conn->error;
	}
	
    echo "0 results";
}