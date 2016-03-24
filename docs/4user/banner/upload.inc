<?
if ($step == 2) {
    $error = array();
    $fimg_name = $_FILES['fimg']['name'];
    $fimg_type = $_FILES['fimg']['type'];
    $fimg_size = $_FILES['fimg']['size'];
    $s = getimagesize($_FILES['fimg']['tmp_name']);
    $s = explode('"', $s[3]);
    $fimg_width = $s[1];
    $fimg_height = $s[3];
    $fimg_type = str_replace('image/', '', $fimg_type);
    $fimg_type = str_replace('pjpeg', 'jpeg', $fimg_type);
    $fimg_type = str_replace('x-png', 'png', $fimg_type);
    $allowed = array('gif', 'jpeg', 'png');
    if (!is_uploaded_file($_FILES['fimg']['tmp_name']))
        $error[] = '<br>Файл не был выбран!<br>';
    elseif (!in_array($fimg_type, $allowed))
        $error[] = 'Недопустимое расширение!<br><strong>' . $fimg_type . '</strong> не поддерживается!<br>';
    elseif (($fimg_width > $network[$size]['width'] + 10) || ($fimg_width < $network[$size]['width'] - 10)
        || ($fimg_height > $network[$size]['height'] + 10) || ($fimg_height < $network[$size]['height'] - 10)
    )
        $error[] = 'Слишком большое отклонение размера баннера!<br>' . $fimg_width . '*' . $fimg_height . ' вместо ' . $network[$size]['width'] . '*' . $network[$size]['height'] . '!<br>';
    if ((($fimg_size > (1024 * 20)) && ($size == 1)) ||
        (($fimg_size > (1024 * 30)) && ($size == 2)) ||
        (($fimg_size > (1024 * 40)) && ($size == 3))
    )
        $error[] = 'Слишком большой размер файла!<br>';
    if (!sizeof($error)) {
        $sql = 'insert into banners values("", ?,?,?,0,0,?,1)';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('issi', $site_id, $name, $fimg_type, $size);
        $stmt->execute();

        if ($bid = $mysqli->insert_id) {
            $NewName = 'uni/banners/imgs/img_' . $bid . '.' . $fimg_type;
            if (!copy($_FILES['fimg']['tmp_name'], $NewName)) {
                echo 'Непредвиденная файловая ошибка!! Сообщите администраторам!';
                error_addlog('Не получилось скопировать баннер ' . $bid . '.' . $fimg_type);
            } else {
                ?>
                Баннер закачан успешно:<br>
                <img src="<?= COMMON_URL; ?>showban.php?id=<?= $bid; ?>"><br>
                <a href="index.php?page=banner&ac=upload&site_id=<?= $site_id; ?>">Закачать ещё баннер</a><br>
                <a href="index.php?page=user">Вернуться к администрированию</a>
            <?
            }
        } else echo 'Непредвиденная ошибка базы данных!! Сообщите администраторам!';
    } else echo implode('<br>', $error) . '<br><a href="index.php?page=banner&ac=upload&site_id=' . $site_id . '">Назад</a><br>';
} else {
    ?><a href='index.php?page=user'>Вернуться к администрированию</a><br>
    Возможна загрузка изображений типа jpeg, gif, png.<br>
    Максимальный размер файлов:<br>
    Для 88*31 - 20 кб;<br>
    Для 100*100 - 30 кб;<br>
    Для 468*60 - 40 кб;<br>
    <strong><span class="larger">Внимание!</span> Закачивайте баннер того стандарта, баннер которого вы поставите у себя на
        сайте (если вы загрузили несколько типов баннеров, то и код надо ставить для именно этих типов). Имеется в виду,
        что если вы закачали баннер размера 88*31 и 468*60, то ставьте код для баннера 88*31 и 468*60 и никакой другой,
        например.</strong><br>
    <form action='index.php' method='post' enctype='multipart/form-data'>
        <table border='0'>
            <tr>
                <td>Укажите стандарт баннерной сети для закачиваемого баннера:</td>
            </tr>
            <tr>
                <td><select name="size">
                        <option value='1' selected>сеть 88*31 (размер счётчика)
                        <option value='2'>сеть 100*100
                        <option value='3'>сеть 468*60 (большой размер)
                    </select></td>
            </tr>
            <tr>
                <td>Выберите файл вашего баннера:</td>
            </tr>
            <script>
                <!--
                function loadimg(url) {
                    if (url) {
                        var k = document.getElementById("img2load");
                        k.src = url
                    }
                }
                //-->
            </script>
            <tr>
                <td><input type="file" name="fimg" id='file' size='20' accept='image/jpeg' align='top'
                           onchange='loadimg(this.value);'></td>
            </tr>
            <tr>
                <td><img align='left' name='img2load' id='img2load' src='graphic/s.gif' border='0' alt=''></td>
            </tr>
            <tr>
                <td><input type='hidden' name='site_id' value='<?= $site_id; ?>'></td>
            </tr>
            <tr>
                <td>Название баннера:</td>
            </tr>
            <tr>
                <td><input type='text' name='name' value='баннер№<?
                    $sql = 'select (count(*)+1) from banners where site_id=?';
                    $r = bind_int_return_row($sql, $site_id);
                    echo $r[0];
                    ?>'></td>
            </tr>
            <input type='hidden' name='page' value='banner'>
            <input type='hidden' name='ac' value='upload'>
            <input type='hidden' name='step' value='2'>
            <tr>
                <td><input type='submit' value='Закачать' class="button"></td>
            </tr>
        </table>
    </form>
<? } ?>