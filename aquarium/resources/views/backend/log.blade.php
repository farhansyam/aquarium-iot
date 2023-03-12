<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="{{asset('css/style.css"')}}>
    <link rel="stylesheet" href="https://maxst.icons8.com/vue-static/landings/line-awesome/line-awesome/1.3.0/css/line-awesome.min.css">
</head>
<body>
    <input type="checkbox" id="menu-toggle">
    <div class="sidebar">
        <div class="side-header">
            <h3>D'Yasmin<span>Aquatic</span></h3>
        </div>
        
        <div class="side-content">
            <div class="profile">
                <div class="profile-img bg-img" style="background-image: {{asset('img/logo.jpeg')}}"></div>
                <h4>D'Yasmin </h4>
                <small>Aquatic</small>
            </div>

            <div class="side-menu">
                <ul>
                    <li>
                       <a href="" >
                            <span class="las la-home"></span>
                            <small>Dashboard</small>
                        </a>
                    </li>
                    <li>
                       <a href="{{route('log')}}" class="active">
                            <span class="las la-clipboard-list"></span>
                            <small>Statistik</small>
                        </a>
                    </li>
                    <li>
                       <a href="{{route('about')}}">
                            <span class="las la-envelope"></span>
                            <small>About</small>
                        </a>
                    </li>
                    <li>
                       <a href="{{route('info')}}">
                            <span class="las la-envelope"></span>
                            <small>Info</small>
                        </a>
                    </li>
                </ul>
            </div>
        </div>
    </div>
    
    <div class="main-content">
        
        <header>
            <div class="header-content">
                <label for="menu-toggle">
                    <span class="las la-bars"></span>
                </label>
                
                <div class="header-menu">
                    <label for="">
                        <span class="las la-search"></span>
                    </label>
                    
                    <div class="notify-icon">
                        <span class="las la-envelope"></span>
                        <span class="notify">4</span>
                    </div>
                    
                    <div class="notify-icon">
                        <span class="las la-bell"></span>
                        <span class="notify">3</span>
                    </div>
                    
                    <div class="user">
                        <div class="bg-img" style="background-image: url({{asset('img/logo.jpeg')}})"></div>
                    <a href="./login/login.html">
                        <span class="las la-power-off"></span>
                        <span>Logout</span>
                    </a>       
                    </div>
                </div>
            </div>
        </header>

        <main>
            <div class="page-header">
                <h1>Statistik</h1>
                <small>Home / Statistik</small>
            </div>
            <br>
            <div class='title'>
                <p>suhu</p>
              </div>
              <svg class='container' width="529px" height="286px" viewBox="30 27 529 286" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                  <desc>Created with Sketch.</desc>
                  <defs></defs>
                  <g id="graph-copy" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd" transform="translate(30.000000, 27.000000)">
                      <g id="y_axis" font-size="11.0833333" font-family=".HelveticaNeueDeskInterface-Regular, .Helvetica Neue DeskInterface" fill="#FFFFFF" opacity="0.4" font-weight="normal">
                          <text id="0">
                              <tspan x="25.3008249" y="264.333333">0</tspan>
                          </text>
                          <text id="200">
                              <tspan x="12.7757572" y="232.666667">200</tspan>
                          </text>
                          <text id="400">
                              <tspan x="12.7757572" y="201">400</tspan>
                          </text>
                          <text id="600">
                              <tspan x="12.7757572" y="169.333333">600</tspan>
                          </text>
                          <text id="800">
                              <tspan x="12.7757572" y="137.666667">800</tspan>
                          </text>
                          <text id="1000">
                              <tspan x="6.51322328" y="106">1000</tspan>
                          </text>
                          <text id="1200">
                              <tspan x="6.51322328" y="74.3333333">1200</tspan>
                          </text>
                          <text id="1400">
                              <tspan x="6.51322328" y="42.6666667">1400</tspan>
                          </text>
                          <text id="1600">
                              <tspan x="6.51322328" y="11">1600</tspan>
                          </text>
                      </g>
                      <g id="GRAPHS" transform="translate(64.000000, 16.000000)" stroke-linecap="round" stroke-width="8" stroke-linejoin="round">
                          <polyline id="Banks" stroke="#5BCAC1" points="0 1 88.0438662 1 128.985782 137 180.170616 137 224.189573 182 256.947867 91 301.990521 137 346.009479 91 392.087202 91 429.952607 179"></polyline>
                          <polyline id="Bridge" stroke="#81DEFF" points="2.04739336 183 54.2559242 227 96.2274882 47 133.080569 1 302.018438 1 346.680361 44.6280822 386.957346 0 427.905213 43"></polyline>
                          <polyline id="PayPal" stroke="#F6F5A6" points="2.04739336 180 53.273159 180 99.2985782 91 137.175355 47 219.077488 47 256.947867 90 301.990521 47 349.080569 137 398.228672 137 432 91"></polyline>
                      </g>
                      <g id="x_axis" transform="translate(71.974046, 271.541667)" font-size="11.0833333" font-family=".HelveticaNeueDeskInterface-Regular, .Helvetica Neue DeskInterface" fill="#FFFFFF" opacity="0.4" font-weight="normal">
                          <text id="1">
                              <tspan x="0.396183206" y="11">1</tspan>
                          </text>
                          <text id="2">
                              <tspan x="39.2603361" y="11">2</tspan>
                          </text>
                          <text id="3">
                              <tspan x="78.8786567" y="11">3</tspan>
                          </text>
                          <text id="4">
                              <tspan x="118.496977" y="11">4</tspan>
                          </text>
                          <text id="5">
                              <tspan x="158.115298" y="11">5</tspan>
                          </text>
                          <text id="6">
                              <tspan x="197.733619" y="11">6</tspan>
                          </text>
                          <text id="7">
                              <tspan x="237.351939" y="11">7</tspan>
                          </text>
                          <text id="8">
                              <tspan x="276.97026" y="11">8</tspan>
                          </text>
                          <text id="9">
                              <tspan x="316.58858" y="11">9</tspan>
                          </text>
                          <text id="10">
                              <tspan x="359.229833" y="11">10</tspan>
                          </text>
                          <text id="11">
                              <tspan x="400.036703" y="11">11</tspan>
                          </text>
                          <text id="12">
                              <tspan x="438.466474" y="11">12</tspan>
                          </text>
                      </g>
                      <g id="grid" transform="translate(46.618321, 4.750000)" stroke="#FFFFFF" stroke-linecap="square" opacity="0.0800000057">
                          <path d="M0.396183206,1.1875 L478.991396,1.1875" id="Line"></path>
                          <path d="M0.396183206,32.8541667 L478.991396,32.8541667" id="Line"></path>
                          <path d="M0.396183206,64.5208333 L478.991396,64.5208333" id="Line"></path>
                          <path d="M0.396183206,96.1875 L478.991396,96.1875" id="Line"></path>
                          <path d="M0.396183206,127.854167 L478.991396,127.854167" id="Line"></path>
                          <path d="M0.396183206,159.520833 L478.991396,159.520833" id="Line"></path>
                          <path d="M0.396183206,191.1875 L478.991396,191.1875" id="Line"></path>
                          <path d="M0.396183206,222.854167 L478.991396,222.854167" id="Line"></path>
                          <path d="M0.396183206,254.520833 L478.991396,254.520833" id="Line"></path>
                      </g>
                  </g>
              </svg>
              <br><br><br>
              <div class='title'>
                <p>PH</p>
              </div>
              <svg class='container' width="529px" height="286px" viewBox="30 27 529 286" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                  <desc>Created with Sketch.</desc>
                  <defs></defs>
                  <g id="graph-copy" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd" transform="translate(30.000000, 27.000000)">
                      <g id="y_axis" font-size="11.0833333" font-family=".HelveticaNeueDeskInterface-Regular, .Helvetica Neue DeskInterface" fill="#FFFFFF" opacity="0.4" font-weight="normal">
                          <text id="0">
                              <tspan x="25.3008249" y="264.333333">0</tspan>
                          </text>
                          <text id="200">
                              <tspan x="12.7757572" y="232.666667">200</tspan>
                          </text>
                          <text id="400">
                              <tspan x="12.7757572" y="201">400</tspan>
                          </text>
                          <text id="600">
                              <tspan x="12.7757572" y="169.333333">600</tspan>
                          </text>
                          <text id="800">
                              <tspan x="12.7757572" y="137.666667">800</tspan>
                          </text>
                          <text id="1000">
                              <tspan x="6.51322328" y="106">1000</tspan>
                          </text>
                          <text id="1200">
                              <tspan x="6.51322328" y="74.3333333">1200</tspan>
                          </text>
                          <text id="1400">
                              <tspan x="6.51322328" y="42.6666667">1400</tspan>
                          </text>
                          <text id="1600">
                              <tspan x="6.51322328" y="11">1600</tspan>
                          </text>
                      </g>
                      <g id="GRAPHS" transform="translate(64.000000, 16.000000)" stroke-linecap="round" stroke-width="8" stroke-linejoin="round">
                          <polyline id="Banks" stroke="#5BCAC1" points="0 1 88.0438662 1 128.985782 137 180.170616 137 224.189573 182 256.947867 91 301.990521 137 346.009479 91 392.087202 91 429.952607 179"></polyline>
                          <polyline id="Bridge" stroke="#81DEFF" points="2.04739336 183 54.2559242 227 96.2274882 47 133.080569 1 302.018438 1 346.680361 44.6280822 386.957346 0 427.905213 43"></polyline>
                          <polyline id="PayPal" stroke="#F6F5A6" points="2.04739336 180 53.273159 180 99.2985782 91 137.175355 47 219.077488 47 256.947867 90 301.990521 47 349.080569 137 398.228672 137 432 91"></polyline>
                      </g>
                      <g id="x_axis" transform="translate(71.974046, 271.541667)" font-size="11.0833333" font-family=".HelveticaNeueDeskInterface-Regular, .Helvetica Neue DeskInterface" fill="#FFFFFF" opacity="0.4" font-weight="normal">
                          <text id="1">
                              <tspan x="0.396183206" y="11">1</tspan>
                          </text>
                          <text id="2">
                              <tspan x="39.2603361" y="11">2</tspan>
                          </text>
                          <text id="3">
                              <tspan x="78.8786567" y="11">3</tspan>
                          </text>
                          <text id="4">
                              <tspan x="118.496977" y="11">4</tspan>
                          </text>
                          <text id="5">
                              <tspan x="158.115298" y="11">5</tspan>
                          </text>
                          <text id="6">
                              <tspan x="197.733619" y="11">6</tspan>
                          </text>
                          <text id="7">
                              <tspan x="237.351939" y="11">7</tspan>
                          </text>
                          <text id="8">
                              <tspan x="276.97026" y="11">8</tspan>
                          </text>
                          <text id="9">
                              <tspan x="316.58858" y="11">9</tspan>
                          </text>
                          <text id="10">
                              <tspan x="359.229833" y="11">10</tspan>
                          </text>
                          <text id="11">
                              <tspan x="400.036703" y="11">11</tspan>
                          </text>
                          <text id="12">
                              <tspan x="438.466474" y="11">12</tspan>
                          </text>
                      </g>
                      <g id="grid" transform="translate(46.618321, 4.750000)" stroke="#FFFFFF" stroke-linecap="square" opacity="0.0800000057">
                          <path d="M0.396183206,1.1875 L478.991396,1.1875" id="Line"></path>
                          <path d="M0.396183206,32.8541667 L478.991396,32.8541667" id="Line"></path>
                          <path d="M0.396183206,64.5208333 L478.991396,64.5208333" id="Line"></path>
                          <path d="M0.396183206,96.1875 L478.991396,96.1875" id="Line"></path>
                          <path d="M0.396183206,127.854167 L478.991396,127.854167" id="Line"></path>
                          <path d="M0.396183206,159.520833 L478.991396,159.520833" id="Line"></path>
                          <path d="M0.396183206,191.1875 L478.991396,191.1875" id="Line"></path>
                          <path d="M0.396183206,222.854167 L478.991396,222.854167" id="Line"></path>
                          <path d="M0.396183206,254.520833 L478.991396,254.520833" id="Line"></path>
                      </g>
                  </g>
              </svg>
        </main>

<style>
html {
height: 100%;
background: -moz-linear-gradient(-45deg, #000000 0%, #000000 100%); /* FF3.6-15 */
background: -webkit-linear-gradient(-45deg, #000000 0%,#000000 100%); /* Chrome10-25,Safari5.1-6 */
background: linear-gradient(135deg, #000000 0%,#000000 100%); /* W3C, IE10+, FF16+, Chrome26+, Opera12+, Safari7+ */
filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#de437d', endColorstr='#5b44b9',GradientType=1 ); /* IE6-9 fallback on horizontal gradient */
}


svg {
  margin: 0 auto;
  text-align: center;
  width: 100%;
  padding-top: 40px;
}

polyline {
  stroke-dasharray: 1000;
  stroke-dashoffset: 1000;
  animation: dash 5s ease-in forwards;
  animation-iteration-count: 10;
  animation-direction: alternate;
}

@keyframes dash{
  to {
    stroke-dashoffset: 0;
  }
}


p {
  font-size: 2rem;
  text-align:center;
  color: #efefef;
}
.name {
  font-size: .8rem;
  font-weight: light;
}

</style>
<br><br>
</body>
</html>