	var valueKTemp=[];
	var valueKWet=[];
	var times=[];
	var dateAndTime=[];
	
    $(document).ready(function() 
	{
	
    //一開始看到的畫面//////////////////////
		$.ajax(
		 {  type:"GET",  
			url:"./Kitchen/RangeHood/GetData.php",
			datatype: "json", 
			contentType: "application/json", 
			data:"",//"id=1",  //Ricky的php第一段可以選擇id，但是我的不需要

		   success:function(data)
		   {
			  valueKTemp = [];
			  valueKWet = [];
			  dateAndTime = [];
		   // alert(data);
			  data=$.parseJSON(data);
		   //  alert(data.length);
		   //  alert(data[1][2]);
		   	  length = data.length;

			 for (var i=length-30;i<data.length;i++)
			 {
			  valueKTemp.push(parseInt(data[i][2]));
			  valueKWet.push(parseInt(data[i][3]));
			  //alert(value[i]);

			  dateAndTime.push(data[i][1]);
			 }
		   //  alert(value);
			 // for(var i=0;i<data.length;i++)
				// times[i]=i+1;
			 chart();
			}

			
		  }
		);
	});

	function chart()
	{
		Highcharts.chart('container', 
		{
		  chart: 
		  {
			zoomType: 'xy'
		  },
		  title: 
		  {
			text: ''//chart的標題
		  },
		  subtitle: 
		  {
			text: ''//chart的副標題
		  },

	      exporting: { enabled: false },//關掉chart context menu

	      //關掉商標 highchart.com=====
	      credits: {
	      enabled: false
	      },
	      //===========================
		  
		  xAxis: 
		  [{
			categories: dateAndTime,
			//['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
			  //'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'],
			crosshair: true
		  }],
		  yAxis: 
		  [{ // Primary yAxis
			labels: 
			{
			  format: '{value}°C',
			  style: 
			  {
				color: Highcharts.getOptions().colors[1]
			  }
			},
			title: 
			{
			  text: 'Temperature',
			  style: 
			  {
				color: Highcharts.getOptions().colors[1]
			  }
			}
		  }, 
		  { // Secondary yAxis
			title: 
			{
			  text: 'Humidity',
			  style: 
			  {
				color: Highcharts.getOptions().colors[0]
			  }
			},
			labels: 
			{
			  format: '%',
			  style: 
			  {
				color: Highcharts.getOptions().colors[0]
			  }
			},
			opposite: true
		  }],
		  tooltip: 
		  {
			shared: true
		  },
		  legend: 
		  {
			layout: 'vertical',
			align: 'left',
			x: 120,
			verticalAlign: 'top',
			y: 100,
			floating: true,
			backgroundColor: (Highcharts.theme && Highcharts.theme.legendBackgroundColor) || 'rgba(255,255,255,0.25)'
		  },
		  series: 
		  [{
			name: 'Humidity',
			type: 'column',
			yAxis: 1,
			data: valueKWet,
			//[49.9, 71.5, 106.4, 129.2, 144.0, 176.0, 135.6, 148.5, 216.4, 194.1, 95.6, 54.4],
			tooltip: 
			{
			  valueSuffix: ' %'
			}

		  }, 
		  {
			name: 'Temperature',
			type: 'spline',
			data: valueKTemp,
			//[7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2, 26.5, 23.3, 18.3, 13.9, 9.6],
			tooltip: {
			  valueSuffix: '°C'
			}
		  }]
		});
	}