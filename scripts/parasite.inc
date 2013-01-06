<?
$urls=array('http://www.youtube.com/watch?v=CpZ1bSMuwZE&feature=player_embedded',
'http://www.youtube.com/watch?v=e8Wn6QoX0w8&feature=player_embedded');
$rand_key=array_rand($urls);
$randval=$urls[$rand_key];
$hash=md5($randval);
if(!$_REQUEST[$hash])
{
  setcookie($hash,'1',time()+60*60*24*30*12);//a year
  Header('Location: '.$randval);
  die();
}
?>