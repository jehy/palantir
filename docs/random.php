<?
mt_srand(time()+(double)microtime()*1000000);
$random=rand(1, 10000);
///setcookie("ifhacookie", $random, time()+10000,"/");
$ip=ip2long($_SERVER['REMOTE_ADDR']);
include('scripts/common.inc');
$sql='update `check` set `rand`='.$random.',`time`='.time().' where (ip='.$ip.')';
sql($sql);
if(mysql_affected_rows()==0)
{
  $sql='insert into `check` values('.$ip.','.$random.','.time().')';
  sql($sql);
}
mysql_close();
//header();
$im=imageCreate(55, 15);
$textcol=imagecolorallocate($im, 0, 0, 0);
$back=imagecolorallocate($im, 111, 127, 143);
imagefill($im, 0, 0, $back);
imagestring($im, 14, 0, 00, $random, $textcol);
Header("Expires: Mon, 26 Jul 2002 05:00:00 GMT");
HEADER("Last-Modified: ".gmdate("D, d M Y H:i:s")."GMT");
HeAdEr("Cache-Control: no-cache, must-revalidate");
hEaDeR("Pragma: no-cache");
header("Content-type: image/png");
imagePng($im);
imagedestroy($im);
?>
