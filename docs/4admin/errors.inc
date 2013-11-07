<table><?
$sql='select * from error_log';
$result=sql($sql);
if(!mysql_num_rows($result))
  echo 'Ошибок нет!';
while($row=mysql_fetch_array($result))
  echo '<tr><td>'.$row['date'].'</td><td>'.$row['script'].'</td><td>'.$row['page'].'</td></tr><tr><td colspan=3>'.$row['text'].'</td></tr>';?></table>