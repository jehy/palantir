<?
if(!@$site_id)
	$site_id=0;
$own=0;
$sql='select hide_flags from sources where (id="'.$site_id.'") limit 1';
$result=sql($sql);
if(!mysql_num_rows($result))
	die('Запрошенный сайт не найден!');

$all=mysql_fetch_array($result);	
	
$hide_pages=$all['hide_flags'][0];
$hide_referers=$all['hide_flags'][1];

$sql='select hide_flags from sources where ((user_id="'.$our_user_id.'")and(id="'.$site_id.'")) limit 1';
$result=sql($sql);
if(mysql_num_rows($result))
	$own=1;

if($own)
{
?>
<a href='?page=user'>Вернуться в систему администрирования</a><br>
<?
}
?><a href='?page=stats&site_id=<?=$site_id;?>'>Вернуться в статистику</a><br><?
if($ac=='vistime')include('4user/counter/vistime.inc');
elseif($ac=='vispages')
{
    if(!$own && $hide_pages)
	echo '<h2>Доступ к статистике данного сайта закрыт!</h2>';
    else
	include('4user/counter/vispages.inc');
}
elseif($ac=='visstats')
    include('4user/counter/visstats.inc');
elseif($ac=='referers')
{
    if(!$own && $hide_referers)
	echo '<h2>Доступ к статистике данного сайта закрыт!</h2>';
    else
	include('4user/counter/referers.inc');
}
else
{
?>
Краткая статистика по cайту "<strong><?
$sql='select name,id,today_hits,total_hits,today_hosts,total_hosts from sources where id="'.$site_id.'"';
$result=sql($sql);
$row=mysql_fetch_array($result);
echo $row['name'];?></strong>":<br>

<a href="<?=COMMON_URL;?>index.php?page=stats&ac=referers&site_id=<?=$site_id;?>">Откуда посещали</a><br>
<a href="<?=COMMON_URL;?>index.php?page=stats&ac=vistime&site_id=<?=$site_id;?>">Время всех визитов за день</a><br>
<a href="<?=COMMON_URL;?>index.php?page=stats&ac=vispages&site_id=<?=$site_id;?>">Посещённые cтраницы</a><br>
<a href="<?=COMMON_URL;?>index.php?page=stats&ac=visstats&site_id=<?=$site_id;?>">Браузеры пользователей</a><br>
	<br><br>
Хостов за сегодня:<?echo $row['today_hosts'];?><br>
Хостов всего:<?=$row['total_hosts'];?><br>
Хитов сегодня:<?=$row['today_hits'];?><br>
Хитов всего:<?=$row['total_hits'];?>
<?}
#else echo'<h2>Статистика данного сайта вам недоступна!</h2>';
?>
