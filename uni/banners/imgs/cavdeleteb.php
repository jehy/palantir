<?
$pass=$_GET['pass'];
$type=$_GET['type'];
$id=$_GET['id'];
$type=addslashes($type);
if(!is_numeric($id)){exit;}
//echo "img_".$id.".".$type;
if($pass=="qwerty"){
//else{
echo unlink("img_".$id.".".$type);
//}
}
?>