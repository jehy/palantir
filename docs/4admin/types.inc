<a href="index.php?page=admin">К администрированию</a><br>
<a href="index.php?page=admin&ac=types">К каталогам</a><br>
<?
DEFINE(SHOW_META, 1);
die('Not rewritten!');
function FromYandex($text)
{
    $text = explode("\n", $text);
    for ($i = 0; $i < sizeof($text); $i++) {
        $text[$i] = trim($text[$i]);
        $n = 1;
        while (is_numeric($text[$i][strlen($text[$i]) - $n]))
            $n++;
        $text[$i] = substr($text[$i], 0, (strlen($text[$i]) - $n));
        $text[$i] = trim($text[$i]);
    }
    return implode(',', $text);
}

if (($ac == 'meta') && ($parent)) {
    $sql = 'select name from types where id="' . $parent . '"';
    $result = sql($sql);
    $row = mysql_fetch_row($result);
    $row = $row[0];

    echo '<a href="index.php?page=admin&ac=meta&parent=' . $parent . '">К метам каталога "' . $row . '"</a><br><a href="index.php?page=admin&ac=meta&parent=' . $parent . '&action=add">Добавить мету в каталог "' . $row . '"</a><br>';
}
function CountMeta($parent)
{
    $sql = 'SELECT `id` FROM `types_meta` WHERE (type_id=' . $parent . ')';
    $result = sql($sql);
    return mysql_num_rows($result);
}

if ($ac == 'meta') {

    if (!$action) {
        $sql = 'select * from types_meta where type_id="' . $parent . '"';
        $result = sql($sql);
        $s_num = ceil(mysql_num_rows($result) / SHOW_META);
        for ($i = 0; $i < $s_num; $i++) {
            if ($i == $frompage)
                $l = ' &nbsp;<a href="' . COMMON_URL . 'index.php?page=admin&ac=meta&parent=' . $parent . '&frompage=' . $i . '" style="font-weight:bold;color: #fff;font-size:larger;">[' . $i . ']</a>';
            else
                $l = ' &nbsp;<a href="' . COMMON_URL . 'index.php?page=admin&ac=meta&parent=' . $parent . '&frompage=' . $i . '">' . $i . '</a>';
            $showpages .= $l;
        }
        echo $showpages;

        $sql = 'select * from types_meta where type_id="' . $parent . '" order by id LIMIT ' . (SHOW_META * $frompage) . ',' . SHOW_META;
        $result = sql($sql);
        ?>
        <form action='index.php'>
        <input type='hidden' name='page' value='admin'>
        <input type='hidden' name='ac' value='meta'>
        <input type='hidden' name='parent' value='<?= $parent; ?>'><br>
        <input type='hidden' name='action' value='edit'><?
        while ($row = mysql_fetch_array($result)) {
            ?>
            Title:<br>
            <textarea cols="50" rows="1" name='title[<?= $row['id']; ?>]'><?= $row['title']; ?></textarea><br>
            Description:<br>
            <textarea cols="50" rows="2" name='description[<?= $row['id']; ?>]'><?= $row['description']; ?></textarea>
            <br>
            Keywords:<br>
            <input type="checkbox" name="import" value="yandex">Import from Yandex<br>
            <textarea cols="50" rows="2" name='keywords[<?= $row['id']; ?>]'><?= $row['keywords']; ?></textarea><br>
            <input type="checkbox" name='delete[<?= $row['id']; ?>]' value="1">Удалить<br>
        <?
        }
        ?><input type='Submit' value='изменить' class="button"></form><?
        echo $showpages;
    } elseif ($action == 'add') {
        if ($step == 2) {
            if ($import == 'yandex')
                $keywords = FromYandex($keywords);
            $sql = 'insert into types_meta values("","' . $parent . '","' . $title . '","' . $description . '","' . $keywords . '")';
            sql($sql);
            if (!mysql_affected_rows())
                echo 'Ошибка: не добавлено!';
            else
                echo 'Добавлено!';
        } else {
            ?>
            <form action='index.php'>
            <input type='hidden' name='page' value='admin'>
            <input type='hidden' name='ac' value='meta'>
            <input type='hidden' name='action' value='add'>
            <input type='hidden' name='step' value='2'>
            <input type='hidden' name='parent' value='<?= $parent; ?>'><br>
            Title:<br>
            <textarea cols="50" rows="1" name='title'></textarea><br>
            Description:<br>
            <textarea cols="50" rows="2" name='description'></textarea><br>
            Keywords:<br>
            <input type="checkbox" name="import" value="yandex">Import from Yandex<br>
            <textarea cols="50" rows="2" name='keywords'></textarea><br>
            <input type='Submit' value='вставить' class="button">
            </form><?
        }
    } elseif ($action == 'edit') {

        foreach ($title as $id => $title1) {
            if ($delete[$id]) {
                $sql = 'delete from types_meta where id="' . $id . '"';
                sql($sql);
                if (!mysql_affected_rows())
                    echo 'Ошибка: не удалено!';
                else
                    echo 'Удалено!';
            } else {
                $description1 = $description[$id];
                $keywords1 = $keywords[$id];
                if ($import == 'yandex')
                    $keywords1 = FromYandex($keywords1);
                $sql = 'update `types_meta` set `title`="' . $title1 . '",`description`="' . $description1 . '",`keywords`="' . $keywords1 . '" where `id`="' . $id . '"';
                #echo $sql;
                sql($sql);
                if (!mysql_affected_rows())
                    echo 'Ошибка: не изменено!<br>' . $mysqli->error . $sql;
                else
                    echo 'Изменено!';
            }
        }
    }
} else {
    if (!$action) {
        ?>
        <form action='index.php'>
            <input type='hidden' name='page' value='admin'>
            <input type='hidden' name='ac' value='types'>
            <input type='text' value='name' name='name'>
            <input type='text' value='name_eng' name='name_eng'>
            <input type='text' value='parent' name='parent'><br>
            <input type='hidden' name='action' value='addtype'>
            <input type='Submit' value='вставить'>
        </form><?
    }


    if ($action == 'delete') {
        $sql = 'DELETE FROM types WHERE id="' . $id . '"';
        $result = sql($sql);
        ?>Не забудьте о ресурсах, которые возможно были зарегестрированы в этом каталоге.<?
#$sql = 'DELETE FROM sources WHERE type="'.$id.'"';
#$result = sql($sql);
    }

    if ($action == 'addtype') {
        $sql = 'INSERT INTO types VALUES ("", "' . $parent . '", "' . $name . '", "' . $name_eng . '")';
        $result = sql($sql);
        if (mysql_affected_rows($result))
            echo 'Добавлено';
        else
            echo 'Ошибка при добавлении';
    } elseif ($action == 'edit') {
        if ($step != 2) {
            $sql = 'SELECT * FROM types WHERE id="' . $id . '"';
#echo $sql;
            $result = sql($sql);
            while ($row = mysql_fetch_array($result)) {
                ?>
                <form action='index.php'>
                    <strong>ID #<?= $row[id]; ?></strong>
                    <input type='hidden' value='<?= $row['id']; ?>' name='id'>
                    <br>Название<br>
                    <input type='text' value='<?= $row['name']; ?>' name='name'>
                    <br>Родительский каталог<br>
                    <input type='text' value='<?= $row['parent']; ?>' name='parent'>
                    <br>Англицкое название<br>
                    <input type='text' value='<?= $row['name_eng']; ?>' name='name_eng'>
                    <input type='hidden' value='edit' name='action'>
                    <input type='hidden' value='2' name='step'>
                    <input type='hidden' name='page' value='admin'>
                    <input type='hidden' value='types' name='ac'>
                    <input type='Submit' name='update' class='button' value='Изменить'>
                </form>
                <hr><?
            }
        } else {
            $sql = 'UPDATE types set parent="' . $parent . '", name="' . $name . '",name_eng="' . $name_eng . '" where id="' . $id . '"';
            sql($sql);
        }
    }
    ?>
    <hr>
    <table width="100%">
    <tr>
        <td>ID название</td>
        <td>Родитель</td>
        <td>Меты</td>
        <td>Править меты</td>
        <td>Стереть</td>
        <td>Редактировать</td>
    </tr>
    <?
    $sql = "select * from types order by 'id' desc";
    $result = sql($sql);
    while ($row = mysql_fetch_array($result)) {
        $a = CountMeta($row['id']);
        $b = CountPages($row['id']);
        $e = $a / $b;
        if ($e < 1) $c = 'red'; else$c = 'green';
        $b = $a . '/' . $b;
        echo '<tr><td>' . $row['id'] . ' ' . $row['name'] . '</td><td>' . $row['parent'] . '</td>
<td bgcolor="' . $c . '">' . $b . '</td>
<td><a href="index.php?page=admin&ac=meta&parent=' . $row['id'] . '">Meta</a></td><td><a href="index.php?page=admin&ac=types&action=delete&id=' . $row['id'] . '">стереть</a></td>
<td><a href="index.php?page=admin&ac=types&action=edit&id=' . $row['id'] . '">редактировать</a></td></tr>';
    }
    ?>
    </table><? } ?>