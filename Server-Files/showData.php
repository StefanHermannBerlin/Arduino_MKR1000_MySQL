<!doctype html>
<html class="no-js" lang="en">
  <head>
		<META HTTP-EQUIV="refresh" CONTENT="6">
    <title>DHT22 – MKR1000</title>
		<link rel="stylesheet" href="styles.css">
  </head>
	
  <body>
		<div id="wrapper">
			<h3>DHT22 – MKR1000</h3>
			
<?php

$servername = "dbXXXXXXXXX.db.1and1.com";
$username = "dboXXXXXXXXX";
$password = 'XXXXXXXXXXXXXXXXXXXX';
$dbname = "dbXXXXXXXXX";
$dbtable = "dht001";

$conn = new mysqli($servername, $username, $password, $dbname);			// Create connection
if ($conn->connect_error) {																					// Check connection
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "select * from `".$dbtable."` order by id desc limit 1";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
      echo '
				<div class="dataWrapper">
					<div class="humidityLabel">Temperature</div>
					<div class="temperatureLabel">Humidity</div>
					<div class="humidity">'.$row["value1"].'</div>
					<div class="temperature">'.$row["value2"].'</div>
					<div class="metadata">'.$row["id"].':  '.$row["time"].'
				</div></div>';
    }
} else {
    echo "0 results";
}

$zoomlevel=1;

if ($_GET["zoomlevel"]){
	$zoomlevel=$_GET["zoomlevel"];
}

$sql = "select * from ( select * from `".$dbtable."` WHERE id mod ".$zoomlevel." = 0 order by id desc limit 800) tmp order by tmp.id asc";
//$sql = "select * from ( select * from `".$dbtable."` order by id desc limit 800) tmp order by tmp.id asc";

$result = $conn->query($sql);
echo '<div class="temperature_graph">';
echo '<span class="bar"></span>';
if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
			echo '<div class="bar2" style="height: '.intval(($row["value1"])).'px;">a</div>';
    }
} else {
    echo "0 results";
}
echo "</div>";

$result = $conn->query($sql);
echo '<div class="humidity_graph">';
echo '<span class="bar"></span>';
if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {
			echo '<div class="bar" style="height: '.intval(($row["value2"])).'px;">a</div>';			
    }
} else {
    echo "0 results";
}
echo "</div>";


echo '<div class="controlls">Zoom: 
 <a href="?zoomlevel=100">100</a>
 <a href="?zoomlevel=50">50</a>
 <a href="?zoomlevel=25">25</a>
 <a href="?zoomlevel=10">10</a>
 <a href="?zoomlevel=1">1</a>
</div>'

//mysql_close($con);
?>
	</div>
  </body>
</html>
