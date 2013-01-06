<?
$shows=array();

  ###selecting total current shows for sources
  $sql='SELECT shows.type as stype,shows.site_id as s_site_id,sources.url, sources.id AS site_id, sources.url, sources.name,sources.ban_koef,count(shows.site_id) AS curr_shows FROM shows left join sources on (sources.id=shows.site_id) GROUP BY shows.site_id,shows.type';
  $result=sql($sql);
  while($row=mysql_fetch_array($result))
  {
    if(!$row['site_id'])
      echo 'О-оу. Есть показы банеров без сайта... Идентификатор - '.$row['s_site_id'];
    $shows[$row['stype']][$row['site_id']]=array('current_shows'=>$row['curr_shows'],
    'ban_koef'=>$row['ban_koef'],
    'name'=>$row['name'],
    'url'=>$row['url']);
  }
  mysql_free_result($result);
  #print_R(array_keys($shows));
#print_R($shows[3]);die();

  ###selecting data about  sources and today shows for sources
  $sql='SELECT COUNT(go.site_id) AS `today_banner_shows`,banners.site_id,banners.type FROM  `go` left join banners on (go.banner_id=banners.id) GROUP BY banners.site_id,banners.type';
  $result=sql($sql);
  while($row=mysql_fetch_array($result))
    if($shows[$row['type']][$row['site_id']])
      $shows[$row['type']][$row['site_id']]['today_banner_shows']=$row['today_banner_shows'];
  mysql_free_result($result);



###selecting all banners, their data and today shows
$sql='SELECT banners.shown,banners.type,banners.site_id,banners.id,banners.clicked,
banners.name,ROUND((banners.clicked/banners.shown),3) AS `ctr`, COUNT(go.site_id) AS today_shown FROM banners LEFT JOIN `go` ON((go.banner_id=banners.id)OR(go.banner_id is NULL)) WHERE (banners.status=1) group by banners.id';
$result=sql($sql);
while($row=mysql_fetch_array($result))
{
  If($shows[$row['type']][$row['site_id']])//if that site has shows and we wanna know about it
  $shows[$row['type']][$row['site_id']]['banners'][$row['id']]=array('ctr'=>$row['ctr'],'name'=>$row['name'],'shown'=>$row['shown'],'clicked'=>$row['clicked'],'today_shown'=>$row['today_shown']);
}
mysql_free_result($result);

###selecting all banner clicks
$sql='SELECT  banners.type, banners.site_id,banners.id,COUNT(clicks.banner_id) AS today_clicks FROM clicks,banners WHERE ((clicks.date="'.date('d').'")AND(banners.id=clicks.banner_id)AND(banners.status=1)) GROUP BY banners.id';
$result=sql($sql);
while($row=mysql_fetch_array($result))
  If($shows[$row['type']][$row['site_id']])
    $shows[$row['type']][$row['site_id']]['banners'][$row['id']]['today_clicks']=$row['today_clicks'];
mysql_free_result($result);

ksort($shows);
#print_R($shows[3]);die();
foreach($shows as $network_id=>$arr)
#for($i=1;$i<=$networks;$i++)
{
  echo'
  <table border="0" cellpadding="0" cellspacing="0" width="600">
  <tr><td colspan="3" align="center"><br><br><br><h2>Показы '.$network[$network_id]['name'].':</h2></td></tr>
  <tr><td>Название сайта</td><td>Идентификатор сайта</td><td>Накоп. показы</td></tr>
  ';

foreach($arr as $site_id=>$site)
{
  $back='dark';
  echo'
  <tr class="bg'.$back.'"><td><strong><a href="'.$site['url'].'">'.$site['name'].'</a></strong></td>
  <td>id '.$site_id.'</td>
  <td>'.$site['current_shows'].'(k='.$site['ban_koef'].')</td></tr>';
  #site data shown, gonna to each banner's data.

  if(is_array($site['banners']))
  {#print_R($site['banners']);
  foreach($site['banners'] as $banner_id=>$banner)
  {if(!$banner['today_clicks'])$banner['today_clicks']='0';
  echo'<tr class="bg'.$back.'"><td colspan="4">
  <table cellpadding="0" cellspacing="0" class="bg'.$back.'" border="0" width="100%">
  <tr><td>Название банера</td><td>Показов сегодня</td><td>Всего</td><td>Кликов сегодня</td><td>Всего</td><td>CTR%</td></tr>
  <tr>
  <td>'.$banner['name'].'</td>
  <td>'.$banner['today_shown'].'</td><td>'.$banner['shown'].'</td>
  <td>'.$banner['today_clicks'].'</td><td>'.$banner['clicked'].'</td><td>'.$banner['ctr'].'</td></tr>
  <tr><td colspan="6"><img src="showban.php?id='.$banner_id.'"</td></tr>
  </table>
  </td></tr>';
  }
} else {echo'<tr class="bg'.$back.'"><td colspan="4">Нет банеров, или остались показы у удалённого сайта!</td></tr>';}
echo'<tr class="bgwhite"><td colspan="3"><br><br><br></td></tr>';
}
echo '</table>';
}

?>Ok!
