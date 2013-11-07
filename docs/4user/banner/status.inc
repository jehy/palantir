<a href='?page=user&site_id=<?=$site_id;?>'>Вернуться в систему администрирования</a><br>
<?

$sql='select * from sources where id="'.$site_id.'" limit 1';
?>
<a href="index.php?page=banner&ac=view&site_id=<?=$site_id;?>">В систему управления банерами</a><br>
<?
$sql='select * from banners,sources,users where ((users.login="'.$clogin.'")&&(users.password="'.$cpassword.'")and(users.id=sources.user_id)
and(banners.site_id=sources.id) and(banners.id="'.$ban_id.'"))';
#echo $sql;
if(mysql_num_rows(sql($sql)))
{
if(!@$status)$status=0;
if(($status>2)||($status<0))echo'Непредусмотреный статус!';
else
{
$sql='update banners set status="'.$status.'" where id="'.$ban_id.'" limit 1';
#echo $sql;
sql($sql);
$r=0;
if(mysql_affected_rows())$r=1;
$date=date("Y-m-d H:m:s");
if(($status==0)&&($r==1))
{
  echo'<h3>Баннер успешно удалён!</h3>';
#$sql='insert into synchro values("","'.$date.'","'.$ban_id.'","'.$status.'")';
#sql($sql);
}
elseif(($status==1)&&($r==1))echo'<h3>Баннер успешно включен!</h3>';
elseif(($status==2)&&($r==1))echo'<h3>Баннер успешно отключен!</h3>';
else echo'<h3>Ошибка в изменении статуса!</h3>';
}
}
else echo'Ошибка доступа!';
?>
