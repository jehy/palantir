<h2>Количество визитов на ресурс по часам:</h2>
<table width="200"><tr><td align='center'>Часы&nbsp;&nbsp;</td><td align='center'>&nbsp;&nbsp;Визиты</td></tr><?
$sql='select count(*) as visits,time from addition where site_id="'.$site_id.'" group by time order by time';
$result=sql($sql);
while($row=mysql_fetch_array($result))echo '<tr><td>'.$row['time'].'</td><td>'.$row['visits'].'</td></tr>';
mysql_free_result($result);
?></table>
