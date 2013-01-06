<a href='index.php??page=user'>Вернуться в систему администрирования</a><br>
<a href="index.php?page=banner">В систему управления банерами</a><br>
<?
$sql="select * from users where ((login='$login')&&(password='$password'))";
$row2=mysql_fetch_array(sql($sql));
$sql="select * from sources where id=$my_id";
$row=mysql_fetch_array(sql($sql));
if($row[user_id]==$row2[id]){?>
Cтраницы, с которых кликали баннеры сайта"<strong><?=$row[name];?></strong>":<br>
<table><tr><td>Страница:</td><td>Кол-во посещений:</td><td></td></tr>
<?$sql="select distinct url from clicks where site_id='$my_id'";
$result=sql($sql);
while($row=mysql_fetch_array($result))
{$sql="select * from clicks where ((site_id='$my_id')and(url='$row[url]'))";
$result1=sql($sql);
$n=mysql_num_rows($result1);
echo "<tr><td><a href='".$row[url]."'>".$row[url]."</a></td><td>".$n."</td></tr>";
}
?></table><?}else echo "<font size='+2'>Ошибка: Статистика этого сайта вам недоступна!</font>";?>
