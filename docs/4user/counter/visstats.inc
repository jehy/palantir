Сведения о браузерах посетителей сайта "<strong><?
$sql='select * from sources where id="'.$site_id.'"';
$result=sql($sql);
$row=mysql_fetch_array($result);
echo $row['name'];?>
</strong>":<br>
<?
function getmicrotime(){
    list($usec, $sec) = explode(" ",microtime());
    return ((float)$usec + (float)$sec);
    }
$t=getmicrotime();
$words=array('Windows NT','Windows 98','FreeBSD','MSIE 6','MSIE 5','MSIE 4','Opera','Firefox','MSIE 7','Safari','Chrome','Macintosh','Linux');
for($i=0;$i<sizeof($words);$i++)
{
  $sql='select id from addition where ((site_id="'.$site_id.'") and (useragent like("%'.$words[$i].'%")))';
  $result=sql($sql);
  $s[$i]=mysql_num_rows($result);
  mysql_free_result($result);
}
//echo (getmicrotime()-$t).'<br>';
echo'
Кратко:<br><table cellpadding="0" cellspacing="0" border="1px" width="200">
<tr><td colspan="2">Операционные системы:</td></tr>
<tr><td>Windows NT </td><td>'.$s[0].'</td></tr>
<tr><td>Windows 98 </td><td> '.$s[1].'</td></tr>
<tr><td>FreeBSD </td><td>'.$s[2].'</td></tr>
<tr><td>Macintosh  </td><td>'.$s[11].'</td></tr>
<tr><td>Linux  </td><td>'.$s[12].'</td></tr>
</table><BR><table cellpadding="0" cellspacing="0" border="1px" width="200">
<tr><td colspan="2">Браузеры:</td></tr>
<tr><td>Internet Explorer 7  </td><td>'.$s[8].'</td></tr>
<tr><td>Internet Explorer 6 </td><td>'.$s[3].'</td></tr>
<tr><td>Internet Explorer 5  </td><td>'.$s[4].'</td></tr>
<tr><td>Internet Explorer 4  </td><td>'.$s[5].'</td></tr>
<tr><td>Opera  </td><td>'.$s[6].'</td></tr>
<tr><td>Firefox  </td><td>'.$s[7].'</td></tr>
<tr><td>Safari  </td><td>'.$s[9].'</td></tr>
<tr><td>Chrome  </td><td>'.$s[10].'</td></tr>
</table>
* Некоторые браузеры могут считаться дважды, если у них проставлена настройка "Распознаваться как IE".
<br><br><br>
Подробная статистика:
<table><tr><td>Тип браузера:</td><td>Кол-во посещений:</td><td></td></tr>';
$sql='select count(*) as quantity,useragent from addition where site_id="'.$site_id.'" group by useragent order by quantity desc,useragent';
$result=sql($sql);
$a=1;
while($row=mysql_fetch_array($result))
{
  if ($a==1)$back='dark'; else $back='white';
  $a=-$a;
  echo '<tr class="bg'.$back.'"><td>'.$row['useragent'].'</td><td>'.$row['quantity'].'</td></tr>';
}
mysql_free_result($result);
?></table>
