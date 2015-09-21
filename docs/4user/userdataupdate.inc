<?
if ($step == 2) {
    ?>
    <a href='?page=user'>Вернуться в систему администрирования</a><br>
    <?if (!$error)
        echo 'Профиль успешно изменён!';
    else
        echo 'Ошибки при изменении профиля:' . $error . '<br><a href="index.php?page=user&ac=changedata">Попробовать ещё</a>';
} else {
    ?><a href='?page=user'>Вернуться в систему администрирования</a><br>
    <?$sql = 'select * from users where id=? limit 1';
    $row = bind_int_return_array($sql, $our_user_id);
    ?>
    <FORM action='index.php' method='post'>
        <input type="hidden" name="page" value="user">
        <input type="hidden" name="ac" value="changedata">
        <input type="hidden" name="step" value="2">
        <TABLE width='100%'>
            <tr>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>
            <TR>
                <TD>Логин:</TD>
                <TD><INPUT class='tab_all' name='loginx' value='<?= $row['login']; ?>'></TD>
            </TR>
            <tr>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>
            <TR>
                <TD>Пароль:</TD>
                <TD><INPUT class='tab_all' value='<?= $row['password']; ?>' name='passwordx'></TD>
            </TR>
            <tr>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>
            <TR>
                <TD>E-mail:</TD>
                <TD><INPUT class='tab_all' name='emailx' value='<?= $row['email']; ?>'></TD>
            </TR>
            <tr>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>
            <TR>
                <TD>Обращение:</TD>
                <TD><INPUT class='tab_all' name='nickx' value='<?= $row['nick']; ?>'></TD>
            </TR>
            <tr>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>
            <TR>
                <TD><INPUT type='reset' value='Cбросить изменения' class="button"></TD>
                <TD><input type='submit' value='Изменить' class="button"></TD>
            </TR>
        </TABLE>
    </FORM>
<? } ?>