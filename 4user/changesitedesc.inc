<?
if($step==2)
{
  /*
  $name=str_replace('"', "&#34;", $name);
  $description=str_replace('"', "&#034;", $description);
  $url=str_replace('"', "&#034;", $url);

  $name=str_replace('"', "&#34;", $name);
  $description=str_replace('"', "&#034;", $description);
  $url=str_replace('"', "&#034;", $url);

  $name=str_replace("'", "&#039;", $name);
  $description=str_replace("'", "&#039;", $description);
  $url=str_replace("'", "&#039;", $url);

  $name=str_replace("<", "&lt;", $name);
  $description=str_replace("<", "&lt;", $description);
  $url=str_replace("<", "&lt;", $url);

  $name=str_replace(">", "&gt;", $name);
  $description=str_replace(">", "&gt;", $description);
  $url=str_replace(">", "&gt;", $url);
  */
$sql='select * from sources where ((user_id="'.$our_user_id.'")and(id="'.$site_id.'")) limit 1';
$result=sql($sql);
if(mysql_num_rows($result))
{
  $sql = 'update sources set
  name="'.$name.'", description="'.$description.'", url="'.$url.'" where id="'.$site_id.'" limit 1';
  sql($sql);
  $sql='select * from sources where id="'.$site_id.'" limit 1';
  $result = sql($sql);
  @$row=mysql_fetch_array($result);
  ?>
  <h3 align='center'>Данные изменены</h3><a href='?page=user'>Вернуться к администрированию</a>
<TABLE width='100%'><tr>
    <TD colSpan=2>
      <HR>
    </TD></TR>
  <TR>
    <TD>Название сайта</TD>
    <TD><?=$row['name'];?></TD></TR>
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>
  <TR>
    <TD>Адрес сайта:</TD><!---->
    <TD><?=$row['url'];?></TD></TR>

  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>

  <TR>
    <TD>Описание сайта:</TD>
    <TD><?=$row['description'];?></TD></TR></table>
<?
}
else echo'Неправильный идентификатор сайта.';
}
else
{
$sql='select * from sources where ((user_id="'.$our_user_id.'")and(id="'.$site_id.'")) limit 1';
$result=sql($sql);
if(mysql_num_rows($result))
{
$row=mysql_fetch_array($result);?>
<a href='?page=user'>Вернуться к администрированию</a><br>
<FORM action='index.php' method='post'>
<input type='hidden' name='page' value='user'>
<input type='hidden' name='ac' value='changesitedesc'>
<input type='hidden' name='step' value='2'>
<input type='hidden' name='site_id' value='<?=$row['id'];?>'>
<TABLE width='100%'>
<TR><TD colSpan=2><HR></TD></TR>
<TR><TD>Название сайта:</TD><!---->
<TD><INPUT class='input_text' name='name' value= '<?=masktags($row['name']);?>'></TD></TR>
<TR><TD colSpan=2><HR></TD></TR>
<TR><TD>Адрес сайта:</TD><!---->
<TD><INPUT class= 'input_text'value= '<?=masktags($row['url']);?>' name='url'></TD></TR>
<TR><TD colSpan=2><HR></TD></TR>
<TR><TD>Описание сайта:</TD>
<TD><!----><INPUT class= 'input_text' name='description' value='<?=masktags($row['description']);?>'></TD></TR>
<TR><TD colSpan=2><HR></TD></TR>
<TR>
<TD colspan=2><input type='submit' value='Изменить' class="button"></TD></TR></TABLE></FORM>
<?
}
else echo'Вы не имеете прав на администрирование этого сайта!';
}
?>
