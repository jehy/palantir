<table>
    <?
    $sql = 'select * from error_log';
    $result = sql($sql);
    if (!$result->num_rows)
        echo 'Ошибок нет!';
    while ($row = $result->fetch_array(MYSQLI_ASSOC))
        echo '<tr><td>' . $row['date'] . '</td><td>' . $row['script'] . '</td><td>' . $row['page'] . '</td></tr><tr><td colspan=3>' . $row['text'] . '</td></tr>'; ?>
</table>