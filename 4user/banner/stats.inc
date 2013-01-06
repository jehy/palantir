<a href='?page=user'>Вернуться в систему администрирования</a><br>
<div align="center">
Баннеры сайта "<strong><?
$sql='select name from sources where id="'.$site_id.'" limit 1';
$row=mysql_fetch_array(sql($sql));
echo $row['name'];?></strong>":</div>
<?$sql='select count(*) from shows where site_id="'.$site_id.'" and type=1';
$r=mysql_fetch_row(sql($sql));$r=$r[0];
echo '<strong>Накоплено '.$r.' показов в сети 88*31</strong>';
$sql='select count(*) from shows where site_id="'.$site_id.'" and type=2';
$r=mysql_fetch_row(sql($sql));$r=$r[0];
echo '<br><strong>Накоплено '.$r.' показов в сети 100*100</strong>';
$sql='select count(*) from shows where site_id="'.$site_id.'" and type=3';
$r=mysql_fetch_row(sql($sql));$r=$r[0];
echo '<br><strong>Накоплено '.$r.' показов в сети 468*60</strong>';?>
<br><a href="<?=COMMON_URL;?>index.php?page=banner&ac=clicks&site_id=<?=$site_id;?>">Здесь</a> вы можете узнать, на каких страницах сайтов системы кликали по вашему баннеру за последние 3 дня.
<?
$sql='select banners.name,banners.status,banners.id as id,banners.shown,banners.clicked,count(go.site_id) as today_views
from banners left join go on ((go.banner_id=banners.id)or(go.site_id=NULL))
where ((banners.site_id="'.$site_id.'")&&(banners.status<>0))
group by banners.id order by banners.type,banners.id desc';
$result=sql($sql); echo mysql_error();
if(!mysql_num_rows($result)){echo'<h1>Сначала уж загрузи банер, а потом на него смотри!</h1>';}
else
{
  $banners=array();
  echo'<table border="0" cellpadding="0" cellspacing="0" width="600">';
  while($row=mysql_fetch_array($result))$banners[$row['id']]=$row;
  mysql_free_result($result);
  $sql='select clicks.banner_id as id,count(clicks.site_id) as today_clicks from clicks where(clicks.site_id="'.$site_id.'") group by clicks.banner_id';
  $result=sql($sql);
  while($row=mysql_fetch_row($result))$banners[$row[0]]['today_clicks']=$row[1];
  mysql_free_result($result);
  foreach($banners as $key=>$val)
  {
    $back='dark';
    echo'<tr><td colspan="3"><br><br></td></tr>';
    echo'
<tr><td class="bg'.$back.'"><strong><form action="index.php" method="post">
<input type="hidden" name="page" value="banner">
<input type="hidden" name="ac" value="status">
<input type="hidden" name="site_id" value="'.$site_id.'">
<select name="status">';
if($val['status']!=2)echo'<option value="2">Отключить баннер</option>';
if($val['status']!=1)echo'<option value="1">Включить банер</option>';
echo'<option value="0">Удалить баннер</option>
</select>
<input type="hidden" name="ban_id" value='.$key.'><input type="hidden" name="site_id" value="'.$site_id.'">
<input type="submit" value="Применить" class="button"></form>
</strong></td>
  <td class="bg'.$back.'"></td></tr>';
  #site data shown, gonna to each banner's data.
  if(!$val['today_views'])$val['today_views']=0;
  if(!$val['today_clicks'])$val['today_clicks']=0;
  if(!$val['clicked'])$val['clicked']=0;
  if(!$val['shown'])$val['shown']=0;
  
  if(!$val['clicked'] ||!$val['shown'])
    $ctr=0;
  else
    $ctr=round($val['clicked']/$val['shown'],3);
  echo'<tr><td colspan="4" class="bg'.$back.'">
  <table cellpadding="0" cellspacing="0" class="bg'.$back.'" border="1" width="100%">
  <tr><td>Название банера</td><td>Показов сегодня</td><td>Всего</td><td>Кликов сегодня</td><td>Всего</td><td>CTR%</td></tr>
  <tr>
  <td>'.$val['name'].'</td>
  <td>'.$val['today_views'].'</td><td>'.$val['shown'].'</td>
  <td>'.$val['today_clicks'].'</td><td>'.$val['clicked'].'</td><td>'.$ctr.'</td></tr>
  <tr><td colspan="6"><img src="showban.php?id='.$key.'"</td></tr>
  </table>
  </td></tr>';
  }
echo'</table>';
}
$sql='select count(*) from go where from_site="'.$site_id.'" group by ip';
$real=mysql_fetch_row(sql($sql));$real=$real[0];
$sql='select count(*) from go where from_site="'.$site_id.'"';
$all=mysql_fetch_row(sql($sql));$all=$all[0];
if($real==0)$k=0; else $k=ceil($all/$real);
echo'У вас за сегодня насчитано '.$all.' показов, из них '.$real.' с уникальными IP (коэффициент - '.$k.').';
if (($k<=4)and($k!=0)) echo '<br>Коэффициент хороший, так держать!';
elseif($k!=0) echo'<br>Слишком много показов с одних и тех же адресов.';
else echo'<br>Либо вы не поставили код, либо ваш сайт вообще не посещали.';
?>
