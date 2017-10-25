<?php
ini_set('display_errors', 'On');
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wiltseb-db", "YIfUVOqjdS4xvfDX", "wiltseb-db");
if ($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
$table_name = $_POST['tables'];

#Provide results based on which table was selected

if ($table_name == "true_id"){
	$stmt = $mysqli->prepare("SELECT id, first_name, last_name, status_id FROM " . $table_name);

	if(!$stmt){
		echo "true_id prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($id, $fname, $lname, $statusid)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>True Identity</td>
		</tr>
		<tr>
			<td>ID</td>
			<td>First Name</td>
			<td>Last Name</td>
			<td>Status ID</td>
		</tr>";
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $id . "\n</td>\n<td>\n" . $fname . "\n</td>\n<td>\n" . $lname . "\n</td>\n<td>\n" . $statusid . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}

else if ($table_name == "villain"){
	$stmt = $mysqli->prepare("SELECT id, pseudonym FROM " . $table_name . " GROUP BY id");

	if(!$stmt){
		echo "villain prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($id, $pseudonym)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>Villain</td>
		</tr>
		<tr>
			<td>ID</td>
			<td>Pseudonym</td>
		</tr>";
		
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $id . "\n</td>\n<td>\n" . $pseudonym . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}

else if ($table_name == "special_abilities"){
	$stmt = $mysqli->prepare("SELECT id, name, definition FROM " . $table_name);

	if(!$stmt){
		echo "special_abilities prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($id, $name, $definition)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>Special Abilities</td>
		</tr>
		<tr>
			<td>ID</td>
			<td>Name</td>
			<td>Definition</td>
		</tr>";
		
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $id . "\n</td>\n<td>\n" . $name . "\n</td>\n<td>\n" . $definition . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}
else if ($table_name == "true_id_villain"){
	$stmt = $mysqli->prepare("SELECT true_id, villain_id FROM " . $table_name);

	if(!$stmt){
		echo "true_id_villain prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($true_id, $villain_id)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>True Identity - Villain Identity</td>
		</tr>
		<tr>
			<td>True ID number</td>
			<td>Villain ID number</td>
			
		</tr>";
		
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $true_id . "\n</td>\n<td>\n"  . $villain_id . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}
else if ($table_name == "true_id_abilities"){
	$stmt = $mysqli->prepare("SELECT true_id, ability_id FROM " . $table_name);

	if(!$stmt){
		echo "true_id_abilities prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($true_id, $ability_id)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>True Identity Number - Ability Identity Number</td>
		</tr>
		<tr>
			<td>True ID number</td>
			<td>Ability ID number</td>
			
		</tr>";
		
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $true_id . "\n</td>\n<td>\n"  . $ability_id . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}

else if ($table_name == "status"){
	$stmt = $mysqli->prepare("SELECT id, description FROM " . $table_name);

	if(!$stmt){
		echo "status prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($id, $description)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>Status</td>
		</tr>
		<tr>
			<td>ID</td>
			<td>Description</td>
		</tr>";
		
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $id . "\n</td>\n<td>\n" . $description . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}
else if ($table_name == "creator_villain"){
	$stmt = $mysqli->prepare("SELECT creator_id, villain_id FROM " . $table_name);

	if(!$stmt){
		echo "creator_villain prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($creator_id, $villain_id)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>Creator - Villain</td>
		</tr>
		<tr>
			<td>Creator ID </td>
			<td>Villain ID </td>
			
		</tr>";
		
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $creator_id . "\n</td>\n<td>\n"  . $villain_id . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}

else if ($table_name == "creator"){
	$stmt = $mysqli->prepare("SELECT id, first_name, last_name, dob FROM " . $table_name);

	if(!$stmt){
		echo "creator prepare failed: " . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "execute failed:" . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->bind_result($id, $first_name, $last_name, $dob)){
		echo "bind failed:" . $stmt->errno . " " . $stmt->error;

	}
	echo "<table>
		  <tr>
			<td>Creator - Villain</td>
		</tr>
		<tr>
			<td>ID </td>
			<td>First Name </td>
			<td>Last Name </td>
			<td>Date of Birth </td>
			
		</tr>";
		
	while ($stmt->fetch()){
		echo "<tr>\n<td>\n" . $id . "\n</td>\n<td>\n"  . $first_name . "\n</td>\n<td>\n"  .  $last_name . "\n</td>\n<td>\n"  . $dob . "\n</td>\n</tr>";
	}
	echo "</table>";
	$stmt->close();
}
?>




