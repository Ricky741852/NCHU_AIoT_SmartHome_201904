<?php
$people = $_GET['people'];
echo $people;
//1. Connect to database
$con = mysqli_connect("localhost","test123","test123","smarthomedb");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }else{
    echo " successfully";
  }

//2. Query table
  for ($i=1; $i <=684 ; $i++) { 
  	mysqli_query($con,"UPDATE door SET  open_temp = 0 WHERE id=$i");

  }
mysqli_query($con,"UPDATE door SET  open_temp = 1 WHERE open=$people");

//3. close
mysqli_close($con);
// header('Location: http://localhost/test0612/index.html')

?>
