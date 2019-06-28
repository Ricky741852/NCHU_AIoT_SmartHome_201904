<!DOCTYPE html>
<html lang="en">

<head>

  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <meta name="description" content="">
  <meta name="author" content="">

  <title>Smart Home｜IR</title>

  <!-- Custom fonts for this template-->
  <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
  <link href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i" rel="stylesheet">

  <!-- Custom styles for this template-->
  <link href="css/sb-admin-2.min.css" rel="stylesheet">

  <!-- ICON -->
  <link rel="icon" type="image/png" href="./img/icons/house.ico"/> 

  <!--IR CDN===============-->
  

  <!--IR CDN end============-->
  
</head>

<body id="page-top">

  <!-- Page Wrapper -->
  <div id="wrapper">

    <!-- Sidebar 側欄-->
    <ul class="navbar-nav bg-gradient-primary sidebar sidebar-dark accordion" id="accordionSidebar">

      <!-- Sidebar - Brand -->
      <a class="sidebar-brand d-flex align-items-center justify-content-center" href="index.html">
        <div class="sidebar-brand-icon rotate-n-15">
          <i class="fas fa-home"></i>
        </div>
        <div class="sidebar-brand-text mx-3">SMART HOME</div>
      </a>

      <!-- Divider 分隔線-->
      <hr class="sidebar-divider my-0">

      <!-- Nav Item - 楷屏 門禁 (nav-item後面加active字體會變粗)-->
      <li class="nav-item">
        <a class="nav-link" href="AccessControl.php">
          <i class="fas fa-fw fa-door-open"></i>
          <span>Access Control</span></a>
      </li>

      <!-- Divider 分隔線 -->
      <!-- <hr class="sidebar-divider"> -->

      <!-- Nav Item - 瑞奇 Bathroom -->
      <li class="nav-item">
        <a class="nav-link" href="Bathroom.php">
          <i class="fas fa-fw fa-toilet"></i>
          <span>Bathroom</span></a>
      </li>

      <!-- Nav Item - 曉慧/湘惟 kitchen Collapse Menu -->
      <li class="nav-item">
        <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseTwo" aria-expanded="true" aria-controls="collapseTwo">
          <i class="fas fa-fw fa-utensils"></i>
          <span>Kitchen</span>
        </a>
        <div id="collapseTwo" class="collapse" aria-labelledby="headingTwo" data-parent="#accordionSidebar">
          <div class="bg-white py-2 collapse-inner rounded">
            <!-- <h6 class="collapse-header">Custom Components:</h6> -->
            <a class="collapse-item" href="FireGasAlarm.html">Fire & Gas Alarm</a>
            <a class="collapse-item" href="RangeHood.html">Range Hood</a>
          </div>
        </div>
      </li>

      <!-- Nav Item - 菜/大哥 IR  -->
      <li class="nav-item">
        <a class="nav-link" href="IR_v2.php">
          <i class="fas fa-fw fa-mobile-alt"></i>
          <span>Remote Control</span></a>
      </li>

      <!-- Divider -->
      <hr class="sidebar-divider d-none d-md-block">

      <!-- Sidebar Toggler (Sidebar) -->
      <div class="text-center d-none d-md-inline">
        <button class="rounded-circle border-0" id="sidebarToggle"></button>
      </div>

    </ul>
    <!-- End of Sidebar -->

    <!-- Content Wrapper -->
    <div id="content-wrapper" class="d-flex flex-column">

      <!-- ==================Main Content 內容放這裡=========================-->
      <div id="content">
        <div id="container-fluid">
          <div class="row">
            <div class="col-xl-4 col-lg-4"></div>
            <div class="col-xl-4 col-lg-4">
              <div class="card shadow mb-4">
                <div class="card-header py-3">
                  <h3 class="m-0 font-weight-bold text-primary text-center">Remote Control</h3>
                </div>
                <div class="card-body">
                 <?php

                 $ir_data=array();
                 $ir_name=array();

                    if (!empty($_GET))
                    {
                     $a=$_GET['g'];

                     $host="localhost";
                     $user="test123";
                     $pwd="test123";
                     $dbname="smarthomedb";
                     $con = mysqli_connect($host,$user,$pwd,$dbname);
                     // Check connection
                     if (mysqli_connect_errno())
                     {
                      echo "Failed to connect to MySQL: " . mysqli_connect_error();
                     }
                     // 2. query table
                     $result=mysqli_query($con,"SELECT * FROM IRData");
                     $i=0;
                     while ($row=mysqli_fetch_array($result,MYSQLI_NUM)) 
                      {
                        $ir_data[$i]=$row[4];
                        $ir_name[$i]=$row[2];
                        //echo $ir_data[$i]."<br>"; 
                        //echo $ir_name[$i]."<br>";        
                        $i++;
                      }
                     mysqli_close($con);           
                     // $j=0;
                     // for ($j=0;$j<$i;$j++)
                     // {
                     //  $b="http://".$a."/?val=".$ir_data[$j]."&321";
                     //       // echo "<button type=\"button\" class=\"btn btn-primary\" //onclick=\"document.location.href='$b'\">Add a Data To Door</button>";
                     
                     //  $c="<a target=\"new\" href=".$b." class=\"button\">$ir_name[$j]</a>";
                     //  if (($j+1)%2==0) $d=$c."<br><br>";
                     //  else $d="&nbsp".$c."&nbsp&nbsp";
                     //  echo $d;


                      echo " <div class='text-center'><form  action='' >
                      <select autofocus class='d-none d-sm-inline-block btn btn-sm btn-primary shadow-sm' name='people' onchange='showCustomer(this.value)'>
                    　<option value='1'> &nbsp&nbsp&nbsp T &nbsp V &nbsp&nbsp&nbsp </option>
                    　<option value='2'> &nbsp&nbsp&nbsp A &nbsp V &nbsp&nbsp&nbsp </option>
                    　<option value='3'> &nbsp&nbsp&nbsp A &nbsp I &nbsp R &nbsp&nbsp&nbsp </option>
                      </select>
                    </form></div><div> &nbsp</div>";
                    echo "<div class='text-center'><button type='button' class='btn btn-primary'>ON</button>";
                    echo "&nbsp &nbsp<button type='button' class='btn btn-secondary'>OFF</button></div>";
                    // $b1="http://".$a."/?val=268261541&321";
                    // $c1="<a target=\"new\" href=".$b1.">RUN OFF </a><br>";
                    // echo $c,$c1; 
                     // }

                    }
                    else
                    {
                     echo "<form method = 'get' action = 'IR_v2.php'><h6 class='text-center'>Please Enter IP Address</h6><br>";   
                     echo "<div class='text-center'><input type = 'text' name = g>";
                     echo "&nbsp &nbsp<button type = 'submit'  name = 'submit' class='btn btn-success btn-circle btn-lg'> 
                    <i class='fas fa-check'></i></button></div></form>";
                    }
                 ?>
                </div>  
              </div> 
            </div>
            <div class="col-xl-4 col-lg-4"></div>
          </div>
        </div>
      </div>
      <!-- ===================End of Main Content ==========================-->

            <!-- Footer 版權字樣 (sticky-footer後面加bg-white背景變白色)-->
      <footer class="sticky-footer">
        <div class="container my-auto">
          <div class="copyright text-center my-auto">
            <span>Copyright &copy; IOT Website 2019</span>
          </div>
        </div>
      </footer>
      <!-- End of Footer -->

    </div>
    <!-- End of Content Wrapper -->

  </div>
  <!-- End of Page Wrapper -->

  <!-- Scroll to Top Button-->
  <a class="scroll-to-top rounded" href="#page-top">
    <i class="fas fa-angle-up"></i>
  </a>

  <!-- Bootstrap core JavaScript-->
  <script src="vendor/jquery/jquery.min.js"></script>
  <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

  <!-- Core plugin JavaScript-->
  <script src="vendor/jquery-easing/jquery.easing.min.js"></script>

  <!-- Custom scripts for all pages-->
  <script src="js/sb-admin-2.min.js"></script>

  <!-- Page level plugins -->
  <script src="vendor/chart.js/Chart.min.js"></script>

  <!-- Page level custom scripts -->
  <script src="js/demo/chart-area-demo.js"></script>
  <script src="js/demo/chart-pie-demo.js"></script>

</body>

</html>
