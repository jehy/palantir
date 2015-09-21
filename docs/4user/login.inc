<div align="center">
    <h1>Вход</h1>
    <? if ($ac == 'login') echo '<h2>Неправильная комбинация логин/пароль!</h2>'; ?>
    <FORM METHOD="POST" ACTION="index.php">
        <input type='hidden' name='ac' value='login'>
        <table align='center' width='350'>

            <tr>
                <td colspan="2">
                    <hr>
                </td>
            </tr>
            <tr>
                <td>Логин:</td>
                <td><input class="input_text" TYPE="text" NAME="login"></td>
            </tr>

            <tr>
                <td>Пароль:</td>
                <td><input class="input_text" TYPE="password" NAME="password"></td>
            </tr>

            <tr>
                <TD colspan=2 align="center"><input type="submit" value="Войти" width="100" class="button"></TD>
            </TR>
        </table>
    </form>
    <? if ($ac == 'login') { ?>
        Если вы забыли логин или пароль, вы можете воспользоваться <a href="index.php?page=reveal">сервисом
            восстановления пароля</a>.
    <? } ?>
