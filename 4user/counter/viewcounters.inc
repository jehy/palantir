Выберите вид счётчика, который вы установите у себя на сайте:<br>
<form action='index.php' method='post'>
<input type='hidden' name='page' value='user'>
<input type='hidden' name='step' value='2'>
<input type='hidden' name='ac' value='countercode'>
<input type='hidden' name='site_id' value='<?=$site_id;?>'>
<table><tr>
<?
$mirror=get_mirror();
$x='';
error_reporting(100);
include('uni/counters/dir2.php');
$res=$x;
//echo $res;
if(!$res)
  die('Ошибка: не удаётся подключиться к серверу счётчиков! Попробуйте позже.');
$res=explode('/',$res);
$c=explode('|',$res[0]);
$n=0;
for($i=0;$i<sizeof($c);$i++)
{
  if($n==5)
  {
    echo'</tr><tr>';
    $n=0;
  }
  $n++;
  echo '<td><input name="cid" type="radio" value="'.$c[$i].'"';
  if($i==1)
    echo' checked';
    echo'><img src="'.$mirror['url'].'counters/standard/'.$c[$i].'" height="31" width="88"></td>';
}
?></tr></table>
<br><center><input type='submit' value='Получить код' class="button"></center></form><div align="center">
Так же есть счётчики со статистикой<br>(показывают количество посещений за сегодня и за всегда).</div>
<form action='index.php' method='post'>
<input type='hidden' name='page' value='user'>
<input type='hidden' name='step' value='2'>
<input type='hidden' name='ac' value='countercode'>
<input type="hidden" name="today_hosts" value="1">
<input type="hidden" name="total_hosts" value="1">
<input type='hidden' name='site_id' value='<?=$site_id;?>'><table><tr>
<?
$c=explode('|',$res[1]);
$n=6;
for($i=0;$i<sizeof($c);$i++)
{
$n--;if($n==0){echo'</tr><tr>';$n=5;}
echo '<td><input name="cid" type="radio" value="'.$c[$i].'"';if($i==1)echo' checked';echo'>
<img src="'.$mirror['url'].'counters/numeric/'.$c[$i].'" height="31" width="88"></td>';
}
?></tr></table>
<br><center><input type='submit' value='Получить код' class="button"></center></form>


И новая услуга каталога - расширенная статистика по счётчику - включает клики за сегодня (хиты), визиты за сегодня и визиты за всё время.<br>
<form action='index.php' method='post'>
<input type='hidden' name='page' value='user'>
<input type="hidden" name="today_hosts" value="1">
<input type="hidden" name="total_hosts" value="1">
<input type="hidden" name="today_hits" value="1">
<input type='hidden' name='step' value='2'>
<input type='hidden' name='ac' value='countercode'>
<input type='hidden' name='site_id' value='<?=$site_id;?>'><table><tr>
<?
$c=explode('|',$res[2]);
$n=6;
for($i=0;$i<sizeof($c);$i++)
{
$n--;if($n==0){echo'</tr><tr>';$n=5;}
echo '<td><input name="cid" type="radio" value="'.$c[$i].'"';if($i==1)echo' checked';echo'>
<img src="'.$mirror['url'].'counters/hit/'.$c[$i].'" height="31" width="88"></td>';
}
?></tr></table>
<br><center><input type='submit' value='Получить код' class="button"></center></form>
