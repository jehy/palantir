<?

die('Not rewritten!');

$sql = "update sources set parent=$parent, name='$name', login='$login', url='$url', today_hosts='$today_hosts', email='$email', password='$password2', description='$description' where id=$id";
sql($sql);
$sql = "select * from sources where id=$id";
$result = sql($sql);
$row = mysql_fetch_array($result);
echo "<h3 align='center'>Данные изменены</h3><a href='?page=18'>Вернуться к администрированию</a>
<TABLE width='100%'>
    <TD colSpan=2>
      <HR>
    </TD></TR>
  <TR>
    <TD>Название сайта (до 20 символов).</TD>
    <TD>$row[name]</TD></TR>
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>
	
<tr><td>Логин</td><!----><td>$row[login]</td></tr>

  <TR>
    <TD>Адрес сайта:</TD><!---->
    <TD>$row[url]</TD></TR>
 
  <TR>
    <TD colSpan=2>
      <HR>
    </TD></TR>

  <TR>
    <TD>Описание сайта (до 100 символов):</TD>
    <TD>$row[description]</TD></TR>";
?>