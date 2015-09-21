<?
function increment_queries($site_id)
{
    global $mysqli;
    $sql = 'update `queries` set `quantity`=`quantity`+5 where ((`ip`=?)and(`site_id`=?)and (`date`=?))';
    $ip = ip2long($_SERVER['REMOTE_ADDR']);
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('iis', $ip, $site_id, date("Y:m:d"));
    $stmt->execute();

    #echo $sql.mysql_error();
    if (!$mysqli->affected_rows) {
        $sql = 'INSERT INTO `queries` VALUES(?,?,1,?)';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('sii', date("Y:m:d"), $site_id, $ip);
        $stmt->execute();
    }
    #echo $sql.mysql_error();
}

function get_queries($site_id)
{
    global $mysqli;
    $sql = 'select SUM(`quantity`) from queries where ((site_id=?) and (`date`=?))';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('is', $site_id, date("Y:m:d"));
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        $row = $result->fetch_array(MYSQLI_ASSOC);

        if ($row[0] == NULL)
            return 0;
        else
            return $row[0];
    }
    return 0;
}

if (@$step != 2) {
    ?>
    Введите хотя бы одно из полей, которые были заполнены вами при регистрации пользователя. Пароль будет выслан по E-мэйл, под которым вы зарегистрировались.
    <br><b>Внимание!</b> Письмо может попасть в "Спам" - посмотрите там, если оно не пришло в течение 10 минут!
    <FORM METHOD="POST" ACTION="index.php">
        <input type='hidden' name='page' value='reveal'>
        <input type='hidden' name='step' value='2'>
        <table align="center">
            <tr>
                <td>Логин:</td>
                <td><input class="tab_all" TYPE="text" NAME="reveal[login]"></td>
            </tr>
            <tr>
                <td>Пароль:</td>
                <td><input class="tab_all" type="Password" NAME="reveal[password]"></td>
            </tr>
            <tr>
                <td>Е-мэйл:</td>
                <td><input class="tab_all" TYPE="text" NAME="reveal[email]"></td>
            </tr>
            <tr>
                <td>Ник или ФИО:</td>
                <td><input class="tab_all" TYPE="text" NAME="reveal[nick]"></td>
            </tr>
            <tr>
                <td>Адрес сайта</td>
                <td><input class="tab_all" TYPE="text" NAME="reveal[url]"></td>
            </tr>
            <tr>
                <td rowspan="2"><input type="submit" value="отправить пароль" class='menu'></td>
            </tr>
        </table>
    </form>
    <br><br><strong>В случае потери вами почтового
        адреса</strong> мы уже не можем вас точно идентифицировать, так что если это случилось, пожалуйста, зарегестрируйте сайт заново. Старая запись будет со временем удалена из-за непосещаемости.
    <br>
    <strong>Количество попыток запроса пароля</strong> для сайта ограничено тремя за сутки.<br>

<?
} else {
    $err = array();
    if (!($reveal['login'] || $reveal['password'] || $reveal['nick'] || $reveal['email'] || $reveal['url']))
        $err[] = 'Не заполнены никакие поисковые поля!';
    else {
        $sql = 'select sources.id,users.id as user,email,nick,login,password from users,sources where((users.id=sources.user_id)and((1=0) ';
        if ($reveal['login']) $sql .= 'or(login=?)';
        if ($reveal['password']) $sql .= 'or(password=?)';
        if ($reveal['nick']) $sql .= 'or(nick=?)';
        if ($reveal['email']) $sql .= 'or(email=?)';
        if ($reveal['url']) $sql .= 'or(url=?)';
        $sql .= ')) GROUP BY users.id limit 20';

        $stmt = $mysqli->prepare($sql);

        if ($reveal['login'])
            $stmt->bind_param('s', $reveal['login']);
        if ($reveal['password'])
            $stmt->bind_param('s', $reveal['password']);
        if ($reveal['nick'])
            $stmt->bind_param('s', $reveal['nick']);
        if ($reveal['email'])
            $stmt->bind_param('s', $reveal['email']);
        if ($reveal['url'])
            $stmt->bind_param('s', $reveal['url']);


        $stmt->execute();
        $result = $stmt->get_result();
        if (!$result->num_rows)
            $err[] = 'Пользователя, соответствующего запросу, не найдено! Попробуйте указать другие данные.';
        else
            while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
                if (get_queries($row['id']) >= 3)
                    $err[] = 'Превышен лимит запросов пароля для сайта на сегодня. Попробуйте завтра.';
                else
                    increment_queries($row['id']);
                if (!sizeof($err)) {
                    // Email получателя/Получателей
                    $Receiver = $row['email'];
                    // Тема сообщения
                    $Subject = 'Palantir: напоминание пароля';
                    // Текст сообщения (в HTML)
                    $Text = '<html><head>
          <meta http-equiv="Content-Type" content="text/html; charset=windows-1251">
          <STYLE TYPE="text/css">
                  body{
                  background-color : #6F7F8F;
                  }
                  A:visited{
                  COLOR : white;
                  }
                  A:link
                  {COLOR : white;
                  }
          </style></head><body><h2><a href="' . COMMON_URL . '">Palantir:</a> Cервис напоминания пароля</h2><strong>' . $row['nick'] . '</strong>, Ваши данные для администрирования сайта в каталоге:<br>
          <table border="1px" cellpadding="0" cellspacing="0" width="400px">
          <tr><td>Ваш логин:</td><td><strong>' . $row['login'] . '</strong></td></tr>
          <tr><td>Ваш пароль:</td><td><strong>' . $row['password'] . '</strong></td></tr></table>
          Приятного вам подсчёта и баннерообмена!<hr>
          Сожалеем, если письмо пришло к вам по ошибке. Если такие случаи будут повторяться, вы можете <a href="' . COMMON_URL . 'index.php?page=mail">связаться с администрацией</a>.</body></html>';
                    // Вложение в письме - адрес к файлу

                    $headers = 'MIME-Version: 1.0' . "\r\n";
                    $headers .= 'Content-type: text/html; charset=utf-8' . "\r\n";

                    $m = mail($Receiver, $Subject, $Text, $headers);
                    if ($m) {
                        echo '<br>Пользователь найден, выслано напоминание пароля.<br>';
                    } else {
                        echo "Возникла ошибка во время отсылки напоминания пароля.<br />";
                    }
                }
            }
    }
    if (sizeof($err)) echo implode('<br>', $err);
}?>
