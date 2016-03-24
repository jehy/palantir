<a href='?page=user'>Вернуться в систему администрирования</a><br>
<a href="index.php?page=banner&site_id=<?= $site_id; ?>&ac=view">В систему управления баннерами</a><br>
<table border="1" cellpadding="0" cellspacing="0">
    <tr>
        <td>URL</td>
        <td>Clicks</td>
    </tr>
    <?

    echo 'Cтраницы, с которых кликали на баннер cайта "<strong>' . GetName($site_id) . '</strong>" за последние 3 дня:</div><br>';
    $sql = 'select url,count(*) as quan from clicks where site_id=? group by url';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $site_id);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
            echo "<tr><td><a target='_blank' href='" . $row['url'] . "'>" . $row['url'] . "</a></td><td>" . $row['quan'] . "</td></tr>";
        }
    } else echo "<div align='center'><strong>На ваш баннер не кликали.</strong></div>";
    ?></table>
