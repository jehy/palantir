<?
function changenfo()
{global $loginx,$passwordx,$emailx,$nickx,$our_user_id;
$error='';
if(!$passwordx)
{
  $error.='<br>Вы не ввели пароль!';
}
if (!$nickx)
{
  $error.='<br>Вы не ввели обращение!';
}
if (!$emailx)
{
  $error.='<br>Вы не ввели E-mail!';
}
if (!$loginx)
{
  $error.='<br>Вы не вписали логин!';
}
$sql='select * from users where ((login="'.$loginx.'")and(id!="'.$our_user_id.'")) limit 1';
//echo $sql;
if(mysql_num_rows(sql($sql)))
{
  $error.='<br>Такой логин уже используется!';
}
$ctime=time()+60*60*24*30*12;//for an approximately year
if (!$error)
{
  setcookie('cpassword', $passwordx,$ctime);
  setcookie('clogin', $loginx,$ctime);
  $sql='update users set login="'.$loginx.'", password="'.$passwordx.'", email="'.$emailx.'",nick="'.$nickx.'" where id="'.$our_user_id.'" limit 1';
  sql($sql);
  $login=$loginx;
  return 0;
  //echo'Профиль успешно изменён! ';
}
else return $error;
}

function authorisate()
{
global $session;
if(!$session)
{$t=60*60*8+time();//for 24 hours
  $session=md5(time()).substr(md5(rand(0,1000)),0,5);
  setcookie('session',$session,$t);
}
//$gcont='user='.$user;
}



function get_user_type()
{
global $ac,$our_user,$admin_user,$our_user_id,$admin_user_id,$login,$password,$clogin,$cpassword,$session;
$login=addslashes($login);
$password=addslashes($password);
$clogin=addslashes($clogin);
$cpassword=addslashes($cpassword);
$our_user_id='';
$admin_user_id='';
$admin_user=false;
$our_user=false;

if($ac=='login')
{
  $clogin=addslashes($login);
  $cpassword=addslashes($password);
}
elseif($ac=='logout')
{
  $our_user_id=$admin_user_id=$our_user=$admin_user=$login=$password=$clogin=$cpassword=false;
  setcookie('clogin','');
  setcookie('cpassword','');
}
//checking admin authorisation
$sql='select id from auth where login="'.$clogin.'" and pass="'.$cpassword.'"';
$result=sql($sql);
if(mysql_num_rows($result))
{
  $row=mysql_fetch_array($result);
  $admin_user_id=$row['id'];
  $admin_user=true;
  setcookie('clogin',$clogin);//only admin cookie expires after closing browser
  setcookie('cpassword',$cpassword);
  //echo'Adm!!';
}
//check if we have user authorisation


$time=time();
#$time2=$time-(8*60*60);// Not more then 8 hours ago.
$cond1='(login="'.$clogin.'")and(password="'.$cpassword.'")';
$sql='select id from users where('.$cond1.') limit 1';
$result=sql($sql);
if(mysql_num_rows($result))
{
  $row=mysql_fetch_row($result);
  $ctime=time()+60*60*24*30*12;//for an approximately year
  setcookie('clogin',$clogin,$ctime);
  setcookie('cpassword',$cpassword,$ctime);
  $our_user_id=$row[0];//echo"<b>!!".$our_user_id."</b>";
  $our_user=true;//echo"<h1>POSLE ".$row[last_login]."</h1>";
  $session=addslashes($session);
  $sql='update users set last_login='.$time.' where id="'.$row[0].'" limit 1';
  //echo $sql;
  sql($sql);
 }
}
###Strange staff for admin


if(($ac=='showsrc')&&$admin_user)
  {if(isset($_POST['show']))
  { if(isset($_COOKIE['show'])){
    foreach ($_COOKIE['show'] as $key=>$entry)
    {if(is_array($_COOKIE['show'][$key])){
    foreach ($_COOKIE['show'][$key] as $key2=>$entry2){
    if(!isset($_POST['show'][$key][$key2]))
    { //echo $key;
    setcookie ('show['.$key.']['.$key2.']', '', time() - 3600);
    //echo 'show['.$key.']['.$key2.'] remove';
    unset($show[$key][$key2]);
    }
    }
    }
    else{
    setcookie ('show['.$key.']', '', time() - 3600);
    //echo 'show['.$key.']['.$key2.'] remove';
    unset($show[$key]);}
    }}//print_R($show);
foreach ($_POST['show'] as $key=>$entry)
    {if(is_array($_POST['show'][$key])){
    foreach (@$_POST['show'][@$key] as $key2=>$entry2){
    if(!isset($_COOKIE['show'][$key][$key2]))
    {
    setcookie ('show['.$key.']['.$key2.']', $entry2[0], time()+3600*300);
    $show[$key][$key2]=$entry2[0];
    //echo 'show['.$key.']['.$key2.'] set';
    }
    }
    }
    else {
    setcookie ('show['.$key.']', $entry, time()+3600*300);
    $show[$key]=$entry;}

    }

  }
}



?>
