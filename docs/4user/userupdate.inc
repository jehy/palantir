<?if($addrec)
{
  $passwordx=str_replace('"', "&#34;", $passwordx);
  $loginx=str_replace('"', "&#34;", $loginx);
  $passwordx=str_replace("'", "&#039;", $passwordx);
  $loginx=str_replace("'", "&#039;", $loginx);
  $nickx=str_replace('"', "&#34;", $nickx);
  $emailx=str_replace('"', "&#034;", $emailx);
  $nickx=str_replace("'", "&#039;", $nickx);
  $emailx=str_replace("'", "&#039;", $emailx);
  $nickx=str_replace("<", "&lt;", $nickx);
  $emailx=str_replace("<", "&lt;", $emailx);
  $nickx=str_replace(">", "&gt;", $nickx);
  $emailx=str_replace(">", "&gt;", $emailx);
    if(!$passwordx)
  {
    $error="$error<br>Вы не ввели пароль!";
  }
  if (!$nickx)
  {
    $error="$error<br>Вы не ввели обращение!";
  }  
  
  if (!$emailx)
  {
    $error="$error<br>Вы не ввели E-mail!";
  }
  
  if (!$loginx)
  {
    $error="$error<br>Вы не вписали логин!";
  }
  $sql="select * from users where ((login='$loginx')and(password!='$password'))";
  if(mysql_num_rows(sql($sql)))
  {
    $error="$error<br>Такой логин уже используется!";
  }
  $date=date("Y:m:d");
  if (!$error)
  {
    setcookie("password", "$passwordx");
    setcookie("login", "$loginx");
    $sql="update users set login='$loginx', password='$passwordx', email='$emailx',nick='$nickx' where login='$login'";
    sql($sql);
	$login=$loginx;
  }
  }?>