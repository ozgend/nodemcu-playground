const char page_INDEX[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <style>
        * {
            font-size: 150%;
            color: #c1c1c1;
            background: #000000;
            font-family: sans-serif;
        }

        .btn {
            width: 100%;
            line-height: 2;
        }

        .btn-on {
            background-color: #d4f7da;
            color: #4ea74e;
        }

        .btn-off {
            background-color: #ffd2d2;
            color: #a74e4e;
        }
    </style>
</head>

<body>
    <br><br>
    <a href="/on"><button class="btn btn-on"> ON </button></a>
    <br><br>
    <a href="/off"><button class="btn btn-off"> OFF </button></a>
    <br>
</body>

</html>
)=====";