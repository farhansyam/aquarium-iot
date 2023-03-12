<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="UTF-8">
    <link rel="stylesheet" href="{{asset('css/login/style.css')}}">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.3/css/all.min.css">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="shortcut icon" href="{{asset('img/logo.jpeg')}}" l">
   </head>
<body>
  <div class="container">
    <input type="checkbox" id="flip">
    <div class="cover">
      <div class="front">
        <img class="backImg" src="/img/index.jpg" alt="">
        <div class="text">
          <span class="text-1">Silahkan Login <br> Untuk masuk</span>
          <span class="text-2">Kehalaman Selanjutnya</span>
        </div>
      </div>
      <div class="back">
        <img class="backImg" src="/img/index.jpg" alt="">
      </div>
    </div>
    <div class="forms">
        <div class="form-content">
            <div class="login-form">
              <form method="POST" action="{{ route('login') }}">
        
              @csrf
            <div class="title">Login</div>
            <div class="input-boxes">
              <div class="input-box">
                <i class="fas fa-envelope"></i>
                <input type="email" class="form-control @error('email') is-invalid @enderror" name="email" value="{{ old('email') }}" required placeholder="Enter your email" required>
              </div>
              <div class="input-box">
                <i class="fas fa-lock"></i>
                <input type="password" class="form-control @error('password') is-invalid @enderror" name="password" placeholder="Enter your password" required>

              </div>
              <div class="text"><a href="#">Forgot password?</a></div>
              <div class="button">
                <button type="submit">Submit</button>
              </div>
              <!--<div class="button input-box">
                <input type="submit" value="Sumbit">
              </div>--->
              <div class="text sign-up-text">Don't have an account? <label for="flip">Sigup now</label></div>
            </div>
      </div>
        <div class="signup-form">
          <div class="title">Signup</div>

            <div class="input-boxes">
              <div class="input-box">
                <i class="fas fa-user"></i>
              </div>
              <div class="input-box">
                @error('email')
                <span class="invalid-feedback" role="alert">
                  <strong>{{ $message }}</strong>
                </span>
                @enderror
                @error('password')
                <span class="invalid-feedback" role="alert">
                  <strong>{{ $message }}</strong>
                </span>
                @enderror
                <i class="fas fa-envelope"></i>
              </div>
              <div class="input-box">
                <i class="fas fa-lock"></i>
              </div>
              <div class="button input-box">
                <input type="submit" value="Sumbit">
              </div>
              <div class="text sign-up-text">Already have an account? <label for="flip">Login now</label></div>
            </div>
      </form>
    </div>
    </div>
    </div>
  </div>
</body>
</html>
