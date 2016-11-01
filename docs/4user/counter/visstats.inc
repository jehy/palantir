Сведения о браузерах посетителей сайта "<strong><?= GetName($site_id); ?>
</strong>":<br>
<?


$sql = "SELECT OS, COUNT(OS) AS freq FROM
(SELECT
 CASE
   WHEN useragent LIKE '%iPad%' THEN 'iPad'
   WHEN useragent LIKE '%iPhone%' THEN 'iPhone'
   WHEN useragent LIKE '%Android%' THEN 'Android'
   WHEN useragent LIKE '%Mac OS X%' THEN 'OS X'
   WHEN useragent LIKE '%X11%' THEN 'Linux'
   WHEN useragent LIKE '%Linux%' THEN 'Linux'
   WHEN useragent LIKE '%Windows NT 10.%' THEN 'Windows 10'
   WHEN useragent LIKE '%Windows NT 6.3%' THEN 'Windows 8.1'
   WHEN useragent LIKE '%Windows NT 6.2%' THEN 'Windows 8'
   WHEN useragent LIKE '%Windows NT 6.1%' THEN 'Windows 7'
   WHEN useragent LIKE '%Windows NT 6.0%' THEN 'Windows Vista'
   WHEN useragent LIKE '%Windows NT 5.2%' THEN 'Windows Server 2003; Windows XP x64 Edition'
   WHEN useragent LIKE '%Windows NT 5.1%' THEN 'Windows XP'
   WHEN useragent LIKE '%Windows NT 5.0%' THEN 'Windows 2000'
   WHEN useragent LIKE '%Windows NT 4.0%' THEN 'Microsoft Windows NT 4.0'
   WHEN useragent LIKE '%Windows 9' THEN 'Windows 95/98/Millenium'
   WHEN useragent LIKE '%Windows CE' THEN 'Windows CE'
   ELSE 'Other'
 END OS
 FROM addition where site_id=?) AS osses
GROUP BY OS
ORDER BY freq DESC";
$stmt = $mysqli->prepare($sql);
$stmt->bind_param('i', $site_id);
$stmt->execute();
$result = $stmt->get_result();
$oses = $browsers = array();
while ($row = $result->fetch_array(MYSQLI_ASSOC))
    $oses[$row['OS']] = $row['freq'];


$sql = "SELECT browser, COUNT(browser) AS freq FROM
(SELECT
CASE
   WHEN useragent LIKE '%Chrome%' THEN 'Chrome'
   WHEN useragent LIKE '%Opera%' THEN 'Opera'
   WHEN useragent LIKE '%Safari%' THEN 'Safari'
   WHEN useragent LIKE '%Firefox%' THEN 'Firefox'
   WHEN useragent LIKE '%MSIE 7%' THEN 'IE7'
   WHEN useragent LIKE '%MSIE 8%' THEN 'IE8'
   WHEN useragent LIKE '%MSIE 9%' THEN 'IE9'
   WHEN useragent LIKE '%MSIE 10%' THEN 'IE10'
   WHEN useragent LIKE '%rv:11%' THEN 'IE11'
   ELSE 'Other'
  END browser
  FROM addition where site_id=?) AS browsers
GROUP BY browser
ORDER BY freq DESC";

$stmt = $mysqli->prepare($sql);
$stmt->bind_param('i', $site_id);
$stmt->execute();
$result = $stmt->get_result();
while ($row = $result->fetch_array(MYSQLI_ASSOC))
    $browsers[$row['browser']] = $row['freq'];


?>
Кратко:<br>
<table cellpadding="0" cellspacing="0" border="1px" width="200">
    <tr>
        <td colspan="2">Операционные системы:</td>
    </tr><?
    foreach ($oses as $name => $freq)
        echo '<tr><td>' . $name . '</td><td>' . $freq . '</td></tr>';
    ?>
</table><BR>
<table cellpadding="0" cellspacing="0" border="1px" width="200">
    <tr>
        <td colspan="2">Браузеры:</td>
    </tr><?
    foreach ($browsers as $name => $freq)
        echo '<tr><td>' . $name . '</td><td>' . $freq . '</td></tr>';
    ?>
</table>

<br><br><br>
Подробная статистика:
<table>
    <tr>
        <td>Тип браузера:</td>
        <td>Кол-во посещений:</td>
        <td></td>
    </tr>
    <?
    $a = 1;
    $sql = 'select count(*) as quantity,useragent from addition where site_id=? group by useragent order by quantity
    desc,useragent';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $site_id);
    $stmt->execute();
    $result = $stmt->get_result();
    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
        if ($a == 1) $back = 'dark'; else $back = 'white';
        $a = -$a;
        echo '
    <tr class="bg' . $back . '">
        <td>' . $row['useragent'] . '</td>
        <td>' . $row['quantity'] . '</td>
    </tr>
    ';
    }
    #mysql_free_result($result);
    ?>
</table>
