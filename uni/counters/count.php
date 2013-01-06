<?


/*
if(mt_rand(1,10)==5)
{
header('location: http://dd16.ru/urban_sex/vote/70/');
die();
}*/
Header("Expires: Mon, 26 Jul 2002 05:00:00 GMT");
HEADER("Last-Modified: ".gmdate("D, d M Y H:i:s")."GMT");
HeAdEr("Cache-Control: no-cache, must-revalidate");
hEaDeR("Pragma: no-cache");
header("Content-type: image/png");
function rep($arg){
if(strpos($arg,'/'))return false;
if(strpos($arg,'\\'))return false; #'
$arg=str_replace(array('..',chr(0),chr(27)),'',$arg);
return $arg;
}
$today_hits=rep(@$_GET['today_hits']);
$total_hits=rep(@$_GET['total_hits']);
$today_hosts=rep(@$_GET['today_hosts']);
$total_hosts=rep(@$_GET['total_hosts']);
$cid=rep($_GET['cid']);
$h1=7-strlen($today_hosts);
$h2=7-strlen($today_hits);
$h3=7-strlen($total_hosts);
$h4=7-strlen($total_hits);
$im=imagecreate(88, 31);//truecolor
if($today_hits&&$today_hits&&$total_hosts)
{
        $c=255;
        if($cid=='spec_green.png')$c=33;
        $im=ImageCreateFromPNG('hit/' . $cid);

        $tcolor = imagecolorallocate($im, $c, $c, $c);
        imagestring ($im,1, 50+$h2*5+1, 3,$today_hits,$tcolor);
        imagestring ($im,1, 50+$h1*5+1, 12, $today_hosts,$tcolor);
        imagestring ($im,1, 50+$h3*5+1, 21,$total_hosts,$tcolor);
}
elseif($today_hosts&&$total_hosts)
{


        $im=ImageCreateFromPNG('numeric/' . $cid);
        $tcolor = imagecolorallocate($im, 255, 255, 255);
        imagestring ($im,1, 50+$h1*5+1, 12+1,$today_hosts,$tcolor);
        imagestring ($im,1, 50+$h3*5+1, 21+1,$total_hosts,$tcolor);
}
ImagePng($im);
?>
