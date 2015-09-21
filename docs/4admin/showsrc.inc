<form action="index.php" method="POST">
<input type="hidden" value="admin" name='page'>
<input type="hidden" value="showsrc" name='ac'>
<input type="hidden" value="show" name='action'>
<?
die('Not rewritten!');
if (!isset($show['fields'])) {
    $show['fields'][0] = 1;
    $show['fields'][1] = 1;
    $show['fields'][7] = 1;
    $show['actions']['DeleteSrc'] = 1;
}
$fields_s = '';
$fields = 'sources.id,sources.name,users.login,users.email,users.password,sources.description,sources.url,sources.today_hosts,sources.total_hosts,sources.today_hits,sources.total_hits,sources.reg';
$fields_n = 'ID,название,логин_пользователя,email_пользователя,пароль_пользователя,описание,УРЛ,хосты_сегодня,хостов_всего,хиты_сегодня,хитов_всего,дата_регистрации';
$links = 'DeleteSrc,EditSrc,DeleteUser,EditUser,Referers,Browsers';
$links_n = 'Удалить_ресурс,Править_ресурс,Удалить_пользователя,Править_Пользователя,Рефереры,Браузеры';
$fields = explode(',', $fields);
$fields_n = explode(',', $fields_n);
$links = explode(',', $links);
$links_n = explode(',', $links_n);
echo '<table><tr><td><strong>Показывать поля:</strong><br>';
for ($i = 0; $i < sizeof($fields); $i++) {
    if (isset($show['fields'][$i])) {
        $c = ' checked';
        $fields_s .= ',' . $fields[$i];
    } else $c = '';
    echo '<input' . $c . ' type="checkbox" value="1" name="show[fields][' . $i . '][]">' . $fields_n[$i] . '<br>';
}
echo '</td><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td><td valign="top"><strong>Показывать ссылки на действия:</strong><br>';

$links_s = '';
for ($i = 0; $i < sizeof($links); $i++) {
    if (@$show['actions'][$links[$i]]) {
        $c = ' checked';
        $links_s .= ',' . $links[$i];
    } else $c = '';
    echo '<input' . $c . ' type="checkbox" value="1" name="show[actions][' . $links[$i] . '][]">' . $links_n[$i] . '<br>';
}
echo '</td></tr></table>';
?><br>


<strong>Критерий:</strong><input type="text" name="show[where]"
                                 value='<? if (@$show['where']) echo stripslashes($show['where']); else echo '(1=1)'; ?>'>
<br><strong>Сортировать по:</strong>
<select name="show[sort]">
    <?
    $sort = '';
    for ($i = 0; $i < sizeof($fields); $i++) {
        if (@$show['sort'] == $i) {
            $c = ' selected';
            $sort = $fields[$i];
        } else $c = '';
        echo '<option' . $c . ' value="' . $i . '">' . $fields_n[$i] . '</option>';
    }
    ?>
</select>
<input type="checkbox" name="show[desc]" value="1"<? if (@$show['desc']) echo ' checked'; ?>>
В обр. порядке<br>
<br>
<input type="submit" value="Отправить">
<script language='JavaScript'> <!--
    function confirmDel() {
        if (confirm('Вы действительно хотите удалить этого участника?')) {
            return true;
        } else {
            return false;
        }
    }
    // --> </script>
<?
$a = 1;
//if(!@$action)$action='show';
//print_R($show);
//if(!@$show['fields'])$show['fields']=array('';
if (@$action == 'DeleteSrc')
{
    $sql = 'delete from sources where id="' . $show_id . '" limit 1';
    sql($sql);
    if (mysql_affected_rows()) echo '<h3>Удалено!</h3>'; else echo '<h3 color="red">Не найдено!!</h3>';
} elseif (@$action == 'DeleteUser') {
    $sql = 'select sources.user_id from sources where id="' . $show_id . '" limit 1';
    $row = mysql_fetch_array(sql($sql));
    $sql = 'delete from users where id="' . $row['user_id'] . '" limit 1';
    sql($sql);
    if (mysql_affected_rows()) echo '<h3>Удален!</h3>'; else echo '<h3 color="red">Не найден!!</h3>';
} elseif (@$action == 'Referers') {
    $sql = 'select name from sources where id="' . $show_id . '"';
    $result = sql($sql);
    $row = mysql_fetch_array($result);
    echo '<h2>Рефереры сайта</h2><strong>ID# ' . $show_id . '</strong> ' . $row['name'];
    $sql = 'select count(*) as quan,referer from addition where site_id="' . $show_id . '" group by referer order by quan desc';
    $result = sql($sql);
    echo '<table cellpadding="0" cellspacing="0" border="1">';
    while ($row = mysql_fetch_array($result)) {
        if (!$row['referer']) echo '<tr><td>' . $row['referer'] = 'Напрямую</td>
    <td>' . $row['quan'] . '</td></tr>';
        else echo '<tr><td><a href="' . $row['referer'] . '">' . $row['referer'] . '</a></td>
    <td>' . $row['quan'] . '</td></tr>';
    }
    echo '</table>';
} elseif (@$action == 'Browsers') {
    $sql = 'select name from sources where id="' . $show_id . '"';
    $result = sql($sql);
    $row = mysql_fetch_array($result);
    echo '<h2>Браузеры сайта</h2><strong>ID# ' . $show_id . '</strong> ' . $row['name'];
    $sql = 'select useragent,count(*) as quan from addition where site_id="' . $show_id . '" group by useragent order by quan desc';
    $result = sql($sql);
    echo '<table cellpadding="0" cellspacing="0" border="1">';
    while ($row = mysql_fetch_array($result)) {
        if (!$row['useragent']) echo '<tr><td>' . $row['referer'] = 'Без браузера:))</td>
    <td>' . $row['quan'] . '</td></tr>';
        else echo '<tr><td>' . $row['useragent'] . '</td>
    <td>' . $row['quan'] . '</td></tr>';
    }
    echo '</table>';
} elseif (@$action == 'show') {

//echo'fields '.$fields_s.'<br>actions'.$links_s.'<br>sort'.$sort;
    $d = '';
    if (@$show['desc']) $d = ' desc';
    if (!@$show['page']) $show['page'] = 0;
    if (!@$show['where']) $show['where'] = '1=1';
    $sql = 'select sources.url as dest,sources.id as link' . $fields_s . ' from users,sources where((users.id=sources.user_id)&&(' . stripslashes($show['where']) . ')) order by ' . $sort . $d;
//echo $sql;
    $result = sql($sql);
    $pages = mysql_num_rows($result);
    $pages = ceil($pages / 50);
    echo '<br><br>';
    $d = '';
    for ($i = 0; $i < $pages; $i++) {
        if ($i == @$show['page']) $d = '  style="background-color: Gray;"';
        echo '<input' . $d . ' type="submit" name="show[page]" value="' . $i . '">&nbsp;';
        $d = '';
    }
    $sql .= ' limit ' . ($show['page'] * 50) . ',50';
//echo '<br>'.$sql;
    $result = sql($sql);
    echo '<table border="1"><tr>';
    if (@$show['fields']) {
        /*print_R($show);
        reset ($show['fields']);
        print_R($show);
        foreach ($show['fields'] as $key=>$entry)
        {
        echo'<td>'.$fields_n[$key].$key.$entry.'</td>';
        }*/
        for ($i = 0; $i < 100; $i++) {
            if (isset($show['fields'][$i])) echo '<td>' . $fields_n[$i] . '</td>';
        }
    }
    if (@$show['actions']) foreach ($show['actions'] as $key => $entry) {
        echo '<td>' . $key . '</td>';
    }
    echo '</tr>';
    while ($row = mysql_fetch_array($result)) {
        echo '<tr>';
        foreach ($row as $key => $entry) {
            if ((!is_numeric($key)) && ($key != 'link') && ($key != 'dest'))
                if (($key == 'id') || ($key == 'name')) echo '<td><a href="' . $row['dest'] . '">' . $entry . '</a></td>';
                else echo '<td>' . $entry . '</td>';
        }
        if (@$show['actions']) foreach ($show['actions'] as $key => $entry) {
            echo '<td><a href="index.php?page=admin&ac=showsrc&action=' . $key . '&show_id=' . $row['link'] . '">' . $key . '</a></td>';
        }
    }
    echo '</tr>';
    echo '</table>';
    #mysql_free_result($result);
} elseif ($action == 'EditSrc') {
    if (@$step != 2) {
        $sql = 'select * from sources where id="' . $show_id . '" limit 1';
        $result = sql($sql);
        $row = mysql_fetch_array($result);
        ?>
        <FORM METHOD="POST" ACTION="index.php">
        <input type='hidden' name='page' value='admin'>
        <input type='hidden' name='action' value='EditSrc'>
        <input type='hidden' name='step' value='2'>
        <table width="100%">
            <tr>
                <td>Каталог</td>
                <!---->
                <td>
                    <input type='text' name='edit[parent]' value='<?= $row['parent'] ?>' class="tab_all"></td>
            </tr>
            <input type="hidden" name="show_id" value=<?= $show_id ?>

            <tr>
            <td colspan="2">
                <hr>
            </td>
            </tr>
            <tr>
                <td>Название сайта</td>
                <!---->
                <td><input maxlength="20" class="tab_all" TYPE="text" NAME="edit[name]" value='<?= $row['name'] ?>'>
                </td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>URL главной страницы</td>
                <!---->
                <td><input maxlength="50" class="tab_all" TYPE="text" NAME="edit[url]" value='<?= $row['url'] ?>'></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Описание регистрируемого сайта</td>
                <td><!----><input class="tab_all" TYPE="text" NAME="edit[description]"
                                  value='<?= $row['description'] ?>' maxlength="60"></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Визиты по ip за сегодня</td>
                <!---->
                <td><input class="tab_all" TYPE="text" NAME="edit[today_hosts]" value='<?= $row['today_hosts'] ?>'
                           maxlength="40"></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Идентификатор пользователя</td>
                <!---->
                <td><input class="tab_all" TYPE="text" NAME="edit[user_id]" value='<?= $row['user_id'] ?>'
                           maxlength="40"></td>
            </tr>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Баннерный коэффициент</td>
                <!---->
                <td><input class="tab_all" TYPE="text" NAME="edit[ban_koef]" value='<?= $row['ban_koef'] ?>'
                           maxlength="40"></td>
            </tr>

            <TR>
                <TD><INPUT type="reset" value="Очистить форму" class="button"></TD>
                <TD><input type="submit" value="Изменить" class="button"></TD>
            </TR>
        </table>
        </form><?
    } else {
        $sql = 'update sources set parent="' . $edit['parent'] . '", user_id="' . $edit['user_id'] . '", ban_koef="' . $edit['ban_koef'] . '",
 name="' . $edit['name'] . '",
url="' . $edit['url'] . '", today_hosts="' . $edit['today_hosts'] . '",
description="' . $edit['description'] . '" where id="' . $show_id . '" limit 1';
//echo $sql;
        sql($sql);
        if (mysql_affected_rows()) {
            $sql = 'select * from sources where id="' . $show_id . '"';
            $result = sql($sql);
            $row = mysql_fetch_array($result);
            echo "<h3 align='center'>Данные изменены</h3>
<TABLE width='100%'>
    <TD colSpan=2>
      <HR>
    </TD></TR>
  <TR>
    <TD>Название сайта</TD>
    <TD>$row[name]</TD></TR>
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>
  <TR>
    <TD>Адрес сайта:</TD><!---->
    <TD>$row[url]</TD></TR>

  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>

  <TR>
    <TD>Описание сайта:</TD>
    <TD>$row[description]</TD></TR>
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>

  <TR>
    <TD>Хосты сегодня:</TD>
    <TD>$row[today_hosts]</TD></TR>
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>

  <TR>
    <TD>Идентификатор пользователя:</TD>
    <TD>$row[user_id]</TD></TR>
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>

  <TR>
    <TD>Баннерный коэффициент:</TD>
    <TD>$row[ban_koef]</TD></TR></table>";
        } else echo '<br>Случилась лажа!<br>' . $sql;
    }

}
elseif ($action == 'EditUser') {
if (@$step != 2) {
$sql = 'select sources.user_id from sources where id="' . $show_id . '" limit 1';
$row = mysql_fetch_array(sql($sql));
$sql = 'select * from users where id="' . $row['user_id'] . '"';
$result = sql($sql);
$row = mysql_fetch_array($result);
?>
<table width="100%">
    <FORM METHOD="POST" ACTION="index.php">
        <input type='hidden' name='page' value='admin'>
        <input type='hidden' name='action' value='EditUser'>
        <input type="hidden" name="show_id" value="<?= $row['id'] ?>">
        <input type='hidden' name='step' value='2'>
        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>Логин</td>
            <!---->
            <td><input class="tab_all" TYPE="text" NAME="edit[login]" value='<?= $row['login'] ?>' maxlength="40">
            </td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>Пароль</td>
            <td><!----><input class="tab_all" TYPE="text" NAME="edit[password]" maxlength="20"
                              value='<?= $row['password'] ?>'></td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>E-mail</td>
            <!---->
            <td><input class="tab_all" TYPE="text" NAME="edit[email]" value='<?= $row['email'] ?>' maxlength="40">
            </td>
        </tr>
        <TR>
            <TD><INPUT type="reset" value="Очистить форму" class="button"></TD>
            <TD><input type="submit" value="Изменить" width="100" class="button"></TD>
        </TR>
</table>
</form><?
} else {
    $sql = 'update users set email="' . $edit['email'] . '", login="' . $edit['login'] . '",
password="' . $edit['password'] . '" where id="' . $show_id . '" limit 1';
//echo $sql;
    sql($sql);
    if (mysql_affected_rows()) {
        $sql = 'select * from users where id="' . $show_id . '"';
        $result = sql($sql);
        $row = mysql_fetch_array($result);
        echo "<h3 align='center'>Данные изменены</h3>
<TABLE width='100%'>
    <TD colSpan=2>
      <HR>
    </TD></TR>
  <TR>
    <TD>Логин</TD>
    <TD>$row[login]</TD></TR>
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>
  <TR>
    <TD>Пароль</TD><!---->
    <TD>$row[password]</TD></TR>

  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>

  <TR>
    <TD>Е-мэйл</TD>
    <TD>$row[email]</TD></TR>
    </table>";
    } else echo '<br>Случилась лажа!<br>' . $sql;
}
}
?>
