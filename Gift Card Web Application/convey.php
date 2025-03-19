<?php

$DBServerName = "localhost";
$DBUserName = "root";
$DBPassword = "";
$DBName = "giftcard";

$conn = mysqli_connect($DBServerName, $DBUserName, $DBPassword, $DBName);

if(isset($_GET['block']) || isset($_GET['color']) || isset($_GET['audio'])){
	$update = array(
	     "block" => (isset($_GET['block'])) ? $_GET['block'] : "default",
		 "color" => (isset($_GET['color'])) ? $_GET['color'] : "default",
		 "audio" => (isset($_GET['audio'])) ? $_GET['audio'] : "default"
	);
	
	$sql = "UPDATE `giftcard` SET `block`='".$update['block']."', `color`='".$update['color']."', `audio`='".$update['audio']."' WHERE 1";
	mysqli_query($conn, $sql);
	
}else if(isset($_GET['print'])){
	$data = [];
	
	$sql = "SELECT * FROM `giftcard` WHERE 1";
	$result = mysqli_query($conn, $sql);
	if($row = mysqli_fetch_assoc($result)){
		$data = array(
		    "block" => $row['block'],
			"color" => $row['color'],
			"audio" => $row['audio']
		);
	}
	
	echo json_encode($data);
}

?>