<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Kreait\Firebase\Factory;
use Kreait\Firebase\Auth;
use Firebase\Auth\Token\Exception\InvalidToken;
use Kreait\Firebase\Exception\Auth\RevokedIdToken;

class FirebaseController extends Controller
{
    protected $auth, $database;

    public function __construct()
    {
        $factory = (new Factory)
        ->withServiceAccount(__DIR__.'/aquarium-iot.json')
        ->withDatabaseUri('https://aquarium-iot-27650-default-rtdb.asia-southeast1.firebasedatabase.app');

        $this->auth = $factory->createAuth();
        $this->database = $factory->createDatabase();
    }

        public function detailApi()
    {
        $ref = $this->database->getReference('admin/aquarium-1')->getValue();
        return($ref);
    }

public function fd1(Request $request)

    {
        $total = $this->database->getReference('admin/aquarium-1/pakan')->set([
                'feed_time_1' => $request->fd1,
                'feed_time_2' => $request->fd2,
                'feed_time_3' => $request->fd3,
        ]);
        
        return redirect('/home');
    }
  
}
