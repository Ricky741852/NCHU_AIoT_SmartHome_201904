<!DOCTYPE html>
<html lang="en">

<head>

  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
  <meta name="description" content="">
  <meta name="author" content="">

  <title>Smart Home｜Access Control</title>

  <!-- Custom fonts for this template-->
  <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
  <link href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i" rel="stylesheet">

  <!-- Custom styles for this template-->
  <link href="css/sb-admin-2.min.css" rel="stylesheet">

  <!-- ICON -->
  <link rel="icon" type="image/png" href="./img/icons/house.ico"/> 

    <!--楷屏 門禁 chart 回家時間-->
  <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
  <script src="https://code.highcharts.com/highcharts.js"></script>    <script src="https://code.highcharts.com/modules/exporting.js"></script>
  <script src="https://code.highcharts.com/modules/export-data.js"></script>
  <!--楷屏 門禁 chart end-->

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
    <div id="content-wrapper" class="d-flex flex-column" >

      <!-- ==================Main Content 內容放這裡=========================-->
      <div id="content" >
        
      <!-- ========= -->
          <div class="container-fluid">
          <!-- Page Heading -->
            <div class="d-sm-flex align-items-center justify-content-between mb-4">
              
            </div>
          <!-- End Page Heading -->

          <!-- Content Row -->
          <div class="row">


            

            <!-- Pending Requests Card Example -->
            <div class="col-xl-3 col-md-6 mb-4">
              <div class="card border-left-warning shadow h-100 py-2">
                <div class="card-body">
                  <div class="row no-gutters align-items-center">
                    <div class="col-auto">
                      <img class="fas  fa-2x text-gray-300" src="./img/icons/tissue.png" alt="Mother" title="Mother" width="100%">
                    </div>
                    <div class="col mr-2">
                      <div class="text-xs font-weight-bold text-warning text-uppercase mb-1">&emsp;Tissue Used: 
                                  <?php
                                  //1. Connect to database
                                  $con = mysqli_connect("localhost","test123","test123","smarthomedb");
                                  if (mysqli_connect_errno())
                                    {
                                    echo "Failed to connect to MySQL: " . mysqli_connect_error();
                                    }
                                  //2. Query table
                                  $result= mysqli_query($con,"SELECT * FROM Paper");
                                  //3. fectch all
                                  $num = mysqli_num_rows($result);
                                  echo $num;
                                  mysqli_close($con);
                                ?>
                      </div>
                      <div class="h5 mb-0 font-weight-bold text-gray-800"></div>
                    </div>
                    
                  </div>
                </div>
              </div>
            </div>
          </div>

          <!-- Content Row -->

          <div class="row">

            <!-- Area Chart -->
            <div class="col-xl-12 col-lg-7">
              <div class="card shadow mb-4">
                <!-- Card Header - Dropdown -->
                <div class="card-header py-3 d-flex flex-row align-items-center justify-content-between">
                  <h6 class="m-0 font-weight-bold text-primary">Health Analysis</h6>
                  <form  action="" >
                    <select autofocus class="d-none d-sm-inline-block btn btn-sm btn-primary shadow-sm" id="people" >
                    　<option value ="1">Dad</option>
                      <option value ="2">Mom</option>
                      <option value ="3">Brother</option>
                      <option value ="4">Sister</option>
                    </select>
                  </form>
                  <!-- <div class="dropdown no-arrow">
                    <a class="dropdown-toggle" href="#" role="button" id="dropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                      <i class="fas fa-ellipsis-v fa-sm fa-fw text-gray-400"></i>
                    </a>
                    <div class="dropdown-menu dropdown-menu-right shadow animated--fade-in" aria-labelledby="dropdownMenuLink">
                      <div class="dropdown-header">Dropdown Header:</div>
                      <a class="dropdown-item" href="#">Action</a>
                      <a class="dropdown-item" href="#">Another action</a>
                      <div class="dropdown-divider"></div>
                      <a class="dropdown-item" href="#">Something else here</a>
                    </div>
                  </div> -->
                </div>
                <!-- Card Body -->
                <div class="card-body">
                  <div class="chart-area">
                    <div id="container" style="min-width: 100%; height: 100%; margin: 0 auto"></div>
                    <script type="text/javascript" src="./Bathroom/health.js"></script>               
                  </div>
                </div>
              </div>
            </div>

            <!-- Pie Chart -->
           
          </div>

          <!-- Content Row -->
  

        </div>
    
      <!-- ========= -->        


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
