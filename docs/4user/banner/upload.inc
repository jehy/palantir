<?
if($step==2)
{
$error=array();#print_R($_FILES['fimg']);
$fimg_name=addslashes($_FILES['fimg']['name']);
$fimg_type=addslashes($_FILES['fimg']['type']);
$fimg_size=addslashes($_FILES['fimg']['size']);
$s=getimagesize($_FILES['fimg']['tmp_name']);
$s=explode('"',$s[3]);
$fimg_width=$s[1];
$fimg_height=$s[3];
$fimg_type=str_replace('image/','',$fimg_type);
$fimg_type=str_replace('pjpeg','jpeg',$fimg_type);
$fimg_type=str_replace('x-png','png',$fimg_type);
$allowed=array('gif','jpeg','png');
if(!is_uploaded_file($_FILES['fimg']['tmp_name']))
	$error[]='<br>Файл не был выбран!<br>';
elseif(!in_array($fimg_type,$allowed))
	$error[]='Недопустимое расширение!<br><strong>'.$fimg_type.'</strong> не поддерживается!<br>';
elseif(($fimg_width>$network[$size]['width']+10)||($fimg_width<$network[$size]['width']-10)
||($fimg_height>$network[$size]['height']+10)||($fimg_height<$network[$size]['height']-10))
	$error[]='Слишком большое отклонение размера банера!<br>'.$fimg_width.'*'.$fimg_height.' вместо '.$network[$size]['width'].'*'.$network[$size]['height'].'!<br>';
if((($fimg_size >(1024*20))&&($size==1))||
(($fimg_size >(1024*30))&&($size==2))||
(($fimg_size >(1024*40))&&($size==3)))
	$error[]='Слишком большой размер файла!<br>';
if(!sizeof($error))
{
  $sql='insert into banners values("", "'.$site_id.'","'.$name.'","'.$fimg_type.'",0,0,"'.$size.'",1)';
  sql($sql);
  if($bid=mysql_insert_id())
  {
    $NewName = 'uni/banners/imgs/img_'.$bid.'.'.$fimg_type;
    if(!copy($_FILES['fimg']['tmp_name'],$NewName))
    {
      error_addlog('Не получилось скопировать банер '.$bid.'.'.$fimg_type);
    }
    else
    {
      # mirroring disabled
      /*$mirror=get_mirror();
      #error_reporting(99);
      $filename=$mirror['url'].'banners/upload.php?id='.$bid.'&ext='.$fimg_type;
      //echo $filename;
      $fd = fopen ($filename, "r");
      $contents = fread ($fd, 1024);
      fclose ($fd);
      if($contents!='1')
      {
        echo'Проблемы с сервером загрузки банеров, банер занесён в систему, но не загружен на дополнительный сервер. В течении суток проблема будет исправлена, и ваш банер появится в панели управления.';
        error_addlog('Недоступен дополнительный сервер - баннер не загружен!');
      }
      else*/


      {
      #$date=date("Y-m-d H:m:s");
      #$sql='insert into synchro values("","'.$date.'","'.$bid.'","1")';
      #sql($sql);
  ?>
Баннер закачан успешно:<br>
<img src="<?=COMMON_URL;?>showban.php?id=<?=$bid;?>"><br>
<a href="index.php?page=banner&ac=upload&site_id=<?=$site_id;?>">Закачать ещё баннер</a><br>
<a href="index.php?page=user">Вернуться к администрированию</a>
<?
}}
  }
  else echo'Непредвиденная ошибка базы данных!! Сообщите администраторам!';
}
else echo implode('<br>',$error).'<br><a href="index.php?page=banner&ac=upload&site_id='.$site_id.'">Назад</a><br>';
}
else
{
?><a href='index.php?page=user'>Вернуться к администрированию</a><br>
Возможна загрузка изображений типа jpeg, gif, png.<br>
Максимальный размер файлов:<br>
Для 88*31 - 20 кб;<br>
Для 100*100 - 30 кб;<br>
Для 468*60 - 40 кб;<br>
<strong><font size="+1">Внимание!</font> Закачивайте баннер того стандарта, банер которого вы поставите у себя на сайте (если вы загрузили несколько типов банеров, то и код надо ставить для именно этих типов). Имеется в виду, что если вы закачали банер размера 88*31 и 468*60, то ставьте код для банера 88*31 и 468*60 и никакой другой, например.</strong><br>
<form action='index.php' method='post' enctype='multipart/form-data'>
<table border='0'>
<tr><td>Укажите стандарт баннерной сети для закачиваемого баннера:</td></tr>
<tr><td><select name="size">
<option value='1' selected>сеть 88*31 (размер счётчика)
<option value='2'>сеть 100*100
<option value='3'>сеть 468*60 (большой размер)
</select></td></tr>
<tr><td>Выберите файл вашего баннера:</td></tr>
<script>
<!--
function loadimg(url)
{
  if (url)
  {
    var k=document.getElementById("img2load");
    k.src=url
  }
}
//-->
</script>
<tr><td><input type="file" name="fimg" id='file' size='20' accept='image/jpeg' align='top' onchange='loadimg(this.value);'></td></tr>
<tr><td><img align='left' name='img2load' id='img2load' src='graphic/s.gif' border='0' alt=''></td></tr>
<tr><td><input type='hidden' name='site_id' value='<?=$site_id;?>'></td></tr>
<tr><td>Название баннера:</td></tr><tr><td><input type='text' name='name' value='баннер№<?
$sql='select (count(*)+1) from banners where site_id="'.$site_id.'"';
//echo $sql;
$result=sql($sql);
$m=mysql_fetch_row($result);
echo $m[0];
?>'></td></tr>
<input type='hidden' name='page' value='banner'>
<input type='hidden' name='ac' value='upload'>
<input type='hidden' name='step' value='2'>
<tr><td><input type='submit' value='Закачать' class="button"></td></tr>
</table>
</form>
<?}?>