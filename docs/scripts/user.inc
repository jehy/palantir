<?
function changenfo()
{
    global $mysqli;
    global $loginx, $passwordx, $emailx, $nickx, $our_user_id;
    $error = '';
    if (!$passwordx)
        $error .= '<br>Вы не ввели пароль!';
    if (!$nickx)
        $error .= '<br>Вы не ввели обращение!';
    if (!$emailx)
        $error .= '<br>Вы не ввели E-mail!';
    if (!$loginx)
        $error .= '<br>Вы не вписали логин!';
    $sql = 'select * from users where ((login=?)and(id!=?)) limit 1';
//echo $sql;

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('si', $loginx, $our_user_id);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows)
        $error .= '<br>Такой логин уже используется!';

    $ctime = time() + 60 * 60 * 24 * 30 * 12; //for an approximately year
    if (!$error) {
        setcookie('cpassword', $passwordx, $ctime);
        setcookie('clogin', $loginx, $ctime);
        $sql = 'update users set login=?, password=?, email=?,nick=? where id=? limit 1';
        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('ssssi', $loginx, $passwordx, $emailx, $nickx, $our_user_id);
        $stmt->execute();

        return 0;
        //echo'Профиль успешно изменён! ';
    } else return $error;

}

function authorisate()
{
    global $session;
    if (!$session) {
        $t = 60 * 60 * 8 + time(); //for 24 hours
        $session = md5(time()) . substr(md5(rand(0, 1000)), 0, 5);
        setcookie('session', $session, $t);
    }
}


function get_user_type()
{
    global $ac, $our_user, $admin_user, $our_user_id, $admin_user_id, $login, $password, $clogin, $cpassword, $session, $mysqli;
    $our_user_id = '';
    $admin_user_id = '';
    $admin_user = false;
    $our_user = false;
    if ($ac == 'login') {
        $clogin = $login;
        $cpassword = $password;
    } elseif ($ac == 'logout') {
        $our_user_id = $admin_user_id = $our_user = $admin_user = $login = $password = $clogin = $cpassword = false;
        setcookie('clogin', '');
        setcookie('cpassword', '');
    }
//checking admin authorisation
    $sql = 'select id from auth where login=? and pass=?';
    #echo '<! -- temp' . $sql . '-->';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('ss', $clogin, $cpassword);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        $row = $result->fetch_row();
        $admin_user_id = $row[0];
        $admin_user = true;
        setcookie('clogin', $clogin); //only admin cookie expires after closing browser
        setcookie('cpassword', $cpassword);
        //echo'Adm!!';
    }
//check if we have user authorisation


    $time = time();
    $sql = 'select id from users where((login=?)and(password=?)) limit 1';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('ss', $clogin, $cpassword);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        $row = $result->fetch_row();

        $ctime = time() + 60 * 60 * 24 * 30 * 12; //for an approximately year
        setcookie('clogin', $clogin, $ctime);
        setcookie('cpassword', $cpassword, $ctime);
        $our_user_id = $row[0]; //echo"<b>!!".$our_user_id."</b>";
        $our_user = true; //echo"<h1>POSLE ".$row[last_login]."</h1>";
        $sql = 'update users set last_login=? where id=? limit 1';
        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('ii', $time, $row[0]);
        $stmt->execute();
    }
}

###Strange staff for admin

/*
if (($ac == 'showsrc') && $admin_user) {
    if (isset($_POST['show'])) {
        if (isset($_COOKIE['show'])) {
            foreach ($_COOKIE['show'] as $key => $entry) {
                if (is_array($_COOKIE['show'][$key])) {
                    foreach ($_COOKIE['show'][$key] as $key2 => $entry2) {
                        if (!isset($_POST['show'][$key][$key2])) { //echo $key;
                            setcookie('show[' . $key . '][' . $key2 . ']', '', time() - 3600);
                            //echo 'show['.$key.']['.$key2.'] remove';
                            unset($show[$key][$key2]);
                        }
                    }
                } else {
                    setcookie('show[' . $key . ']', '', time() - 3600);
                    //echo 'show['.$key.']['.$key2.'] remove';
                    unset($show[$key]);
                }
            }
        }
        //print_R($show);
        foreach ($_POST['show'] as $key => $entry) {
            if (is_array($_POST['show'][$key])) {
                foreach (@$_POST['show'][@$key] as $key2 => $entry2) {
                    if (!isset($_COOKIE['show'][$key][$key2])) {
                        setcookie('show[' . $key . '][' . $key2 . ']', $entry2[0], time() + 3600 * 300);
                        $show[$key][$key2] = $entry2[0];
                        //echo 'show['.$key.']['.$key2.'] set';
                    }
                }
            } else {
                setcookie('show[' . $key . ']', $entry, time() + 3600 * 300);
                $show[$key] = $entry;
            }

        }

    }
}
*/


?>
