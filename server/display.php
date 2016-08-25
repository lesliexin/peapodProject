<html>
<head>
</head>
<body>

<?php
// Connecting
$db = mysql_connect("localhost","root","lxin2016");

// Checking if connection was made
if (!$db){
die("Can not connect: " . mysql_error());
}

// Selecting and querying database and table
mysql_select_db("test",$db);
$sql = "SELECT * FROM peapod";
$mydata = mysql_query($sql,$db);

// Creating table to display data
echo "<table border=1>
<tr>
<th>Time</th>
<th>MAC Address</th>
<th>Signal Strength</th>
</tr>";

// Printing the data into the table
while ($record = mysql_fetch_array($mydata)){
echo "<tr>";
echo "<td>" . $record['Time'] . "</td>";
echo "<td>" . $record['MAC_Address'] . "</td>";
echo "<td>" . $record['Signal_Strength'] . "</td>";
echo "</tr>";
echo "<br />";
}
echo "</table>";
mysql_close($db);

?>

</body>
</html>
