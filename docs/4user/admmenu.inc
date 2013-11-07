
<table width="100%" border="0" cellpadding='4' cellspacing='4'><tr><td>
<table width=350 border="0" bgcolor="#3D3E46" cellpadding="0" cellspacing="0" align="left">
        <tr>
                <td><strong style="color:black;"><font color=white>Меню пользователя
<?

$sql='select nick from users where id='.$our_user_id.' limit 1';
$result=sql($sql);
$row=mysql_fetch_array($result);
echo $row['nick'];
$javasc ='><a style="COLOR:C8C8BF;"';
$sql='select id,name,url,today_hosts from sources where user_id='.$our_user_id;
$result=sql($sql);
if(!mysql_num_rows($result))$spec='<font size=-1>&nbsp;Подсказка: Добавьте&nbsp;свой&nbsp;первый&nbsp;сайт!</font>';else $spec='';

?>:</strong></td></tr><tr><td>
<table border="0" width=100%><tr>
<td <?=$javasc;?> href="<?=COMMON_URL;?>index.php?page=user&ac=changedata">Изменить&nbsp;профиль</a></td></tr><tr>
<td <?=$javasc;?>
href="<?=COMMON_URL;?>index.php?page=reg&ac=addsite">Добавить&nbsp;сайт</a><?=$spec;?>
</td></tr><tr>
<td <?=$javasc;?> href="<?=COMMON_URL;?>index.php?page=index&ac=logout">Выйти</a></td></tr></table></td></tr></table></td></tr>
<tr><td><hr></td></tr>
<tr><td>
<table border="0" cellpadding="0" cellspacing="0" width="500px" align="left">
<tr><td  bgcolor="#3D3E46" align="left"><strong style="color:white;">Ваши сайты:</strong><br></td></tr>
<?
#$sql='select id,name,url,today_hosts from sources where user_id='.$our_user_id;
#$result=sql($sql);
if(mysql_num_rows($result)){
while($row2=mysql_fetch_array($result))
{
  echo ('
  <tr><td><table  width="100%"  border="0"
   align="center" cellpadding="0" cellspacing="0">
  <tr><td align="center" colspan="3">
  <em><b><a href="'.masktags($row2['url']).'">'.masktags($row2['name']).'</a> (сегодня '.$row2['today_hosts'].'
   посещений)</em></b></td></tr>
 <tr><td bgcolor="#4D3E46" ><b>Сайт:</b></td>
 <td bgcolor="#5D3E46"><b>Счётчик:</b></td>
 <td bgcolor="#6D3E46"><b>Баннеры:</b></td></tr>

  <tr><td bgcolor="#4D3E46"'.$javasc.'><a style="COLOR:C8C8BF;"
  href="'.COMMON_URL.'index.php?page=user&ac=changesitedesc&site_id='.$row2['id'].'">Изменить описание</a></td>
  <td bgcolor="#5D3E46"'.$javasc.' href="'.COMMON_URL.'index.php?page=user&ac=countercode&site_id='.$row2['id'].'">
  <b>Получить код счётчика</b></a></td>
  <td bgcolor="#6D3E46"'.$javasc.' href="'.COMMON_URL.'index.php?page=banner&ac=upload&site_id='.$row2['id'].'">Закачать баннер</a></td></tr>
  <tr><td>&nbsp;</td><td  bgcolor="#5D3E46"'.$javasc.' href="'.COMMON_URL.'index.php?page=stats&site_id='.$row2['id'].'">
  Cтатистика по счётчику</a></td>
  <td bgcolor="#6D3E46"'.$javasc.' href="'.COMMON_URL.'index.php?page=banner&ac=code&site_id='.$row2['id'].'">Получить код баннера</a></td></tr>
<tr><td>&nbsp;</td><td>&nbsp;</td><td  bgcolor="#6D3E46" '.$javasc.' href="'.COMMON_URL.'index.php?page=banner&ac=view&site_id='.$row2['id'].'">
Управление банерами</a></td></tr>
</table></td></tr>
<tr><td width="100%">&nbsp;</td></tr>
  ');
}
}
else echo'<tr><td><font color=white><b>Подсказка:</b>У вас ещё нет сайтов, зарегестрированных в системе.
 Добавить сайт вы можете <a href="'.COMMON_URL.'index.php?page=reg&ac=addsite">здесь</a>,
  или нажав на ссылку пользовательского меню "Добавить ещё сайт".
   Это сделано для того, чтобы вы могли зарегестрировать в системе несколько сайтов
    под одного пользователя. После добавления сайта следует поставить на свой сайт картинку со счёчиком.</font></td></tr>';
?>
</table></td></tr></table>