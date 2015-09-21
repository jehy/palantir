<h2>Количество визитов на ресурс по часам:</h2>
<table width="200">
    <tr>
        <td align='center'>Часы&nbsp;&nbsp;</td>
        <td align='center'>&nbsp;&nbsp;Визиты</td>
    </tr><?
    $sql = 'select count(*) as visits,time from addition where site_id=? group by time order by time';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $site_id);
    $stmt->execute();
    $result = $stmt->get_result();
    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
        echo '<tr><td>' . $row['time'] . '</td><td>' . $row['visits'] . '</td></tr>';
    }
    ?></table>
