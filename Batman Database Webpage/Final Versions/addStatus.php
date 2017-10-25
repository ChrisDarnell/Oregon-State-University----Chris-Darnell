<?php
ini_set('display_errors', 'On');
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wiltseb-db", "YIfUVOqjdS4xvfDX", "wiltseb-db");
if ($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	

#Add to status table

$stmt = $mysqli->prepare("INSERT INTO status(description) VALUES(?)");

if(!$stmt){
	echo "status prepare failed: " . $stmt->errno . " " . $stmt->error;
}	
if(!($stmt->bind_param("s", $_POST['status']))){
	echo "status bind failed: " . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "status execute failed: " . $stmt->errno . " " . $stmt->error;
}
else{
	echo "Added " . $stmt->affected_rows . " rows to status\n";
}
$stmt->close();


?>

