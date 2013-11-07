<?
#jehy redirect system

if ($_REQUEST['redirect_c'] && $_SERVER['SCRIPT_URL'] == '/')
  die('<html><head></head><body><script language="javascript">window.location = "' . $_REQUEST['redirect_c'] . '";</script></body></html>');
setcookie('redirect_c', '', 0, '/');

$REQUEST_URI = $_SERVER['REQUEST_URI'];
$REMOTE_ADDR = $_SERVER['REMOTE_ADDR'];
#die('fuck');
$t = microtime();
include ('scripts/common.inc');
include('scripts/defence.inc');
$mirror = '';
#include('checkup.php');###TEMPORARY!! While only 1 mirror! Or user will die, waiting!
include('scripts/user.inc');
authorisate();
get_user_type();
if (($ac == 'changedata') && ($step == 2) && ($page == 'user'))
  $error = changenfo();
$inc = '';

/* Do not need on new location
$domain=str_replace('/','',$HTTP_HOST);
$domain=explode('.',strtolower($domain));
if($domain[0]=='fantasy')
{
    if($rand)
      header('Location: http://Palantir.in?from='.$from.'&rand='.$rand.'&url='.$url);
    elseif($from)
      header('Location: http://Palantir.in?from='.$from);
    else
      header('Location: http://Palantir.in');
    die();
}
*/
if ((isset($from)) && (isset($rand))) //perehod
{
  $sql = 'select banner_id,site_id,url from go where rand="' . $rand . '"';
  $result = sql($sql);
  if (mysql_num_rows($result))
  {
    $row = mysql_fetch_array($result);
    $sql = 'update banners set clicked=clicked+1 where id=' . $row['banner_id'];
    sql($sql);
    $d = date("d");
    $sql = 'insert into clicks values(' . $row['site_id'] . ',' . $row['banner_id'] . ',"' . addslashes($row['url']) . '","' . $d . '")';
    sql($sql);
    $sql = 'select name,url from sources where id=' . $row['site_id'];
    $result = sql($sql);
    $row = mysql_fetch_array($result);
    #header('location: '.$row['url']);exit;
    #header("HTTP/1.1 301 Moved Permanently");

    header('HTTP/1.0 404 Not Found');
    header("Status: 404 Not Found");

    header('Content-type: text/html; charset="utf-8"', true);
    ?><!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
  <html>
  <head>
      <STYLE TYPE="text/css">body {
          background-color: 6 F7F8F;
      }

      A:visited {
          COLOR: white;
      }

      A:link {
          COLOR: white;
      }</style>
      <LINK REL="SHORTCUT ICON" HREF="<?=COMMON_URL;?>favicon.ico">
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
      <META http-equiv="refresh" content="2; URL=<?=$row['url'];?>">
  </head>
  <body>
  <div align="center">
      Большое спасибо за использование баннерной системы <a target="_blank" href="<?=COMMON_URL;?>">"Палантир"</a><br>
      Через две секунды вы будете направлены на сайт "<?=$row['name']?>";<br>
      Если этого не случилось - нажмите <a href="<?=$row['url']?>">на эту ссылку.</a></div>
  </body>
  </html><?die();
  }
  else $page = 'index';
  //if we dunno where to go^^
}


if ($from)
{
  $sql = 'select types.name_eng,sources.today_hosts,sources.parent,sources.name from sources,types where ((sources.id="' . $from . '")and(types.id=sources.parent)) limit 1';
  #$sql='select types.name_eng,sources.today_hosts,sources.parent,sources.name from sources,types where ((sources.id="'.$from.'")) limit 1';
  $result = sql($sql);
  if (mysql_num_rows($result))
  {
    $row = mysql_fetch_array($result);
    $sql = 'SELECT `id` FROM `sources` WHERE ((parent=' . $row['parent'] . ')and((today_hosts>"' . $row['today_hosts'] . '")or(name<"' . addslashes($row['name']) . '")and(today_hosts="' . $row['today_hosts'] . '")))';
    #$sql='select id from sources where ((today_hosts>='.$row['today_hosts'].')and(name<"'.$row['name'].'"))';
    #die($sql);
    $result = sql($sql);
    $frompage = ceil((mysql_num_rows($result) + 1) / TOP);
    if ($frompage == 0) $frompage = 1;
    $url = 'http://palantir.in/top/' . $row['name_eng'] . '/' . $frompage . '.html#' . $from;
    #$url='http://palantir.in/top/Fantasy/'.$frompage.'.html#'.$from;
    header("HTTP/1.1 301 Moved Permanently");
    header('Location: ' . $url);
    die('<html><head><META http-equiv="refresh" content="0; URL=' . $url . '"></head><body></body></html>');
  }
  else die('Данного сайта в каталоге не найдено. Он вам показался. Возможно, вы воспользовались неверной ссылкой - или он был удалён.');
  $page = 'top';
}


if ($katid) //old system link
{
  $sql = 'select `name_eng` from `types` where `id`="' . $katid . '"';
  $result = sql($sql);
  if (mysql_num_rows($result))
  {
    $row = mysql_fetch_row($result);
    $katname = $row[0];
    $url = 'http://palantir.in/top/' . $katname;
    if ($frompage) $url .= '/' . $frompage;
    $url .= '.html';
    header("HTTP/1.1 301 Moved Permanently");
    header('Location: ' . $url);
    die('<html><head><META http-equiv="refresh" content="0; URL=' . $url . '"></head><body></body></html>');
  }
}
######################################
######             Mode rewrite script
##########
$u = substr($REQUEST_URI, 1);
//echo $u;
//if(strpos($u,'/')===true)
//{
if (strpos($u, '.html'))
{
  $u = explode('.html', $u);
  $r = explode('/', $u[0]);
  $page = $r[0];
  if ($page == 'top')
  {
    $katname = $r[1];
    //$action=$r[2];
    $frompage = $r[2];
    if (!$frompage)
      $frompage = 1;
  }
}
//else $page='404';
//}
if ($katname)
{
  $sql = 'select `id` from `types` where `name_eng`="' . $katname . '"';
  $result = sql($sql);
  if (mysql_num_rows($result))
  {
    $row = mysql_fetch_row($result);
    $katid = $row[0];
  }
  else
  {
    header('Location: http://Palantir.in');
    header('HTTP/1.0 404 Not Found');
    header("Status: 404 Not Found");
    die('<html><head><META http-equiv="refresh" content="0; URL=' . COMMON_URL . '404.html"></head><body></body></html>');
  }

}
#########################
########################
#######################
function index($str, $arr)
{
  foreach ($arr as $key => $val) if ($val == $str) return $key;
  return -1;
}

if (@$ac == 'login')
{
  if ((!$our_user) && (!$admin_user)) $page = 'login';
  else $page = 'user';
}
$pages = 'index,reg,login,user,admin,top,reg,stats,banner,mail,about,faq,maintop,reveal,404';
$pages = explode(',', $pages);
if (!$page && $_SERVER['REQUEST_URI'] == '/') $page = 'index';
if (in_array($page, $pages))
{
  include ('scripts/no_cache.inc');
}
else
{
  header('Location: http://Palantir.in');
  header('HTTP/1.0 404 Not Found');
  header("Status: 404 Not Found");
  die('<html><head><META http-equiv="refresh" content="0; URL=' . COMMON_URL . '404.html"></head><body></body></html>');
}
$incs = 'index,reg,login,user,admin,showtop,reg,stats,banner,mail,about,faq,maintop,reveal,404';
$incs = explode(',', $incs);
$dirs = 'pages,4user,4user,4user,4admin,4user,4user,4user/counter,4user,4user,pages,pages,pages,4user,pages';
$dirs = explode(',', $dirs);
$num = index($page, $pages);

include ('scripts/head.inc');
include($dirs[$num] . '/' . $incs[$num] . '.inc');
//if(@$page!='18')
{
  echo'<br>';
  include ('scripts/footer.inc');
}
?>
