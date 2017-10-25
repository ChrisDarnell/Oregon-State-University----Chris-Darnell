<?php
ini_set('display_errors', 'On');
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wiltseb-db", "YIfUVOqjdS4xvfDX", "wiltseb-db");
if ($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	

#Add to true_id table
$firstName = $_POST['fname'];
$lastName = $_POST['lname'];

$stmt = $mysqli->prepare("INSERT INTO true_id(first_name, last_name, status_id) VALUES(?,?,?)");

if(!$stmt){
	echo "true_id prepare failed: " . $stmt->errno . " " . $stmt->error;
}	
if(!($stmt->bind_param("ssi", $_POST['fname'], $_POST['lname'], $_POST['status']))){
	echo "true_id bind failed: " . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "true_id execute failed: " . $stmt->errno . " " . $stmt->error;
}
else{
	echo "Added " . $stmt->affected_rows . " rows to true_id\n";
}
$newTrueID = $stmt->insert_id; #Retrieves auto-increment ID from true_id insertion
$stmt->close();


#Add to true_id_villain
if (isset($_POST['pseudonyms']))
{
  	foreach($_POST['pseudonyms'] as $pseudonym){
		if (!($stmt = $mysqli->prepare("INSERT INTO true_id_villain(true_id, villain_id) VALUES(?,?)"))) {
			echo "true_id_villain prepare failed: " . $stmt->errno . " " . $stmt->error;
		}	
		if(!($stmt->bind_param("ii", $newTrueID, $pseudonym))){
			echo "true_id_villain bind failed: " . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "true_id_villain execute failed: " . $stmt->errno . " " . $stmt->error;
		}
		else{
			echo "Added " . $stmt->affected_rows . " rows to true_id_villain\n";
		}
		$stmt->close();
	}
}

#Add to true_id_abilities
if (isset($_POST['abilities']))
{
  	foreach($_POST['abilities'] as $ability){
		if (!($stmt = $mysqli->prepare("INSERT INTO true_id_abilities(true_id, ability_id) VALUES(?,?)"))) {
			echo "true_id_abilities prepare failed: " . $stmt->errno . " " . $stmt->error;
		}	
		if(!($stmt->bind_param("ii", $newTrueID, $ability))){
			echo "true_id_abilities bind failed: " . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "true_id_abilities execute failed: " . $stmt->errno . " " . $stmt->error;
		}
		else{
			echo "Added " . $stmt->affected_rows . " rows to true_id_abilities\n";
		}
		$stmt->close();
	}
}



?>

