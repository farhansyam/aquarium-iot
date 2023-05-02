<?php

use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('auth.login');
});

Auth::routes();

Route::get('/home', [App\Http\Controllers\HomeController::class, 'index'])->name('home');
Route::get('/info', [App\Http\Controllers\HomeController::class, 'info'])->name('info');
Route::get('/about', [App\Http\Controllers\HomeController::class, 'about'])->name('about');
Route::get('/log', [App\Http\Controllers\HomeController::class, 'read'])->name('log');
Route::get('/read', [App\Http\Controllers\FirebaseController::class, 'detailApi'])->name('read');
Route::get('/fd1', [App\Http\Controllers\FirebaseController::class, 'fd1'])->name('setfeedtime');
