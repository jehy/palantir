<a href='?page=user'>Вернуться в систему администрирования</a><br>
<a href="index.php?page=banner&site_id=<?=$site_id;?>&ac=view">В систему управления банерами</a><br>
<table border="1" cellpadding="0" cellspacing="0">
<tr><td>URL</td><td>Clicks</td></tr>
<?
$sql='select name from sources where id="'.$site_id.'"';
$row=mysql_fetch_array(sql($sql));
echo 'Cтраницы, с которых кликали на баннер cайта "<strong>'.$row['name'].'</strong>" за последние 3 дня:</div><br>';
$sql='select url,count(*) as quan from clicks where site_id="'.$site_id.'" group by url';
$result=sql($sql);
if(mysql_num_rows($result))
{
  while($row=mysql_fetch_array($result))
  {
    echo "<tr><td><a target='_blank' href='".$row['url']."'>".$row['url']."</a></td><td>".$row['quan']."</td></tr>";
  }
}
else echo"<div align='center'><strong>На ваш баннер не кликали!!!</strong></div>";
?></table>
