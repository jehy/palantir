<?
if ($step == 2) {
    $sql = 'select * from sources where ((user_id=?)and(id=?)) limit 1';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('ii', $our_user_id, $site_id);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {

        $sql = 'update sources set
  name=?, description=?, url=? where id=? limit 1';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('sssi', $name, $description, $url, $site_id);
        $stmt->execute();

        $sql = 'select * from sources where id=? limit 1';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('i', $site_id);
        $stmt->execute();
        $result = $stmt->get_result();
        $row = $result->fetch_array(MYSQLI_ASSOC);
        ?>
        <h3 align='center'>Данные изменены</h3><a href='?page=user'>Вернуться к администрированию</a>
        <TABLE width='100%'>
            <tr>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>
            <TR>
                <TD>Название сайта</TD>
                <TD><?= $row['name']; ?></TD>
            </TR>
            <TR>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>
            <TR>
                <TD>Адрес сайта:</TD>
                <!---->
                <TD><?= $row['url']; ?></TD>
            </TR>

            <TR>
                <TD colSpan=2>
                    <HR>
                </TD>
            </TR>

            <TR>
                <TD>Описание сайта:</TD>
                <TD><?= $row['description']; ?></TD>
            </TR>
        </table>
    <?
    } else echo 'Неправильный идентификатор сайта.';
} else {

    $sql = 'select * from sources where ((user_id=?)and(id=?)) limit 1';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('ii', $our_user_id, $site_id);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        $row = $result->fetch_array(MYSQLI_ASSOC);?>
        <a href='?page=user'>Вернуться к администрированию</a><br>
        <FORM action='index.php' method='post'>
            <input type='hidden' name='page' value='user'>
            <input type='hidden' name='ac' value='changesitedesc'>
            <input type='hidden' name='step' value='2'>
            <input type='hidden' name='site_id' value='<?= $row['id']; ?>'>
            <TABLE width='100%'>
                <TR>
                    <TD colSpan=2>
                        <HR>
                    </TD>
                </TR>
                <TR>
                    <TD>Название сайта:</TD>
                    <!---->
                    <TD><INPUT class='input_text' name='name' value='<?= masktags($row['name']); ?>'></TD>
                </TR>
                <TR>
                    <TD colSpan=2>
                        <HR>
                    </TD>
                </TR>
                <TR>
                    <TD>Адрес сайта:</TD>
                    <!---->
                    <TD><INPUT class='input_text' value='<?= masktags($row['url']); ?>' name='url'></TD>
                </TR>
                <TR>
                    <TD colSpan=2>
                        <HR>
                    </TD>
                </TR>
                <TR>
                    <TD>Описание сайта:</TD>
                    <TD><!----><INPUT class='input_text' name='description'
                                      value='<?= masktags($row['description']); ?>'></TD>
                </TR>
                <TR>
                    <TD colSpan=2>
                        <HR>
                    </TD>
                </TR>
                <TR>
                    <TD colspan=2><input type='submit' value='Изменить' class="button"></TD>
                </TR>
            </TABLE>
        </FORM>
    <?
    } else echo 'Вы не имеете прав на администрирование этого сайта!';
}
?>
