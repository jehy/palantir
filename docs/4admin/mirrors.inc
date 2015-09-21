<?
die('Not rewritten!');
if (!@$step) $step = 0;
if ($step == 0) {
    ?>
    <form action='index.php' method='post'>
        <table>
            <tr>
                <td colspan="2">Новое зеркало:</td>
            </tr>
            <tr>
                <td>Mirror name</td>
                <td><input type='Text' name='add[name]'></td>
            </tr>
            <tr>
                <td>UNI URL:</td>
                <td><input type='Text' name='add[url]'></td>
            </tr>
            <tr>
                <td>Status:</td>
                <td><input type='Text' name='add[status]'></td>
            </tr>
            <tr>
                <td>Priority:</td>
                <td><input type='Text' name='add[priority]'></td>
            </tr>

            <input type='hidden' name='page' value='admin'>
            <input type='hidden' name='step' value='1'>
            <input type='hidden' name='ac' value='mirrors'>
        </table>
        <input type='Submit' class='menu' value='вставить'></form>
<?
}
if ($step == 4) {
    $sql = 'DELETE FROM mirrors WHERE id="' . $nid . '"';
    sql($sql);
}
if ($step == 1) {
    $sql = 'INSERT INTO `mirrors` VALUES
  (NULL, "' . $add['name'] . '", "' . $add['url'] . '", "' . $add['priority'] . '", "' . $add['status'] . '")';
    sql($sql);
}
if ($step == 3) {
    $sql = 'UPDATE `mirrors` SET name="' . $update['name'] . '", url="' . $update['url'] . '", priority="' . $update['priority'] . '",status="' . $update['status'] . '" where id="' . $nid . '"';
#echo $sql;
    sql($sql);
} elseif ($step == 2) {
    $result = sql('SELECT * FROM mirrors WHERE id="' . $nid . '"');
    $row = mysql_fetch_array($result);
    ?>
    <form action='index.php' method='post'>
        <table>
            <tr>
                <td colspan="2">Редактировать зеркало:</td>
            </tr>
            <tr>
                <td colspan="2"><strong>ID<?= $row['id']; ?></strong></td>
            </tr>
            <input type='hidden' value='<?= $row['id']; ?>' name='nid' size='26'>
            <tr>
                <td>Name</td>
                <td><input type='text' name='update[name]' value="<?= $row['name']; ?>"></td>
            </tr>
            <tr>
                <td>UNI Url</td>
                <td><input type='text' name='update[url]' value="<?= $row['url']; ?>"></td>
            </tr>
            <tr>
                <td>Priority</td>
                <td><input type='text' name='update[priority]' value="<?= $row['priority']; ?>"></td>
            </tr>
            <tr>
                <td>Status</td>
                <td><input type='text' name='update[status]' value="<?= $row['status']; ?>"></td>
            </tr>
        </table>
        <input type='Submit' class='menu' value='Изменить'>
        <input type='hidden' name='page' value='admin'>
        <input type='hidden' name='ac' value='mirrors'>
        <input type='hidden' name='step' value='3'>
    </form>
    <hr><? } ?>
<hr>
<?
$sql = 'select * from `mirrors` order by `id` desc';
$result = sql($sql);
while ($row = mysql_fetch_array($result)) {
    ?>
    <table>
    <tr>
        <td><?= $row['name']; ?></td>
        <td>Priority=<?= $row['priority']; ?></td>
        <td>Status=<?= $row['status']; ?></td>
    </tr>
    <tr>
        <td><em><?= $row['url']; ?></em></td>
    </tr>
    </table>
    <input type='button' class='menu' value='удалить'
           onClick="window.location.href = 'index.php?page=admin&ac=mirrors&step=4&nid=<?= $row[id]; ?>'">
    <input type='button' class='menu' value='редактировать'
           onClick="window.location.href = 'index.php?page=admin&ac=mirrors&step=2&nid=<?= $row[id]; ?>'">
    <input type='button' class='menu' value='обновить'
           onClick="window.location.href = 'index.php?page=admin&ac=mirrors&step=2&nid=<?= $row[id]; ?>'"><br><br>
    <br>
    <hr>
<?
}
?>
