<?php
ini_set('display_errors', 'On');
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wiltseb-db", "YIfUVOqjdS4xvfDX", "wiltseb-db");
if ($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	

#Add to villain table
$pseudonym = $_POST['pseudonym'];

$stmt = $mysqli->prepare("INSERT INTO villain(pseudonym) VALUES(?)");

if(!$stmt){
	echo "villain prepare failed: " . $stmt->errno . " " . $stmt->error;
}	
if(!($stmt->bind_param("s", $pseudonym))){
	echo "villain bind failed: " . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "villain execute failed: " . $stmt->errno . " " . $stmt->error;
}
else{
	echo "Added " . $stmt->affected_rows . " rows to villain\n";
}
$newVillainID = $stmt->insert_id; #Retrieves auto-increment ID from villain insertion
$stmt->close();


#Add to true_id_villain
if (isset($_POST['characters']))
{
  	foreach($_POST['characters'] as $character){
		if (!($stmt = $mysqli->prepare("INSERT INTO true_id_villain(true_id, villain_id) VALUES(?,?)"))) {
			echo "true_id_villain prepare failed: " . $stmt->errno . " " . $stmt->error;
		}	
		if(!($stmt->bind_param("ii", $character, $newVillainID))){
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

#Add to villain_creator
if (isset($_POST['creators']))
{
  	foreach($_POST['creators'] as $creator){
		if (!($stmt = $mysqli->prepare("INSERT INTO villain_creator(villain_id, creator_id) VALUES(?,?)"))) {
			echo "villain_creator prepare failed: " . $stmt->errno . " " . $stmt->error;
		}	
		if(!($stmt->bind_param("ii", $newVillainID, $creator))){
			echo "villain_creator bind failed: " . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "villain_creator execute failed: " . $stmt->errno . " " . $stmt->error;
		}
		else{
			echo "Added " . $stmt->affected_rows . " rows to villain_creator\n";
		}
		$stmt->close();
	}
}



?>

