<?php
ini_set('display_errors', 'On');
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wiltseb-db", "YIfUVOqjdS4xvfDX", "wiltseb-db");
if ($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	

#Add to creator table
$firstName = $_POST['firstname'];
$lastName = $_POST['lastname'];
$dob = $_POST['dob'];


$stmt = $mysqli->prepare("INSERT INTO creator(first_name, last_name, dob) VALUES(?,?,?)");

if(!$stmt){
	echo "creator prepare failed: " . $stmt->errno . " " . $stmt->error;
}	
if(!($stmt->bind_param("sss", $firstName, $lastName, $dob))){
	echo "creator bind failed: " . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "creator execute failed: " . $stmt->errno . " " . $stmt->error;
}
else{
	echo "Added " . $stmt->affected_rows . " rows to creator\n";
}
$newCreatorID = $stmt->insert_id; #Retrieves auto-increment ID from creator insertion
$stmt->close();

'''
#Add to creator_villain
if (isset($_POST['vids']))
{
  	foreach($_POST['vids'] as $vid){
		if (!($stmt = $mysqli->prepare("INSERT INTO creator_villain(villain_id, creator_id) VALUES(?,?)"))) {
			echo "creator_villain prepare failed: " . $stmt->errno . " " . $stmt->error;
		}	
		if(!($stmt->bind_param("ii", $vid, $newCreatorID))){
			echo "creator_villain bind failed: " . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "creator_villain execute failed: " . $stmt->errno . " " . $stmt->error;
		}
		else{
			echo "Added " . $stmt->affected_rows . " rows to creator_villain\n";
		}
		$stmt->close();
	}
}
'''


?>