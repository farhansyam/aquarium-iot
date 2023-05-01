<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Kreait\Firebase\Factory;
use Kreait\Firebase\Auth;
use Firebase\Auth\Token\Exception\InvalidToken;
use Kreait\Firebase\Exception\Auth\RevokedIdToken;
class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
        $factory = (new Factory)
        ->withServiceAccount(__DIR__.'/aquarium-iot.json')
        ->withDatabaseUri('https://aquarium-iot-27650-default-rtdb.asia-southeast1.firebasedatabase.app');

        $this->auth = $factory->createAuth();
        $this->database = $factory->createDatabase();
    }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Contracts\Support\Renderable
     */
    public function index()
    {
        $total = $this->database->getReference('admin')->getValue();
        $t = count($total);
        $ref = $this->database->getReference('admin')->getValue();
        $factory = (new Factory)
        ->withServiceAccount(__DIR__.'/aquarium-iot.json');
        foreach($ref as $k)
            $phs = $k['ph'];
            $turb = $k['turbidity'];
            $temp = $k['temp'];

        $k2 = $this->database->getReference('admin/aquarium-1/pakan')->getValue();
        $fd1 = $k2['feed_time_1'];
        $fd2 = $k2['feed_time_2'];
        $fd3 = $k2['feed_time_3'];

        return view('backend.index',compact('phs','turb','temp','fd1','fd2','fd3'));
    }
    public function info()
    {
        return view('backend.info');
    }
    public function about()
    {
        return view('backend.about');
    }

     public function read()
    {
        $factory = (new Factory)
        ->withServiceAccount(__DIR__.'/aquarium-iot.json');
        $firestore = $factory->createFirestore();

        $kolam = $firestore->database()->collection('admin/aquarium-1/update-harian')->orderby('date','DESC')->limit(7)->documents(); //FireStoreClient Object
        foreach($kolam as $k)
            $tanggal = $k->data()['date'];
        foreach($kolam as $k)
            $phs[] = $k->data()['ph'];
        foreach($kolam as $k)
            $turb[] = $k->data()['turbidity'];
        foreach($kolam as $k)
            $temp[] = $k->data()['temp'];
        // return view('log.index',compact());
       

        return view('backend.log',compact('kolam','tanggal','phs','turb','temp'));
    
      }

}
