<?if ($addrec) {
    $passwordx = str_replace('"', "&#34;", $passwordx);
    $loginx = str_replace('"', "&#34;", $loginx);
    $passwordx = str_replace("'", "&#039;", $passwordx);
    $loginx = str_replace("'", "&#039;", $loginx);
    $nickx = str_replace('"', "&#34;", $nickx);
    $emailx = str_replace('"', "&#034;", $emailx);
    $nickx = str_replace("'", "&#039;", $nickx);
    $emailx = str_replace("'", "&#039;", $emailx);
    $nickx = str_replace("<", "&lt;", $nickx);
    $emailx = str_replace("<", "&lt;", $emailx);
    $nickx = str_replace(">", "&gt;", $nickx);
    $emailx = str_replace(">", "&gt;", $emailx);
    if (!$passwordx)
        $error = $error . '<br>Вы не ввели пароль!';
    if (!$nickx)
        $error = $error . '<br>Вы не ввели обращение!';
    if (!$emailx)
        $error = $error . '<br>Вы не ввели E-mail!';
    if (!$loginx)
        $error = $error . '<br>Вы не вписали логин!';
    $sql = 'select * from users where ((login=?)and(password!=?))';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('ss', $loginx, $password);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        $error = $error . '<br>Такой логин уже используется!';
    }
    $date = date("Y:m:d");
    if (!$error) {
        setcookie("password", $passwordx);
        setcookie("login", $loginx);
        $sql = 'update users set login=?, password=?, email=?,nick=? where login=?';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('sssss', $loginx, $password, $emailx, $nickx, $login);
        $stmt->execute();
        $login = $loginx;
    }
}
?>