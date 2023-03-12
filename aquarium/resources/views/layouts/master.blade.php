<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1">
    <title>Modern Admin Dashboard</title>
    <link rel="stylesheet" href="{{asset('css/style.css')}}">
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
                <div class="profile-img bg-img" style="background-image: url(img/logo.jpeg)"></div>
                <h4>D'Yasmin </h4>
                <small>Aquatic</small>
            </div>

            <div class="side-menu">
                <ul>
                    <li>
                       <a href="" class="active">
                            <span class="las la-home"></span>
                            <small>Dashboard</small>
                        </a>
                    </li>
                    <li>
                       <a href="{{route('log')}}">
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
                        <div class="bg-img" style="background-image: url(img/logo.jpeg)"></div>
                    <a href="./login/login.html">
                        <span class="las la-power-off"></span>
                        <a class="dropdown-item" href="{{ route('logout') }}"
                        onclick="event.preventDefault();
                                                     document.getElementById('logout-form').submit();">
                                        <span>Logout</span>
                                    </a>

                                    <form id="logout-form" action="{{ route('logout') }}" method="POST" class="d-none">
                                        @csrf
                                    </form>
                    </a>       
                    </div>
                </div>
            </div>
        </header>
        
        
        <main>
            
            <div class="page-header">
                <h1>Dashboard</h1>
                <small>Home / Dashboard</small>
            </div>
            
            <div class="page-content">
            
                <div class="analytics">

                    <div class="card">
                        <div class="card-temperature">
                            <h2>fedding</h2>
                        </div>
                        <div class="card-progress">
                            <small>Pakan Otomatis</small>
                            <div class="card-indicator">
                                <div class="indicator one" style="width: 100%"></div>
                            </div>
                        </div>
                    </div>

                    <div class="card">
                        <div class="card-head">
                            <h2>Suhu</h2>
                        </div>
                        <div class="card-progress">
                            <small>Monitoring Suhu</small>
                            <div class="card-indicator">
                                <div class="indicator two" style="width: 100%"></div>
                            </div>
                        </div>
                    </div>

                    <div class="card">
                        <div class="card-head">
                            <h2>PH</h2>
                        </div>
                        <div class="card-progress">
                            <small>Monitoring PH</small>
                            <div class="card-indicator">
                                <div class="indicator three" style="width: 100%"></div>
                            </div>
                        </div>
                    </div>

                    <div class="card">
                        <div class="card-head">
                            <h2>Oksigen</h2>
                        </div>
                        <div class="card-progress">
                            <small>Pengecekan Kecepatan Oksigen</small>
                            <div class="card-indicator">
                                <div class="indicator four" style="width: 100%"></div>
                            </div>
                        </div>
                    </div>

                </div>

                <div class="records table-responsive">
                    
                <center><h1>Jadwal Makanan</h1></center>
                <br>


                    <div>
                        <table width="100%">
                            <thead>
                                <tr>
                                    <th><span class="las la-sort"></span> CLIENT</th>
                                    <th><span class="las la-sort"></span> WAKTU</th>
                                    <th><span class="las la-sort"></span> DATE</th>
                                    <th><span class="las la-sort"></span> STATUS</th>
                                </tr>
                            </thead>
                            <tbody>
                                <tr>
                                    <td>
                                        <div class="client">
                                            <div class="client-info">
                                                <h4>Andrew Bruno</h4>
                                            </div>
                                        </div>
                                    </td>
                                    <td>
                                        08.00
                                    </td>
                                    <td>
                                        19 April, 2022 
                                    </td>
                                    <td>
                                       SUKSES
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <div class="client">
                                            <div class="client-info">
                                                <h4>Andrew Bruno</h4>
                                            </div>
                                        </div>
                                    </td>
                                    <td>
                                        08.00
                                    </td>
                                    <td>
                                        19 April, 2022 
                                    </td>
                                    <td>
                                       SUKSES
                                    </td>
                                </tr>
                                <tr>
                                    <td>
                                        <div class="client">
                                            <div class="client-info">
                                                <h4>Andrew Bruno</h4>
                                            </div>
                                        </div>
                                    </td>
                                    <td>
                                        08.00
                                    </td>
                                    <td>
                                        19 April, 2022 
                                    </td>
                                    <td>
                                       SUKSES
                                    </td>
                                </tr>
                                             
            
                                             
                            </tbody>
                        </table>
                    </div>

                </div>
            
            </div>
            
        </main>
        
    </div>
</body>
</html>