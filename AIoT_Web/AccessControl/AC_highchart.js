function updatephp(){
      $.getJSON(
  './AccessControl/getData.php',
  function(data) {
    
    var date = [];
    var time = [];
 
    var len = data.length;
      for (var i = 0; i <len; i++)
        {
          if(parseInt(data[i][4])==1)
          {
            date[i] = data[i][1];

            time[i] = parseInt(data[i][2]);
            
            //val2.push({y:parseInt(data[i][2]), color: '#14ffec' });
          }
        }
         

    Highcharts.chart('container', {
      chart: {
        zoomType: 'x'
      },
      title: {
        text: '' //chart的標題
      },

      exporting: { enabled: false },//關掉chart context menu

      //關掉商標 highchart.com=====
      credits: {
      enabled: false
      },
      //===========================

      subtitle: {  //chart的副標題
        text: document.ontouchstart === undefined ?
          'Click and drag in the plot area to zoom in' : 'Pinch the chart to zoom in'
      },
      xAxis: {
        title: {
          text: 'DATE'
        },
        categories: date,
        labels:{ 

          enabled: true,
        }        
      },
      yAxis: {
        title: {
          text: 'TIME'
        }, 
      legend: {
        enabled: true
      }
    },
      plotOptions: {
        area: {
          fillColor: {
            linearGradient: {
              x1: 0,
              y1: 0,
              x2: 1,
              y2: 1
            },
            stops: [
              [0, Highcharts.getOptions().colors[0]],
              [1, Highcharts.Color(Highcharts.getOptions().colors[0]).setOpacity(0).get('rgba')]
            ]
          },
          marker: {
            radius: 2
          },
          lineWidth: 1,
          states: {
            hover: {
              lineWidth: 1
            }
          },
          threshold: null
        }
      },

      series: [{
        //type: 'area',
        name: 'value1',
        data: time,
        showInLegend: false   //關掉選擇chart的線    
      }
      ]
    });
    //setTimeout(updatephp, 5000);
  }
  
);}
      updatephp();

function showCustomer(str) {
  var c;
  var xhttp; 

  if (str == "") {
   //document.getElementById("txtHint").innerHTML = "";
    return;
  }
  xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      //document.getElementById("txtHint").innerHTML = this.responseText;
       updatephp();
    }
  };
  xhttp.open("GET", "./AccessControl/postdata.php?people="+str, true);
  xhttp.send();
}  