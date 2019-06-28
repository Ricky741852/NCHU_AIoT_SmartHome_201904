<?php

//1. Connect to database
$con = mysqli_connect("localhost","test123","test123","smarthomedb");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }else{
  	
  }


//2. Query table
$result = mysqli_query($con,"SELECT * FROM door where open_temp = 1");

//3. fectch all
$data=[];
$i=0;
while ($row=mysqli_fetch_array($result,MYSQLI_NUM)){
	$data[$i]=$row  ;	
	$i ++;
     }

//4. encode json

echo json_encode($data);

//5. close
mysqli_close($con);

//header('Location: http://localhost/test0612/index.html')
?>
