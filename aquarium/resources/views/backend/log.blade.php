<div class="row">
        <div class="col l3 m6 s12">
            <div class="card">
                <div class="card-content">
                    <div class="row">
                        <div class="col s12">
                            <div class="d-flex no-block align-items-center">
                                <div class="ml-auto">
                                    <span class="green-text display-6"><i class="ti-layout-media-left-alt"></i></span>
                                </div>
                            </div>
                        </div>
                        <div class="col s12">
                            <div class="progress">
                                <div class="determinate teal darken-2" style="width:100%;"></div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            
        </div>
        {{-- {{-- <div class="col l3 m6 s12">
            <div class="card">
                <div class="card-content">
                    <div class="row">
                        <div class="col s12">
                            <div class="d-flex no-block align-items-center">
                                <div>
                                    <h4>10.10.10</h4>
                                    <h6 class="card-subtitle">Terakhir Online</h6>
                                </div>
                                <div class="ml-auto">
                                    <span class="orange-text display-6"><i class="ti-notepad"></i></span>
                                </div>
                            </div>
                        </div>
                        <div class="col s12">
                            <div class="progress">
                                <div class="determinate amber darken-3" style="width:70%;"></div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div> --}}
    </div>
<script src="https://code.highcharts.com/highcharts.js"></script>
  <div class="row">
    <div class="col s12">
        <div id="grafik-ph" style="height: 240px; width:100%"></div>
    </div>
 </div>
 <br>
 <div class="row">
     <div class="col s12">
        <div id="grafik-temp" style="height: 240px; width:100%"></div>
    </div> 
  </div>
  <br>
    <div class="row">
    <div class="col s12">
        <div id="grafik-turbidity" style="height: 240px; width:100%"></div>
    </div>
</div>

<script>
    var ph = <?= json_encode($phs)?>;
    var time = <?= json_encode($tanggal)?>;
    var turbidity = <?= json_encode($turb)?>;
    Highcharts.chart('grafik-ph',{
        title : {
            text : 'PH Air'
        },
         subtitle: {
        text: 'ph air kolam'
         },
        xAxis : {
            categories : time,
            title:{
                text:"Tanggal"
            }
        },
        yAxis : {
            title:{
                text : 'Ph Air'
            }
        },
        legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'middle'
    },
        plotOption : {
            series :{
                allowPointSelect: true
                }
        },
        series:[
            {
                name: 'PH Air',
                data:ph
            }
        ]

    })

</script>
<script>

    var ph = <?= json_encode($temp)?>;
    var time = <?= json_encode($tanggal)?>;
    var turbidity = <?= json_encode($turb)?>;
    Highcharts.chart('grafik-temp',{
        title : {
            text : 'Temperatur Air'
        },
         subtitle: {
        text: 'Temperatur air kolam'
         },
        xAxis : {
            categories : time,
            title:{
                text:"Tanggal"
            }
        },
        yAxis : {
            title:{
                text : 'temp Air'
            }
        },
        legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'middle'
    },
        plotOption : {
            series :{
                allowPointSelect: true
                }
        },
        series:[
            {
                name: 'Temperature Air',
                data:ph
            }
        ]

    })

</script>

<script>

    var ph = <?= json_encode($turb)?>;
    var time = <?= json_encode($tanggal)?>;
    var turbidity = <?= json_encode($turb)?>;
    Highcharts.chart('grafik-turbidity',{
        title : {
            text : 'Kekeruhan Air'
        },
         subtitle: {
        text: 'Kekeruhan air kolam'
         },
        xAxis : {
            categories : time,
            title:{
                text:"Tanggal"
            }
        },
        yAxis : {
            title:{
                text : 'Kekeruhan Air'
            }
        },
        legend: {
        layout: 'vertical',
        align: 'right',
        verticalAlign: 'middle'
    },
        plotOption : {
            series :{
                allowPointSelect: true
                }
        },
        series:[
            {
                name: 'Kekeruhan Air',
                data:ph
            }
        ]

    })

</script>

          
      