<?
$sql='select name from sources where id="'.$site_id.'"';
$row=mysql_fetch_array(sql($sql));?>
Постраничное посещение сайта "<strong><?=$row['name'];?></strong>":<br>
(Имеются в виду страницы вашего сайта, на которые попадали уникальные посетители)<br>
<table><tr class="bgdark"><td style="padding-left:20px;" class="bgdark">Посещённая страничка:</td><td>Кол-во посещений:</td></tr>
<?
$sql='select count(*) as quantity, referer from addition where site_id="'.$site_id.'" group by referer order by quantity desc,referer';
$result=sql($sql);
while($row=mysql_fetch_array($result))
{
  if(!$row['referer'])
  ;#{$show='<strong>Чёрт его знает</strong>';$link='';}
  else
  {
  /*
	#$link=iconv('utf8','cp1251',urldecode($row['referer']));
	$link=urldecode($row['referer']);
	if(strlen($link)>250)
		$show=substr($link,0,250).'...';
	else
		$show=$link;*/
  echo '<tr class="bgdark"><td style="padding-left:20px;" class="bgdark">'.shortlink($row['referer']).'</td><td>'.$row['quantity'].'</td></tr>';
	}
	#$link=urlencode($link);
			
}
mysql_free_result($result);
?>
</table>
