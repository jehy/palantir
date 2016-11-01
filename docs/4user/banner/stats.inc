<a href='?page=user'>Вернуться в систему администрирования</a><br>
<div align="center">
    Баннеры сайта "<strong><?= GetName($site_id); ?></strong>":
</div>
<? $sql = 'select count(*) from shows where site_id=? and type=1';
$r = bind_int_return_row($sql, $site_id);
$r = $r[0];
echo '<strong>Накоплено ' . $r . ' показов в сети 88*31</strong>';
$sql = 'select count(*) from shows where site_id=? and type=2';
$r = bind_int_return_row($sql, $site_id);
$r = $r[0];
echo '<br><strong>Накоплено ' . $r . ' показов в сети 100*100</strong>';
$sql = 'select count(*) from shows where site_id=? and type=3';
$r = bind_int_return_row($sql, $site_id);
$r = $r[0];
echo '<br><strong>Накоплено ' . $r . ' показов в сети 468*60</strong>'; ?>
<br><a
    href="<?= COMMON_URL; ?>index.php?page=banner&ac=clicks&site_id=<?= $site_id; ?>">Здесь</a> вы можете узнать, на каких страницах сайтов системы кликали по вашему баннеру за последние 3 дня.
<?
$sql = 'select banners.name,banners.status,banners.id as id,banners.shown,banners.clicked,count(go.site_id) as today_views
from banners left join go on ((go.banner_id=banners.id)or(go.site_id=NULL))
where ((banners.site_id=?)&&(banners.status<>0))
group by banners.id order by banners.type,banners.id desc';

$stmt = $mysqli->prepare($sql);
$stmt->bind_param('i', $site_id);
$stmt->execute();
$result = $stmt->get_result();

echo $mysqli->error;
if (!$result->num_rows) {
    echo '<h1>Сначала уж загрузи баннер, а потом на него смотри!</h1>';
} else {
    $banners = array();
    echo '<table border="0" cellpadding="0" cellspacing="0" width="600">';
    while ($row = $result->fetch_array(MYSQLI_ASSOC)) $banners[$row['id']] = $row;
    $sql = 'select clicks.banner_id as id,count(clicks.site_id) as today_clicks from clicks where(clicks.site_id=?) group by clicks.banner_id';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $site_id);
    $stmt->execute();
    $result = $stmt->get_result();

    while ($row = $result->fetch_row()) $banners[$row[0]]['today_clicks'] = $row[1];
    foreach ($banners as $key => $val) {
        $back = 'dark';
        echo '<tr><td colspan="3"><br><br></td></tr>';
        echo '
<tr><td class="bg' . $back . '"><strong><form action="index.php" method="post">
<input type="hidden" name="page" value="banner">
<input type="hidden" name="ac" value="status">
<input type="hidden" name="site_id" value="' . $site_id . '">
<select name="status">';
        if ($val['status'] != 2) echo '<option value="2">Отключить баннер</option>';
        if ($val['status'] != 1) echo '<option value="1">Включить баннер</option>';
        echo '<option value="0">Удалить баннер</option>
</select>
<input type="hidden" name="ban_id" value=' . $key . '><input type="hidden" name="site_id" value="' . $site_id . '">
<input type="submit" value="Применить" class="button"></form>
</strong></td>
  <td class="bg' . $back . '"></td></tr>';
        #site data shown, gonna to each banner's data.
        if (!$val['today_views']) $val['today_views'] = 0;
        if (!$val['today_clicks']) $val['today_clicks'] = 0;
        if (!$val['clicked']) $val['clicked'] = 0;
        if (!$val['shown']) $val['shown'] = 0;

        if (!$val['clicked'] || !$val['shown'])
            $ctr = 0;
        else
            $ctr = round($val['clicked'] / $val['shown'], 3);
        echo '<tr><td colspan="4" class="bg' . $back . '">
  <table cellpadding="0" cellspacing="0" class="bg' . $back . '" border="1" width="100%">
  <tr><td>Название баннера</td><td>Показов сегодня</td><td>Всего</td><td>Кликов сегодня</td><td>Всего</td><td>CTR%</td></tr>
  <tr>
  <td>' . $val['name'] . '</td>
  <td>' . $val['today_views'] . '</td><td>' . $val['shown'] . '</td>
  <td>' . $val['today_clicks'] . '</td><td>' . $val['clicked'] . '</td><td>' . $ctr . '</td></tr>
  <tr><td colspan="6"><img src="showban.php?id=' . $key . '"</td></tr>
  </table>
  </td></tr>';
    }
    echo '</table>';
}
$sql = 'select count(*) from go where from_site=? group by ip';
$r = bind_int_return_row($sql, $site_id);
$real = $r[0];
$sql = 'select count(*) from go where from_site=?';
$r = bind_int_return_row($sql, $site_id);
$all = $r[0];
if ($real == 0) $k = 0; else $k = ceil($all / $real);
echo 'У вас за сегодня насчитано ' . $all . ' показов, из них ' . $real . ' с уникальными IP (коэффициент - ' . $k . ').';
if (($k <= 4) and ($k != 0)) echo '<br>Коэффициент хороший, так держать!';
elseif ($k != 0) echo '<br>Слишком много показов с одних и тех же адресов.';
else echo '<br>Либо вы не поставили код, либо ваш сайт вообще не посещали.';
?>
