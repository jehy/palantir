<?
if ($error) {
    echo "Ошибки:<br>$error";
}
$sql = "select * from users where login=?";

$stmt = $mysqli->prepare($sql);
$stmt->bind_param('s', $login);
$stmt->execute();
$result = $stmt->get_result();
$row = $result->fetch_array(MYSQLI_ASSOC)
?><a href='?page=admin'>Вернуться к администрированию</a><br>
<FORM action='?page=15' method='post'>
    <TABLE width='100%'>
        <tr>
            <TD colSpan=2>
                <HR>
            </TD>
        </TR>
        <TR>
            <TD>Логин:</TD>
            <TD><INPUT class='tab_all' name='loginx' value='<?= $row[login]; ?>'></TD>
        </TR>
        <tr>
            <TD colSpan=2>
                <HR>
            </TD>
        </TR>
        <TR>
            <TD>Пароль:</TD>
            <TD><INPUT class='tab_all' value='<?= $row[password]; ?>' name='passwordx'></TD>
        </TR>
        <tr>
            <TD colSpan=2>
                <HR>
            </TD>
        </TR>
        <TR>
            <TD>E-mail:</TD>
            <TD><INPUT class='tab_all' name='emailx' value='<?= $row[email]; ?>'></TD>
        </TR>
        <tr>
            <TD colSpan=2>
                <HR>
            </TD>
        </TR>
        <TR>
            <TD>Обращение:</TD>
            <TD><INPUT class='tab_all' name='nickx' value='<?= $row[nick]; ?>'></TD>
        </TR>
        <tr>
            <TD colSpan=2>
                <HR>
            </TD>
        </TR>
        <TR>
            <TD><INPUT width='100' type='reset' value='Cбросить изменения'
                       style='color: white; background: url(graphic/blue_menu_button.gif); font-size: 12px;'></TD>
            <TD><input type='submit' name='addrec' value='Изменить' width='100'
                       style='color: white; background: url(graphic/blue_menu_button.gif); font-size: 12px;'></TD>
        </TR>
    </TABLE>
</FORM>