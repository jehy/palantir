<?

function f_connect()
{
    global $mysqli;
    $mysqli = new mysqli('localhost', 'user', 'password', 'dbName');

    if (mysqli_connect_errno()) {
        echo "Error: Unable to connect to MySQL." . PHP_EOL;
        echo "Debugging errno: " . mysqli_connect_errno() . PHP_EOL;
        echo "Debugging error: " . mysqli_connect_error() . PHP_EOL;
        exit;
    }
}
?>