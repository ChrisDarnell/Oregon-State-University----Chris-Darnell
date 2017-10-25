<?php
ini_set('display_errors', 'On');
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","wiltseb-db", "YIfUVOqjdS4xvfDX", "wiltseb-db");
if ($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
?>
<!DOCTYPE html>

 <head>
	<title>Arkham Asylum: Rogue's Gallery Database</title>
	<link rel="stylesheet" href="css/style.css">
</head>
<body>

	<div id="header">
		<h1>Arkham Asylum: Rogue's Gallery Database</h1>
	</div>
	
	
	<div id="nav"></div>

	<div>



<!-- SELECT  -->

	<form method ="post" action="select.php"> 
		<fieldset>	
			<legend>SELECT for which table to display contents </legend>
			<p>See Contents in Table: <select name="tables">

<!--Populate dropdown with all tables -->
<?php

if (!($stmt = $mysqli->prepare("show tables"))) {
	echo "prepare failed:" . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "execute failed:" . $stmt->errno . " " . $stmt->error;

}

if (!$stmt->bind_result($table_name)){
	echo "bind failed:" . $stmt->errno . " " . $stmt->error;

}
while ($stmt->fetch()){
	echo "<option value=\"" . $table_name . "\">" . $table_name . "</option>";
	

}
$stmt->close();

?>

			</select>
			</p>
			<p><input type="submit" name="getselect" value="Select"/> </p>
		</fieldset>	
	</form>





<!-- DELETE  -->


	<form method ="post" action='deleteVillain.php'> <!--CHANGE TO DELETEVILLAIN.PHP-->
		<fieldset>	
			<legend>Delete a Villain From The Database</legend>
			<p>Delete from the database: <select name='pseudonym'>

<!-- Populate dropdown with current characters in database -->			
<?php
if (!($stmt = $mysqli->prepare("SELECT id, first_name, last_name FROM true_id"))) {
	echo "prepare failed:" . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "execute failed:" . $stmt->errno . " " . $stmt->error;

}

if (!$stmt->bind_result($trueID, $fname, $lname)){
	echo "bind failed:" . $stmt->errno . " " . $stmt->error;

}
while ($stmt->fetch()){
	echo "<option value=\"" . $trueID . "\">" . $fname . " " . $lname . "</option>";
}
$stmt->close();

?>
			</select>
			</p>
			<p><input type="submit" value="Delete"/> </p>
			</fieldset>	
		</form>


<!-- SEARCH -->


		
		<form method="post" action="search.php"> 
			<fieldset>	
				<legend>SEARCH Functionality</legend>
				<p>Search for Villains who are: </p>
				<p><select name="status" /> </p>
<!--Populate dropdown with all statuses -->
<?php

if (!($stmt = $mysqli->prepare("SELECT id, description FROM status"))) {
	echo "prepare failed:" . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "execute failed:" . $stmt->errno . " " . $stmt->error;

}

if (!$stmt->bind_result($statusID, $descriptionID)){
	echo "bind failed:" . $stmt->errno . " " . $stmt->error;

}
while ($stmt->fetch()){
	echo "<option value=\"" . $statusID . "\">" . $descriptionID . "</option>";
}
$stmt->close();
?>


				<p><input type="submit" name="getsearch" value="Search"/> </p>
			</fieldset>	
		</form>


<!-- ADD  -->
		
		
		
		<form method="post" action="addVillain.php">
			<fieldset>
				<legend>ADD A New Villain Identity</legend>
				<p>True First Name (required): <input class="hideme" type="text" name="fname" /></p>
				<p>True Last Name: <input type="text" name = "lname" /> </p> 
				<p>Status: <select name="status">
<!--Populate dropdown with all statuses -->
<?php
if (!($stmt = $mysqli->prepare("SELECT id, description FROM status"))) {
	echo "prepare failed:" . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "execute failed:" . $stmt->errno . " " . $stmt->error;

}

if (!$stmt->bind_result($statusID, $statusDescription)){
	echo "bind failed:" . $stmt->errno . " " . $stmt->error;

}
while ($stmt->fetch()){
	echo "<option value=\"" . $statusID . "\">" . $statusDescription . "</option>";
}
$stmt->close();
?>
				</select> </p>	
				<p>Pseudonym:
				
<!--Populate dropdown with available villains -->
<?php

if (!($stmt = $mysqli->prepare("SELECT id, pseudonym FROM villain"))) {
	echo "prepare failed:" . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "execute failed:" . $stmt->errno . " " . $stmt->error;

}

if (!$stmt->bind_result($villainID, $pseudonym)){
	echo "bind failed:" . $stmt->errno . " " . $stmt->error;

}
while ($stmt->fetch()){
	echo "<div> <input type=checkbox value=" . $villainID . "\" name=\"pseudonyms[]\" /> ";
	echo "<label for=\"" . $villainID . "\">" . $pseudonym .  "</label> </div>";
}
$stmt->close();
?>
				</p>
					
				<p>Special Abilities: 
<!--Create a checkbox for all possible special abilities -->
<?php

if (!($stmt = $mysqli->prepare("SELECT id, name FROM special_abilities"))) {
	echo "prepare failed:" . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "execute failed:" . $stmt->errno . " " . $stmt->error;

}

if (!$stmt->bind_result($abilityID, $abilityName)){
	echo "bind failed:" . $stmt->errno . " " . $stmt->error;

}
while ($stmt->fetch()){
	echo "<div> <input type=checkbox value=" . $abilityID . "\" name=\"abilities[]\" /> ";
	echo "<label for=\"" . $abilityID . "\">" . $abilityName .  "</label> </div>";

}
$stmt->close();
?>
				</p>
				</select>
				<p><input type="submit" name="addtrueid" value="Add Villain"/> </p>
			</fieldset>
		</form>
</div>
<div id="footer"></div>
<script src="js/footer.js"></script>

</body>
</html>