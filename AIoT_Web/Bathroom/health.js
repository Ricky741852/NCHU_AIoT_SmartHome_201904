	var valueGas=[];
	var valueLiquid=[];
	var times=[];
	
    $(document).ready(function() 
	{
	
    ////////////////////////
	$.ajax(
		 {  type:"GET",  
			url:"./Bathroom/GetData.php",
			datatype: "json", 
			contentType: "application/json", 
			data:"id=1",
		   success:function(data)
		   {
			  valueGas = [];
			  valueLiquid = [];
		   // alert(data);
			 data=$.parseJSON(data);
		   //  alert(data.length);
		   //  alert(data[1][2]);
		   length = data.length;
			 for (var i=0;i<data.length;i++)
			 {
			  valueGas[i]=parseInt(data[i][3]);
			  valueLiquid[i]=parseInt(data[i][4]);
			  //alert(value[i]);
			 }
		   //  alert(value);
			 for(var i=0;i<data.length;i++)
				times[i]=i+1;
			 chart();
			}
		  }
		);
		//  alert("456");
	
		$("#people").change(function()
		{
			var people = $(this).val();
			var dataString = "id=" + people;
			$.ajax(
			 {  type:"GET",  
				url:"./Bathroom/GetData.php",
				datatype: "json", 
				contentType: "application/json", 
				data: dataString,
			   success:function(data)
			   {
			     valueGas = [];
			  valueLiquid = [];
			   // alert(data);
				 data=$.parseJSON(data);
			   //  alert(data.length);
			   //  alert(data[1][2]);
			   length = data.length;
				 for (var i=0;i<data.length;i++)
				 {
				  valueGas[i]=parseInt(data[i][3]);
				  valueLiquid[i]=parseInt(data[i][4]);
				  //alert(value[i]);
				 }
			   //  alert(value);
				 for(var i=0;i<data.length;i++)
					times[i]=i+1;
				 chart();
				}
			  }
			);
		});
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

	      exporting: { enabled: false },//關掉chart context menu

	      //關掉商標 highchart.com=====
	      credits: {
	      enabled: false
	      },
	      //===========================

		  subtitle: 
		  {
			text: ''//chart的副標題
		  },
		  xAxis: 
		  [{
			categories: times,
			//['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
			  //'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'],
			crosshair: true
		  }],
		  yAxis: 
		  [{ // Primary yAxis
			labels: 
			{
			  format: '{value} ppm',
			  style: 
			  {
				color: Highcharts.getOptions().colors[1]
			  }
			},
			title: 
			{
			  text: 'Gas',
			  style: 
			  {
				color: Highcharts.getOptions().colors[1]
			  }
			}
		  }, 
		  { // Secondary yAxis
			title: 
			{
			  text: 'Liquid',
			  style: 
			  {
				color: Highcharts.getOptions().colors[0]
			  }
			},
			labels: 
			{
			  format: '{value} mg/L',
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
			name: 'Liquid',
			type: 'column',
			yAxis: 1,
			data: valueLiquid,
			//[49.9, 71.5, 106.4, 129.2, 144.0, 176.0, 135.6, 148.5, 216.4, 194.1, 95.6, 54.4],
			tooltip: 
			{
			  valueSuffix: ' mg/L'
			}

		  }, 
		  {
			name: 'Gas',
			type: 'spline',
			data: valueGas,
			//[7.0, 6.9, 9.5, 14.5, 18.2, 21.5, 25.2, 26.5, 23.3, 18.3, 13.9, 9.6],
			tooltip: {
			  valueSuffix: ' ppm'
			}
		  }]
		});
	}