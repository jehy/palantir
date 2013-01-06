<?
if($admin_user)
{
if($ac=='baners')include('4admin/allbans.inc');
elseif($ac=='news')include('4admin/news.inc');
elseif($ac=='showsrc')include('4admin/showsrc.inc');
elseif($ac=='mirrors')include('4admin/mirrors.inc');
elseif($ac=='errors')include('4admin/errors.inc');
elseif(($ac=='types')||($ac=='meta'))include('4admin/types.inc');
else{?>
Сие есть администрационный центр.
<?
if (@$ac=='optimize')
{
  $sql="Optimize tables()";
  $result=sql($sql);
  if($result)
  {
  echo"<div align='center'><strong>Таблицы оптимизированы.</strong></div>";
  }
}
?>
<table style="background-color:gray;color:black;" width="100%" border="0" cellspacing="1px" cellpadding="1px">
<tr><td>
<table border="0" cellspacing="3px" cellpadding="1px"><tr>
<td width='150' >Администрирование:
</td></tr><tr>
<td width='150'>
<a href="<?=COMMON_URL;?>index.php?page=admin&ac=news">Новости</a>
</td></tr>
<tr><td width='150'>
<a href="<?=COMMON_URL;?>index.php?page=admin&ac=types">Каталоги</a>
</td></tr>
<tr><td width='150'>
<a href="<?=COMMON_URL;?>index.php?page=admin&ac=showsrc">Ресурсов</a>
</td></tr>
<tr><td width='150'>
<a href="<?=COMMON_URL;?>index.php?page=admin&ac=baners">Банеров</a>
</td></tr>
<tr><td width='150'>
<a href="<?=COMMON_URL;?>index.php?page=admin&ac=errors">Ошибки</a>
</td></tr>
<tr><td width='150'>
<a href="<?=COMMON_URL;?>index.php?page=admin&ac=mirrors">Зеркал</a>
</td></tr>
</table></td>
<td>
<table height="100%">
<tr>
<td width='150' valign="top" align="left" >Управление&nbsp;таблицами:
</td></tr><tr><td><font size="-1"><br></font></td></tr>
<tr><td width='150'>
<a href="<?=COMMON_URL;?>index.php?page=42&action=optimize">Оптимизировать&nbsp;таблицы</a>
</td></tr></table>
</td></tr><tr><td colspan="2">Функции для глупых пользователей:<br>
<a href="<?=COMMON_URL;?>index.php?page=46">Загрузка пользовательского банера</a>
</td></tr></table>
</table>
<?}}
else echo'<h1>Неаффторизован!!</h2>';?>

