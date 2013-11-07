<?
#include('scripts/parasite.inc');
Header('Expires: Mon, 26 Jul 2002 05:00:00 GMT');
HEADER('Last-Modified: '.gmdate('D, d M Y H:i:s').'GMT');
HeAdEr('Cache-Control: no-cache, must-revalidate');
hEaDeR('Pragma: no-cache');
$url=addslashes($_GET['url']);
if(!is_numeric($type=$_GET['type']))exit;
if(!is_numeric($from=$_GET['from']))exit;
if((!is_numeric($rand=$_GET['rand'])and($rand)))exit;
$ip_w=ip2long($_SERVER['REMOTE_ADDR']);
$id=$from;
include('scripts/fuck.inc');
#$chanse=0;
include('scripts/common.inc');
$mirror=get_mirror();
$sql='SELECT sources.ban_koef FROM sources,banners WHERE ((sources.id="'.$from.'")AND(banners.site_id=sources.id)AND(banners.status=1)AND(banners.type='.$type.')) LIMIT 1';//we need to detect id user hasn't uploaded banner - or is it a fictive site ID
$result=sql($sql);
if(mysql_num_rows($result))
{
  $k=mysql_fetch_row($result);
  $k=$k[0];#may be used in different mystery goals
  $sql='SELECT sources.ban_koef,sources.id AS target_id,sources.url AS target_url,banners.id AS ban_id,banners.img_type AS ext FROM shows,sources,banners WHERE ((shows.type='.$type.')and(banners.status=1)AND(sources.id=shows.site_id)AND(banners.site_id=shows.site_id)AND(banners.type='.$type.')AND(sources.id<>'.$from.'))ORDER BY RAND() LIMIT 1';
  $result=sql($sql);
  if(mysql_num_rows($result))
  {
    $row=mysql_fetch_array($result);
    $sql='update shows set site_id="'.$from.'" where site_id='.$row['target_id'].' and type='.$type.' LIMIT 1';
    sql($sql);
  }

  else
  {
    ##Very bad, neccessary banner not found. Showing our banner for now.
    $sql='UPDATE shows SET site_id='.$from.' WHERE site_id='.$Comission_Site_Id.' and type='.$type.' LIMIT 1';
    sql($sql);
    $sql='select sources.id as target_id,banners.id as ban_id,banners.img_type as ext,sources.url as target_url from sources,banners where ((banners.status=1)and(sources.id='.$Comission_Site_Id.')and(banners.site_id=sources.id)and(banners.type='.$type.'))order by rand() limit 1';
    $result=sql($sql);
    $row=mysql_fetch_array($result);
  }


    sql('insert into go values("'.$rand.'","'.$row[ban_id].'","'.$row[target_id].'","'.$from.'","'.$url.'","'.$ip_w.'")');
    #sql('UPDATE `banners` SET `shown`=`shown`+1 WHERE `id`="'.$row['ban_id'].'"');
    mysql_close();
    //Header("Location: http://valar.ru/2b/img_".$row[ban_id].'.'.$row[ext]);
    Header('Location: '.$mirror['url'].'banners/imgs/img_'.$row['ban_id'].'.'.$row['ext']);
}

else  //site id for show couldn`t be selected
{
  if ($type==1)$im=imageCreate(88, 31);
  elseif ($type==2)$im=imageCreate(100, 100);
  elseif ($type==3) $im=imageCreate(468, 60);
  $textcol=imagecolorallocate($im, 0, 0, 0);
  $back=imagecolorallocate($im, 111, 127, 143);
  imagefill($im, 0, 0, $back);
  if ($type==1)
    {imagestring($im, 6, 1, 0, "Error-your", $textcol);
    imagestring($im, 6, 1, 8, "banner not", $textcol);
    imagestring($im, 6, 1, 18, "uploaded!", $textcol);}
  elseif ($type==2)
    {imagestring($im, 14, 3, 00,"You have", $textcol);
    imagestring($im, 14, 1, 14, "Error in", $textcol);
    imagestring($im, 14, 3, 28, "banner code", $textcol);
    imagestring($im, 14, 3, 42, "or YOU", $textcol);
    imagestring($im, 14, 3, 56, "DIDN`T", $textcol);
    imagestring($im, 14, 1, 70, "upload YOUR", $textcol);
    imagestring($im, 14, 3, 84, "BANNER!!", $textcol);}
  elseif ($type==3)
    {imagestring($im, 14, 3, 00, "Banner network error: you have error in code,", $textcol);
    imagestring($im, 14, 3, 20, "your site doesn`t exist in system or ", $textcol);
    imagestring($im, 18, 3, 40, "YOUR OWN BANNER ISN`T UPLOADED!!", $textcol);}
  imagepng($im);
}
/*else  //there is no such site or such banner
{
  if ($type==1) Header("Location: http://valar.ru/2s/14_1.png");
  elseif ($type==2) Header("Location: http://valar.ru/2s/err/100_100.jpg");
  elseif ($type==3) Header("Location: http://valar.ru/2s/err/468_60.gif");
}*/
?>
