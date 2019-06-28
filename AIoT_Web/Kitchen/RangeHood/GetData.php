<?php 
	if (!empty($_GET)) {
		$num=$_GET['num'];

	} else{
		$num=1000000;
	}

//1. connect db
$host="localhost";
$user="test123";
$pwd="test123";
$dbname="smarthomedb";

/////改成大哥的資料
// $host="localhost";
// $user="nchuteam";
// $pwd="nchu2019";
// $dbname="HomeDB";

$con = mysqli_connect($host,$user,$pwd,$dbname);


// Check connection
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

//2. query table
$result=mysqli_query($con,"SELECT * FROM kitchen");
//table name "light"改成大哥的tablename: kitchen


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
//header('Location: http://localhost:80/2019aiot/myiot/20190605_CH_and_DG/show(working)_DG_hhc.html');//這一行是回傳資料
?>