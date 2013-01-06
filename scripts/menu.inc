<b style="color:black; margin-right: 63px;">Навигация:</b><br>
<a class="bb" href="<?=COMMON_URL;?>">Главная</a><br>
<a class="bb" href="<?=COMMON_URL;?>top/Fantasy.html"><b>Каталог</b></a><br>

<?
if($admin_user)
  echo '<a class="bb" href="' . COMMON_URL.'admin.html">Админ.&nbspЦентр</a><br>';
if($our_user)
  echo'<a  style="color:#2222ff" class="bb" href="'.COMMON_URL.'user.html"><i>Мои сайты</i> </a><br>';
  elseif((!$our_user)&&(!$admin_user))
  echo'<a  class="bb" href="'.COMMON_URL.'reg.html">Регистрация</a><br><a  class="bb" href="'.COMMON_URL.'login.html">Вход</a><br>';

?><!---->
<a class="bb"  href="<?=COMMON_URL;?>about.html">О проекте</a><br>
<a class="bb"  title="Часто задаваемые вопросы" href="<?=COMMON_URL;?>faq.html">FAQ</a><br>
<a  class="bb" href="<?=COMMON_URL;?>mail.html">Связь с авторами</a><br>
<?
if(!isset($katid))$katid=13;
$sql='select parent from types where id='.$katid;
$result=sql($sql);
if(!mysql_num_rows($result))$h='Нихрена такого каталога нет!';
else
{
  $row=mysql_fetch_row($result);
  $sql='select name_eng from `types` where id="'.$row[0].'"';
  $result=sql($sql);
  $row=mysql_fetch_row($result);
  echo ('<br><b style="color:black">Подкаталоги:</b><br>');
  if($katid!=13)
  {
    echo'<a  class="bb" href="'.COMMON_URL.'top/'.$row[0].'.html">.. Выше</a><br>';
  }
  $sql = 'select name,id,name_eng from types where parent='.$katid;
  $result = sql($sql);
  if(mysql_num_rows($result))
  {
    while ($row = mysql_fetch_array($result))
    {
      echo('<a  class="bb" href="'.COMMON_URL.'top/'.$row['name_eng'].'.html">'.$row['name'].'</a><br>');
    }
  }
}
?>
