<!-- SEARCH -->

<?php
ini_set('display_errors', 'On');
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wiltseb-db", "YIfUVOqjdS4xvfDX", "wiltseb-db");
if ($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

	
#Get all people - Left Join required to join true_id to abilities and villains
$sql = "SELECT t.id, t.first_name, t.last_name, v.id, v.pseudonym, a.id, a.name, s.description
FROM true_id t
LEFT JOIN true_id_villain tiv ON tiv.true_id = t.id
LEFT JOIN villain v ON v.id = tiv.villain_id
LEFT JOIN status s ON s.id = t.status_id
LEFT JOIN true_id_abilities tia ON tia.true_id = t.id
LEFT JOIN special_abilities a ON a.id = tia.ability_id
WHERE s.id =?
GROUP BY t.first_name, t.id, v.id, a.id";


if($query = $mysqli->prepare($sql)) { 
    $query->bind_param("i", $_POST['status']);
    $query->execute();
    $query->bind_result($id, $fname, $lname, $vid, $pseudo, $aid, $name, $descrip);
	
    
	echo "<table border='1'>
	  <tr>
		<th>Results:</th>
	</tr>
	<tr>
		<th>True ID</th>
		<th>First Name</th>
		<th>Last Name</th>
		<th>Villain Identity</th>
		<th>Special Abilities</th>
		<th>Status</th>
	</tr>";
	$lastID = null;
	$lastAbilityID = null;
	$lastAbilityName = null;
	$lastVillainID = null;
	
	
	#$idarray = mysql_fetch_array($id);
	#echo $idarray;
	// '''
     while (mysqli_stmt_fetch($query)) {
		
		
		if ($id == $lastID){
			if ($aid != $lastAbilityID && $vid != $lastVillainID){
				echo "<tr><td></td><td></td><td>" . $vid . "</td><td>" . $name . "</td><td></td></tr>";
			}
			else if ($aid != $lastAbilityID){
				echo "<tr><td></td><td></td><td>" . $vid . "</td><td>" . $name . "</td><td></td></tr>";
			}
			else if ($vid != $lastVillainID){
				echo "<tr><td></td><td></td><td>" . $vid . "</td><td>" . $name . "</td><td></td></tr>";
			}
		}
		else{

			echo "<tr>\n<td>\n" . $id . "\n</td>\n<td>\n" . $fname . "\n</td>\n<td>\n" .  $lname . "\n</td>\n<td>\n" . $pseudo . "\n</td>\n<td>\n" . $name . "\n</td>\n<td>\n" . $descrip . "\n</td>\n</tr>"; 
		}
		
		$lastID = $id;
		$lastAbilityID = $aid;
		$lastVillainID = $vid;
	}

}
  
 else {
    $error = $mysqli->errno . ' ' . $mysqli->error;
    echo $error; 
}



?>
