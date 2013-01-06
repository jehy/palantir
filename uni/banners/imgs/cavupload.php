<?$size=$_POST['size'];
$name=$_POST['name'];
$login=$_POST['login'];
$pas=$_POST['pas'];
$my_id=$_POST['my_id'];
$thefile=$_FILES['thefile']['tmp_name'];
$thefile_type=$_FILES['thefile']['type'];
$thefile_size=$_FILES['thefile']['size'];

$size=addslashes($size);
$name=addslashes($name);
$login=addslashes($login);
$pas=addslashes($pas);
$my_id=addslashes($my_id);
$thefile_type=str_replace("image/","",$thefile_type);
$thefile_type=str_replace("pjpeg","jpeg",$thefile_type);
$thefile_type=str_replace("x-png","png",$thefile_type);
if(!$thefile){$error=$error."<br>Файл не был выбран!<br>";}
elseif(($thefile_type != "gif" ) &&
 ($thefile_type != "png" ) &&
 ($thefile_type != "jpeg" ))
 {
    $error="Недопустимое расширение!<br>";
  }
if ((($thefile_size >(1024*10))&&($size==1))||
   (($thefile_size >(1024*20))&&($size==2))||
    (($thefile_size >(1024*25))&&($size==3)))
{$error=$error."Слишком большой размер файла!<br>";}
if(!$error){
$filename="http://fantasy.d2.ru/getlast.php?name=$name&site_id=$my_id&size=$size&login=$login&pas=$pas&type=$thefile_type";
$fd = fopen ($filename, "r");
$contents = fread ($fd, 1024);
fclose ($fd);
}
if((!is_numeric($contents))||($error)){
$error=$error."<br>".$contents;
echo "<html><head>
<meta http-equiv='Content-Type' content='text/html; charset=windows-1251'>
<STYLE TYPE='text/css'>
	body{
	background-color : 6F7F8F;
</style></head><body><b><font size='+1'>Ошибки:</font></b><br>".$error."<br><a href='http://fantasy.d2.ru/?page=31&my_id=$my_id'>Попробовать ещё раз</a></body></html>";}
else
{
$type=str_replace("image/", "", $thefile_type);
$aCurBasePath = dirname( $PATH_TRANSLATED );
$aNewName = $CurBasePath ."img_".$contents.".".$type;
copy( $thefile, $aNewName);
header("Location: http://fantasy.d2.ru?page=32&last=$contents&type=$type");}?>

	   