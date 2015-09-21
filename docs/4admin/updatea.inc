<?

die('Not rewritten!');

$sql = "select * from sources where id=$id";
$result = sql($sql);
$row = mysql_fetch_array($result);
?>
<FORM METHOD="POST" ACTION="index.php">
    <input type='hidden' name='page' value='22'>
    <table width="100%">
        <tr>
            <td>Каталог</td>
            <!---->
            <td><input type='text' name='parent' value='<?= $row[parent] ?>'></td>
        </tr>
        <input type="hidden" name="id" value=<?= $id ?>

        <tr>
        <td>Название сайта</td>
        <!---->
        <td><input maxlength="20" class="tab_all" TYPE="text" NAME="name" value='<?= $row[name] ?>'></td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>URL главной страницы</td>
            <!---->
            <td><input maxlength="50" class="tab_all" TYPE="text" NAME="url" value='<?= $row[url] ?>'></td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>Описание регистрируемого сайта</td>
            <td><!----><input class="tab_all" TYPE="text" NAME="description" value='<?= $row[description] ?>'
                              maxlength="60"></td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>Логин</td>
            <!---->
            <td><input class="tab_all" TYPE="text" NAME="login" value='<?= $row[login] ?>' maxlength="40"></td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>Пароль</td>
            <td><!----><input class="tab_all" TYPE="text" NAME="password2" maxlength="20" value='<?= $row[password] ?>'>
            </td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>E-mail контактного лица</td>
            <!---->
            <td><input class="tab_all" TYPE="text" NAME="email" value='<?= $row[email] ?>' maxlength="40"></td>
        </tr>

        <tr>
            <td colspan="2">
                <hr>
            </td>
        </tr>
        <tr>
            <td>Визиты по ip за сегодня</td>
            <!---->
            <td><input class="tab_all" TYPE="text" NAME="today_hosts" value='<?= $row[today_ip_hosts] ?>'
                       maxlength="40"></td>
        </tr>

        <TR>
            <TD><INPUT type="reset" value="Очистить форму" class="button"></TD>
            <TD><input type="submit" name="addrec" value="Изменить" class="button"></TD>
        </TR>
    </table>
</form>
