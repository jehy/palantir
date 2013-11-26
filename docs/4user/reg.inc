<?
###################################
###################################
function showlev2($n)
{
  $sql='select * from types where parent="'.$n.'"';
  $result=sql($sql);
  echo '<ul>';
  while ($row = mysql_fetch_array($result))
  {
    $sql='select * from types where parent="'.$row['id'].'"';
    $result2=sql($sql);
    if(!mysql_num_rows($result2))
      echo '<a href="index.php?page=reg&ac=addsite&step=2&sid='.$row['id'].'">'.$row['name'].'</a><br>';
    else
      echo $row['name'].'<br>';
    showlev2($row['id']);
  }
echo '</ul>';
}

function drevo()
{?>
<h1>Добавление сайта, шаг №1</h1>
Выберите категорию для регистрации cвоего сайта:
<br><?
showlev2(13);
}

###################################
###################################
function reguser()
{
global $reg,$REMOTE_ADDR;
?>
<h1>Регистрация</h1>
<FORM METHOD="POST" ACTION="index.php">
<input type='hidden' name='page' value='reg'>
<input type='hidden' name='step' value='2'>
<table width="100%" align="center">

<tr><td colspan="2">Вначале производится регистрация пользователя (аккаунта), потом вы сможете добавить в свой профиль ваши сайты, получить к каждому своему сайту код счётчика\банера и т.д.<hr></td></tr>
<tr><td>Логин</td><!----><td><input class= "tab_all" TYPE="text" NAME="reg[login]" value='<?=$reg['login']?>' maxlength="40"></td></tr>

<tr><td colspan="2"><hr></td></tr>
<tr><td>Пароль</td><td><!----><input class= "tab_all" TYPE="password" NAME="reg[password1]" maxlength="20" ></td></tr>

<tr><td colspan="2"><hr></td></tr>
<tr><td>Повторите пароль</td><td><!----><input class= "tab_all" TYPE="password" NAME="reg[password2]" maxlength="20" ></td></tr>

<tr><td colspan="2"><hr></td></tr>
<tr><td>E-mail</td><!----><td><input class= "tab_all" TYPE="text" NAME="reg[email]" value='<?=$reg['email']?>' maxlength="40"></td></tr>

<tr><td colspan="2"><hr></td></tr>
<tr><td>Ник или Ф.И.О.</td><!----><td><input class= "tab_all" TYPE="text" NAME="reg[nick]" value='<?=$reg['nick']?>' maxlength="40"></td></tr>

<tr><td colspan="2"><hr></td></tr>
<tr><td>Введите число с картинки&nbsp;<img src="random.php"></td><td><input class= "tab_all" TYPE="text" NAME="reg[if_hacker]"></td></tr>

<tr><td colspan="2"><hr></td></tr>
 <TR>
    <TD colspan="2" align="center"><input type="submit" value="Зарегистрировать" class="button"></TD></TR>
</table>
</form>
<?
}
###################################
###################################
function reguser2()
{global $reg,$REMOTE_ADDR;
$error=array();
if(!$reg['if_hacker'])
  $error[]='<br>Поле с числом незаполнено!';
else
{
  $sql='select 1 from `check` where ((`ip`="'.ip2long($_SERVER['REMOTE_ADDR']).'")and(time>'.(time()-60*15).') and (rand="'.$reg['if_hacker'].'")) limit 1';
  $result=sql($sql);
  if(!mysql_num_rows($result))$error[]='введённое число не совпадает со сгенерированным!';
}
if(!$reg['password1'])
  $error[]='<br>Вы не ввели пароль!';

if(!$reg['password2'])
  $error[]='<br>Вы не ввели повтор пароля!';

if($reg['password1']!=$reg['password2'])
  $error[]='<br>Пароли не совпадают!';

if (!$reg['nick'])
  $error[]='<br>Вы не ввели обращение!';

if (!$reg['email'])
  $error[]='<br>Вы не ввели E-mail!';

if (!$reg['login'])
  $error[]='<br>Вы не вписали логин!';


$sql='select id from users where login="'.$reg['login'].'" limit 1';
if(mysql_num_rows(sql($sql)))
  {$error[]='<br>Такой логин уже используется!';}
#$date=date("Y:m:d");
if (!sizeof($error))
{
  sql('DELETE from `check` where `ip`="'.ip2long($_SERVER['REMOTE_ADDR']).'"');
  $sql = 'INSERT INTO `users` VALUES
  ("", "'.$reg['login'].'", "'.$reg['password1'].'", "'.$reg['email'].'", "'.$reg['nick'].'",0,0)';
  sql($sql);
  echo'Регистрация аккаунта прошла упешно,
   теперь надо <a href="?page=login">войти</a> под указанными логином и паролем,
    добавить в профиль сайт и можно пользоваться сервисами!';
}
else echo'<h3>В течении регистрации были ошибки:</h3>'.implode('<br>',$error).'<br>
<a href="index.php?page=reg&amp;reg[nick]='.$reg['nick'].'&amp;reg[email]='.$reg['email'].'&amp;reg[login]='.$reg['login'].'">Вернуться и попробовать ещё раз</a>';
}

###################################
###################################
function regsite3()
{
global $reg,$REMOTE_ADDR,$sid,$our_user_id;
/*
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
$error=array();
if(!$reg['if_hacker']) $error[]='Поле с числом незаполнено!';

if(!$reg['description']) $error[]='Вы не ввели описание!';


if (!$reg['name']) $error[]='Вы не ввели имя сайта!';

if ((!$reg['url']) or($reg['url']=='http://')) $error[]='Вы не вписали адрес!';


$sql='select 1 from `check` where ((`ip`="'.ip2long($_SERVER['REMOTE_ADDR']).'")and(time>'.(time()-60*15).') and (rand="'.$reg['if_hacker'].'")) limit 1';
#echo $sql;
if(!mysql_num_rows(sql($sql)))
  $error[]='Введённое число не совпадает со сгенерированным!';


/*
$sql='select * from sources where url="'.$url.'" limit 1';
if(mysql_num_rows(sql($sql)))
  {$error[]='Cайт с таким адресом URL уже есть в каталоге!';}
*/

$sql='select * from types where parent="'.$sid.'" limit 1';
if(mysql_num_rows(sql($sql)))
  $error[]='В этом каталоге нельзя регистрироваться! Спуститесь ниже по ветке!';

$sql='select * from types where id="'.$sid.'" limit 1';
if(!mysql_num_rows(sql($sql)))
  $error[]='Такого каталога не существует!';
$date=date("Y:m:d");
if (!$error)
{
  sql('DELETE from `check` where `ip`="'.ip2long($_SERVER['REMOTE_ADDR']).'"');
  $sql = 'INSERT INTO sources VALUES
  ("", "'.$reg['name'].'", "'.$reg['description'].'", "'.$sid.'", "'.$reg['url'].'", "'.$date.'", 0, 0,0,0,"'.$our_user_id.'",0,0,"00")';
  #echo $sql;
  $result=sql($sql);
  if(mysql_affected_rows())echo'<h1>Добавление сайта, шаг №3</h1><div width=500>Сайт зарегестрирован успешно!<br>Теперь вы можете воспользоваться нашими сервисами на <a href="index.php?page=user">странице администрирования</a></div>';
  else echo'Страшная ошибка при регистрации!';
}
else echo'<h1>Добавление сайта, шаг №3</h1><div width=500><strong>Ошибки при регистрации:</strong>'.implode('<br>',$error).'<a href="index.php?page=reg&amp;step=2&amp;ac=addsite&amp;reg[name]='.$reg['name'].'&amp;reg[url]='.$reg['url'].'&amp;reg[description]='.$reg['description'].'&amp;sid='.$sid.'"><br>Вернуться и попробовать ещё раз</div></a>';
}

###################################
###################################
function regsite2()
{global $reg,$sid;
?>
<h2>Добавление сайта, шаг №2</h2>
Вы выбрали раздел "
<?$choisen=mysql_fetch_array(sql('select * from types where id="'.$sid.'"'));
echo $choisen['name'];
?>"&nbsp;
<a href='?page=reg&ac=addsite'>Выбрать другой</a>
<FORM METHOD="POST" ACTION="index.php">
<input type='hidden' name='page' value='reg'>
<input type='hidden' name='ac' value='addsite'>
<input type='hidden' name='sid' value='<?=$sid?>'>
<input type='hidden' name='step' value='3'>
<table width="500">
<tr><td>Название сайта (до 20 символов)</td><td><input maxlength="20" class= "tab_all" TYPE="text" NAME="reg[name]" value='<?=$reg['name']?>'></td></tr>
<tr><td colspan="2">*Примечание: использование в названии сайта кавычек и некоторых других спецсимволов укорачивает возможную длину названия. Пожалуйста, если вы их используете, проверьте после регистрации, насколько название корректно отображается, и, если необходимо - измеите его.</td></td></tr>
<tr><td colspan="2"><hr></td></tr>
<?if(isset($reg['url'])){$urlval=$reg['url'];}else{$urlval='http://';}?>
<tr><td>URL главной страницы</td><td><input maxlength="50"  class= "tab_all" TYPE="text"  NAME="reg[url]" value='<?=@$urlval?>'></td></tr>
<tr><td colspan="2"><hr></td></tr>
<tr><td>Описание регистрируемого сайта (до 60 символов)</td><td><input class= "tab_all" TYPE="text" NAME="reg[description]" value='<?=$reg['description']?>' maxlength="60" ></td></tr>
<tr><td colspan="2"><hr></td></tr>
<tr><td>Введите число с картинки&nbsp;<img src="random.php"></td><td><input class= "tab_all" TYPE="text" NAME="reg[if_hacker]"></td></tr>
<tr><td colspan="2"><hr></td></tr>
<TR><TD colspan=2><input type="submit" value="Зарегистрировать" class="button"></TD></TR>
</table>
</form>
<?
}

###################################
###################################
if(!$our_user)
{
  if($step==2)reguser2();
  else reguser();
}
elseif($ac=='addsite')
{
  if($step==2)regsite2();
  elseif($step==3)regsite3();
  else drevo();
}
?>
