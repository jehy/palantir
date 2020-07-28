<a href='index.php??page=user'>Вернуться в систему администрирования</a><br>
<a href="index.php?page=banner">В систему управления баннерами</a><br>
<?
$sql = "select sources.name from users,sources where ((login=?)&&(password=sha1(CONCAT(?, "666")))) and sources.id=?";

$stmt = $mysqli->prepare($sql);
$stmt->bind_param('ssi', $login, $password, $my_id);
$stmt->execute();
$result = $stmt->get_result();
if ($result->num_rows) {
    $row = $result->fetch_array(MYSQLI_ASSOC);
    ?>
    Cтраницы, с которых кликали баннеры сайта"<strong><?= $row[name]; ?></strong>":<br>
    <table>
    <tr>
        <td>Страница:</td>
        <td>Кол-во посещений:</td>
        <td></td>
    </tr>
    <? $sql = "select distinct url from clicks where site_id=?";

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $my_id);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
            $sql = "select count(1) from clicks where ((site_id=?)and(url=?))";
            $stmt = $mysqli->prepare($sql);
            $stmt->bind_param('is', $my_id, $row[url]);
            $stmt->execute();
            $result = $stmt->get_result();
            $n = $result->num_rows;
            echo "<tr><td><a href='" . $row[url] . "'>" . $row[url] . "</a></td><td>" . $n . "</td></tr>";
        }
        ?></table><?
    }
} else echo "<span class='larger2'>Ошибка: Статистика этого сайта вам недоступна!</span>"; ?>
