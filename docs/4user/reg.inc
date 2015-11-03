<?
###################################
###################################
function showlev2($n)
{
    global $mysqli;
    $sql = 'select * from types where parent=?';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $n);
    $stmt->execute();
    $result = $stmt->get_result();
    echo '<ul>';
    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
        $sql = 'select * from types where parent=?';
        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('i', $row['id']);
        $stmt->execute();
        $result2 = $stmt->get_result();
        if (!$result2->num_rows)
            echo '<a href="index.php?page=reg&ac=addsite&step=2&sid=' . $row['id'] . '">' . $row['name'] . '</a><br>';
        else
            echo $row['name'] . '<br>';
        showlev2($row['id']);
    }
    echo '</ul>';
}

function drevo()
{
    ?>
    <h1>Добавление сайта, шаг №1</h1>
    Выберите категорию для регистрации cвоего сайта:
    <br><?
    showlev2(13);
}

###################################
###################################
function reguser()
{
    global $reg, $REMOTE_ADDR;
    ?>
    <h1>Регистрация</h1>
    <FORM METHOD="POST" ACTION="index.php">
        <input type='hidden' name='page' value='reg'>
        <input type='hidden' name='step' value='2'>
        <table width="100%" align="center">

            <tr>
                <td colspan="2">Вначале производится регистрация пользователя (аккаунта), потом вы сможете добавить в
                    свой профиль ваши сайты, получить к каждому своему сайту код счётчика\банера и т.д.
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Логин</td>
                <!---->
                <td><input class="tab_all" TYPE="text" NAME="reg[login]" value='<?= $reg['login'] ?>' maxlength="40">
                </td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Пароль</td>
                <td><!----><input class="tab_all" TYPE="password" NAME="reg[password1]" maxlength="20"></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Повторите пароль</td>
                <td><!----><input class="tab_all" TYPE="password" NAME="reg[password2]" maxlength="20"></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>E-mail</td>
                <!---->
                <td><input class="tab_all" TYPE="text" NAME="reg[email]" value='<?= $reg['email'] ?>' maxlength="40">
                </td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Ник или Ф.И.О.</td>
                <!---->
                <td><input class="tab_all" TYPE="text" NAME="reg[nick]" value='<?= $reg['nick'] ?>' maxlength="40"></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Введите число с картинки&nbsp;<img src="random.php"></td>
                <td><input class="tab_all" TYPE="text" NAME="reg[if_hacker]"></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <TR>
                <TD colspan="2" align="center"><input type="submit" value="Зарегистрировать" class="button"></TD>
            </TR>
        </table>
    </form>
<?
}

###################################
###################################
function reguser2()
{
    global $reg, $mysqli;
    $error = array();
    if (!$reg['if_hacker'])
        $error[] = '<br>Поле с числом незаполнено!';
    else {
        $sql = 'select 1 from `check` where ((`ip`=?)and(time>?) and (rand=?)) limit 1';

        $stmt = $mysqli->prepare($sql);
        $time=(time() - 60 * 15);
        $ip=ip2long($_SERVER['REMOTE_ADDR']);
        $stmt->bind_param('sis', $ip, $time, $reg['if_hacker']);
        $stmt->execute();
        $result = $stmt->get_result();
        if (!$result->num_rows) $error[] = 'введённое число не совпадает со сгенерированным!';
    }
    if (!$reg['password1'])
        $error[] = '<br>Вы не ввели пароль!';

    if (!$reg['password2'])
        $error[] = '<br>Вы не ввели повтор пароля!';

    if ($reg['password1'] != $reg['password2'])
        $error[] = '<br>Пароли не совпадают!';

    if (!$reg['nick'])
        $error[] = '<br>Вы не ввели обращение!';

    if (!$reg['email'])
        $error[] = '<br>Вы не ввели E-mail!';

    if (!$reg['login'])
        $error[] = '<br>Вы не вписали логин!';


    $sql = 'select id from users where login=? limit 1';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('s', $reg['login']);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows)
        $error[] = '<br>Такой логин уже используется!';

    if (!sizeof($error)) {
        $sql = 'DELETE from `check` where `ip`=?';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('s', $ip);
        $stmt->execute();

        $sql = 'INSERT INTO `users` VALUES  ("", ?,?, ?, ?,0,0)';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('ssss', $reg['login'], $reg['password1'], $reg['email'], $reg['nick']);
        $stmt->execute();

        echo 'Регистрация аккаунта прошла упешно,
   теперь надо <a href="?page=login">войти</a> под указанными логином и паролем,
    добавить в профиль сайт и можно пользоваться сервисами!';
    } else echo '<h3>В течении регистрации были ошибки:</h3>' . implode('<br>', $error) . '<br>
<a href="index.php?page=reg&amp;reg[nick]=' . $reg['nick'] . '&amp;reg[email]=' . $reg['email'] . '&amp;reg[login]=' . $reg['login'] . '">Вернуться и попробовать ещё раз</a>';
}

###################################
###################################
function regsite3()
{
    global $reg, $sid, $our_user_id, $mysqli;
    $error = array();
    if (!$reg['if_hacker']) $error[] = 'Поле с числом незаполнено!';

    if (!$reg['description']) $error[] = 'Вы не ввели описание!';


    if (!$reg['name']) $error[] = 'Вы не ввели имя сайта!';

    if ((!$reg['url']) || ($reg['url'] == 'http://')) $error[] = 'Вы не вписали адрес!';


    $sql = 'select 1 from `check` where ((`ip`=?)and(time>?) and (rand=?)) limit 1';

    $stmt = $mysqli->prepare($sql);
    $ip=ip2long($_SERVER['REMOTE_ADDR']);
    $time=(time() - 60 * 15);
    $stmt->bind_param('sis', $ip, $time, $reg['if_hacker']);
    $stmt->execute();
    $result = $stmt->get_result();
    if (!$result->num_rows)
        $error[] = 'Введённое число не совпадает со сгенерированным!';


    $sql = 'select 1 from types where parent=? limit 1';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $sid);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows)
        $error[] = 'В этом каталоге нельзя регистрироваться! Спуститесь ниже по ветке!';

    $sql = 'select 1 from types where id="' . $sid . '" limit 1';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $sid);
    $stmt->execute();
    $result = $stmt->get_result();
    if (!$result->num_rows)
        $error[] = 'Такого каталога не существует!';
    $date = date("Y:m:d");
    if (!$error) {
        $sql = 'DELETE from `check` where `ip`=?';
        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('i', ip2long($_SERVER['REMOTE_ADDR']));
        $stmt->execute();

        $sql = 'INSERT INTO sources VALUES
  ("", ?,?, ?, ?, ?, 0, 0,0,0,?,0,0,"00")';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('sssssi', $reg['name'], $reg['description'], $sid, $reg['url'], $date, $our_user_id);
        $stmt->execute();

        if ($mysqli->insert_id)
            echo '<h1>Добавление сайта, шаг №3</h1><div width=500>Сайт зарегестрирован успешно!<br>Теперь вы можете воспользоваться нашими сервисами на <a href="index.php?page=user">странице администрирования</a></div>';
        else
            echo 'Страшная ошибка при регистрации!';
    } else
        echo '<h1>Добавление сайта, шаг №3</h1><div width=500><strong>Ошибки при регистрации:</strong>' . implode('<br>', $error) . '<a href="index.php?page=reg&amp;step=2&amp;ac=addsite&amp;reg[name]=' . $reg['name'] . '&amp;reg[url]=' . $reg['url'] . '&amp;reg[description]=' . $reg['description'] . '&amp;sid=' . $sid . '"><br>Вернуться и попробовать ещё раз</div></a>';
}

###################################
###################################
function regsite2()
{
    global $reg, $sid;
    ?>
    <h2>Добавление сайта, шаг №2</h2>
    Вы выбрали раздел "
    <?$sql = 'select name from types where id=?';
    $r = bind_int_return_row($sql, $sid);
    echo $r[0];
    ?>"&nbsp;
    <a href='?page=reg&ac=addsite'>Выбрать другой</a>
    <FORM METHOD="POST" ACTION="index.php">
        <input type='hidden' name='page' value='reg'>
        <input type='hidden' name='ac' value='addsite'>
        <input type='hidden' name='sid' value='<?= $sid ?>'>
        <input type='hidden' name='step' value='3'>
        <table width="500">
            <tr>
                <td>Название сайта (до 20 символов)</td>
                <td><input maxlength="20" class="tab_all" TYPE="text" NAME="reg[name]" value='<?= $reg['name'] ?>'></td>
            </tr>
            <tr>
                <td colspan="2">*Примечание: использование в названии сайта кавычек и некоторых других спецсимволов
                    укорачивает возможную длину названия. Пожалуйста, если вы их используете, проверьте после
                    регистрации, насколько название корректно отображается, и, если необходимо - измеите его.
                </td>
                </td></tr>
            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <? if (isset($reg['url'])) {
                $urlval = $reg['url'];
            } else {
                $urlval = 'http://';
            } ?>
            <tr>
                <td>URL главной страницы</td>
                <td><input maxlength="50" class="tab_all" TYPE="text" NAME="reg[url]" value='<?= @$urlval ?>'></td>
            </tr>
            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Описание регистрируемого сайта (до 60 символов)</td>
                <td><input class="tab_all" TYPE="text" NAME="reg[description]" value='<?= $reg['description'] ?>'
                           maxlength="60"></td>
            </tr>
            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Введите число с картинки&nbsp;<img src="random.php"></td>
                <td><input class="tab_all" TYPE="text" NAME="reg[if_hacker]"></td>
            </tr>
            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <TR>
                <TD colspan=2><input type="submit" value="Зарегистрировать" class="button"></TD>
            </TR>
        </table>
    </form>
<?
}

###################################
###################################
if (!$our_user) {
    if ($step == 2) reguser2();
    else reguser();
} elseif ($ac == 'addsite') {
    if ($step == 2) regsite2();
    elseif ($step == 3) regsite3();
    else drevo();
}
?>
