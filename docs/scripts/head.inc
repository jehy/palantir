<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<LINK REL="SHORTCUT ICON" HREF="<?=COMMON_URL;?>favicon.ico">
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<meta name='yandex-verification' content='53816566f67c50d7'>
<meta name='yandex-verification' content='7524fb51cb1def33'>
<meta name="verify-v1" content="zxdRsPVLYr6H4N3hHRloXU23BNsX5ffu9nDJGOgWAWs=">
<meta name="verify-v1" content="xzEA/8SNtvV3ZnVQKNYVTvuYX2u1/2zhJ5sUjfUcKlw=">
<?
if($page!='admin')
{
$title1=$keywords1=$description1='';
if($page=='top')
{

  if((!isset($frompage))||($frompage<1))
    $frompage=1;
  $from2=($frompage-1)*TOP;
  $sql='select * from types_meta where `type_id`="'.$katid.'" order by `id` LIMIT '.($frompage-1).',1';
  $result=sql($sql);
  if(mysql_num_rows($result))
  {
    $row=mysql_fetch_array($result);
    $title1=$row['title'];
    $description1=$row['description'];
    $keywords1=$row['keywords'];
  }
  $sql='select name from types where id="'.$katid.'"';
  $result=sql($sql);
  if(mysql_num_rows($result))
  {
    $row = mysql_fetch_row($result);
    if($title1)
      $title1=$row[0].' - '.$title1;
    else $title1=$row[0];
  }
}
if(!$title1)
  $title1='Палантир - каталог фэнтези сайтов с банерной системой';
else $title1='Палантир - '.$title1;
if(!$description1)
  $description1='Палантир - каталог фэнтези сайтов, ролевая банерная система';
if(!$keywords1)
  $keywords1='фэнтези каталог,банерная система,Palantir,fantasy,tolkien,top,list,site,source,resource,палантир,каталог,фэнтези,ресурсы,сайты';
}
?>
<title><?=$title1;?></title>
<meta name="Description" content="<?=$description1;?>">
<meta name="Keywords" content="<?=$keywords1;?>">
<link rel="stylesheet" href="<?=COMMON_URL;?>etc/stl.css" type="text/css">
<script type="text/javascript" src="<?=COMMON_URL;?>etc/top.js"></script>
<script type="text/javascript" src="<?=COMMON_URL;?>etc/metric.js"></script>

</head>
<body>
<table class="main" cellpadding="0" cellspacing="0" border="0" align="center">
<tr><td height="102" valign="top" colspan="2"><a href="<?=COMMON_URL;?>"><img width="415" height="102" alt="Палантир: каталог фентези, ролевых, аниме ресурсов. Банерная система." src="<?=COMMON_URL;?>graphic/logo_small.gif" border=0></a><!-- put your fucken banner here <a href="/goto/party.photologia.ru"><img src="http://party.photologia.ru/images/info/ah.gif" border=0 style="padding-right:0px"></a>--></td><td width="6" bgcolor="#3D3E46">&nbsp;</td></tr>
<tr>
        <td valign="top" align="center" class="menubg" width="238">


                        <div style="width: 197px" class="bgtop">&nbsp;</div>
<div style="width: 197px;" class="texture"><div style="width: 148px; text-align: left;">
<?
        include('scripts/menu.inc');
?>
</div></div>
<div><img src="<?=COMMON_URL;?>graphic/block_bottom.gif" alt=""></div>

<font size="-1">Cайтов в каталоге:</font><?$row=mysql_fetch_row(sql("select count(*) from sources"));echo $row[0];?><br>
<font   size="-1">За сегодня показов банеров:</font>&nbsp;<?$row=mysql_fetch_row(sql("select count(*) from go"));echo $row[0];?>

<br>

<!-- Yandex.Metrika informer -->
<!--<a href="https://metrika.yandex.ru/stat/?id=24112042&amp;from=informer"
target="_blank" rel="nofollow"><img src="//bs.yandex.ru/informer/24112042/3_0_000080FF_000080FF_1_pageviews"
style="width:88px; height:31px; border:0;" alt="Яндекс.Метрика" title="Яндекс.Метрика: данные за сегодня (просмотры, визиты и уникальные посетители)" onclick="try{Ya.Metrika.informer({i:this,id:24112042,lang:'ru'});return false}catch(e){}"/></a>
-->
<!-- /Yandex.Metrika informer -->
<noscript><div><img src="//mc.yandex.ru/watch/24112042" style="position:absolute; left:-9999px;" alt="" /></div></noscript>
<!-- /Yandex.Metrika counter -->


<script type="text/javascript">
Md=document;Mnv=navigator;
Mrn=Math.random();Mn=(Mnv.appName.substring(0,2)=="Mi")?0:1;Mp=0;Mz="p="+Mp+"&";
Ms=screen;Mz+="wh="+Ms.width+'x'+Ms.height;My="<img src='http://palantir.in/count.php?id=2&today_hits=1&today_hosts=1&total_hosts=1&cid=special_blue.png";My+="&cntc=none&rand="+Mrn+"&"+Mz+"&referer="+escape(Md.referrer)+'&pg='+escape(window.location.href);My+="'  alt='Palantir' title='Хотите такой счётчик? Регистрируйтесь в рейтинге Палантир' border='0' width='88px' height='31px'>";Md.write(My);</script>
<noscript><img src="http://palantir.in/count.php?id=2&today_hits=1&today_hosts=1&total_hosts=1&cid=special_blue.png" alt='Palantir' title="Хотите такой счётчик? Регистрируйтесь в рейтинге Палантир" border=0 width="88px" height="31px"></noscript><br>

<img border=0 src="<?=COMMON_URL;?>graphic/copyright.gif" alt="&copy;"></a><br>

<?
if (!defined('_SAPE_USER'))
        {define('_SAPE_USER', '2679d8db6fb58eb88c77b607fa55e7ac');}
require_once(_SAPE_USER.'/sape.php');

$uri = $_SERVER['REQUEST_URI'];
$opt = array();
$opt['request_uri'] = $uri;
$opt['charset'] = 'UTF-8';

$sape = new SAPE_client($opt);
$x=$sape->return_links();
if($x)echo 'Спонсоры каталога:<li>'.$x.'</li>';
?>
</td>
<td width=712 valign=top>
