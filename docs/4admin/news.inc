<?
if(!@$step)$step=0;
if ($step==0)
{?>
Вставьте сюда новые новости
<form action='index.php' method='post'>
URL:<input type='Text' name='news[url]'>
URL name<input type='Text' name='news[url_name]'>
<strong>текст</strong><br>
<textarea cols='60' rows='5' name='news[text]'></textarea><br>
<input type='Submit' class='menu' value='вставить'>
<input type='hidden' name='page' value='admin'>
<input type='hidden' name='step' value='1'>
<input type='hidden' name='ac' value='news'>
</form>
<?
}
if ($step==4)
{
  $sql = 'DELETE FROM p_news WHERE id="'.$nid.'"';
  sql($sql);
}
if ($step==1)
{
$text=$news['text'];
$url_name=$news['url_name'];
$date = date("Y-m-d");
$sql = "INSERT INTO p_news VALUES
(NULL, '$date', '$news[url]', '$url_name', '$text')";
$result = sql($sql);
}

if ($step==3)
{
$text=$news['text'];
$url_name=$news['url_name'];
$sql="UPDATE p_news SET text='$text', date='$news[date]', url='$news[url]', url_name='$url_name' where id=$nid";
//echo $sql;
sql($sql);
}

elseif ($step==2)
{
$result = sql("SELECT * FROM p_news WHERE id='$nid'");
while ($row = mysql_fetch_array($result))
{
echo("
<form action='index.php' method='post'>
<strong>ID$row[id]</strong>
<input type='hidden' value='$row[id]' name='nid' size='26'>
<strong>текст</strong><br>
<textarea cols='60' rows='5' name='news[text]'>$row[text]</textarea><br>
<input type='text' name='news[date]' value='$row[date]'><br>
<input type='text' name='news[url]' value='$row[url]'><br>
<input type='text' name='news[url_name]' value='$row[url_name]'><br>
<input type='Submit' class='menu' value='Изменить'>
<input type='hidden' name='page' value='admin'>
<input type='hidden' name='ac' value='news'>
<input type='hidden' name='step' value='3'>
</form><hr>");
}
}
?>



<input type="button" class="menu" value="обновить" onClick="window.location.href = '<?=COMMON_URL;?>?page=admin&ac=news'"><br>
<input type="button" class="menu" value="<?=COMMON_URL;?>" onClick="window.location.href = '<?=COMMON_URL;?>'"><br>
<hr>

<?
$sql = 'select * from p_news order by `id` desc';
$result = sql($sql);
while ($row = mysql_fetch_array($result))
{echo("
<input type='button' class='menu' value='стереть' onClick=\"window.location.href = 'index.php?page=admin&ac=news&step=4&nid=$row[id]'\">
<input type='button' class='menu' value='редактировать' onClick=\"window.location.href = 'index.php?page=admin&ac=news&step=2&nid=$row[id]'\"><br><br>
$row[text]<br>
<div align='right'><em>$row[date], $row[url]</em></div><br><hr>"
);
}
?>
