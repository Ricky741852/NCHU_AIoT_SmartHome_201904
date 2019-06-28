<?php 
	if (!empty($_GET)) {
		$people=$_GET['id'];

	} else{
		$people=1;
	}
	
//1. connect db
$con = mysqli_connect("localhost","test123","test123","smarthomedb");

// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

//2. query table
$result=mysqli_query($con,"SELECT * FROM health WHERE people = $people");


//3. fectch all
$data=[];
$i=0;
while ($row=mysqli_fetch_array($result,MYSQLI_NUM)){
	$data[$i]=$row;
	$i++;
}

//4. encode json
echo json_encode($data);

//5. close

mysqli_close($con);
//header('Location: http://localhost:8080/aIot/show(ok).html');//這一行是回傳資料
?>