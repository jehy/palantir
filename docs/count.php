<?

if(!is_numeric(@$_REQUEST['id']))die;
else $id=$_REQUEST['id'];
$img=addslashes(@$_REQUEST['img']);
$pic=addslashes(@$_REQUEST['pic']);
$type=addslashes(@$_REQUEST['type']);
$cid=addslashes(@$_REQUEST['cid']);
#$referer=addslashes(iconv('utf8','cp1251',$_REQUEST['referer']));
$referer=addslashes(@$_REQUEST['referer']);
if(!mb_check_encoding($referer, 'UTF-8'))
    $referer=mb_convert_encoding($referer,'UTF-8');
    
$today_hits=addslashes(@$_REQUEST['today_hits']);
$total_hits=addslashes(@$_REQUEST['total_hits']);
$today_hosts=addslashes(@$_REQUEST['today_hosts']);
$total_hosts=addslashes(@$_REQUEST['total_hosts']);
if((!strpos($img,'.'))&&(($img!='')))$img.='.png';
if((!strpos($pic,'.'))&&(($pic!='')))$pic.='.png';
if(isset($_SERVER['HTTP_REFERER']))
    $ref=addslashes($_SERVER['HTTP_REFERER']);
else $ref='';


if(stripos($ref,'lifesoccer.ru') || stripos ($ref,'lifesoccer.ru'))
    Header('Location: http://palantir.in/uni/counters/standard/1_2.png');

$agent=addslashes($_SERVER['HTTP_USER_AGENT']);
$errors='';
Header('Expires: Mon, 26 Jul 2002 05:00:00 GMT');
HEADER('Last-Modified: '.gmdate('D, d M Y H:i:s').'GMT');
HeAdEr('Cache-Control: no-cache, must-revalidate');
hEaDeR('Pragma: no-cache');

include('scripts/fuck.inc');
$ip_w=sprintf("%u",ip2long($_SERVER['REMOTE_ADDR']));
include('scripts/common.inc');
$sql='select 1 from addition where ((ip="'.$ip_w.'") and (site_id="'.$id.'")) limit 1';
$result=sql($sql);
$set='update sources set ';
if($cid!='')
{
        if(!$today_hits&&!$total_hits&&!$today_hosts&&!$total_hosts)
        {
                $c=$cid . ' - static ';
        }
        elseif($today_hosts&$today_hits&$total_hosts)
        {
                $c=$cid . ' - num(hosts) ';
        }
        else
        {
                $c=$cid . ' - num(hits) ';
        }
}
elseif($pic!='')
{
        $c=$pic . ' - static ';
}
elseif($img!='')
{
        $c=$img . ' - num(hosts) ';
}
else
{
        $c= $img . $pic. $cid;
}
$uphits='today_hits=today_hits+1,total_hits=total_hits+1,cid="' . $c . '"';
$uphosts='today_hosts=today_hosts+1, total_hosts=total_hosts+1';
if(!mysql_num_rows($result))
{
  $time=date("H");
  $sql='INSERT INTO addition VALUES (NULL, '.$ip_w.', "'.$ref.'","'.$referer.'","'.$agent.'",'.$id.','.$time . ')';
  sql($sql);
  $sql=$set.$uphits.', '.$uphosts;
}
else $sql=$set.$uphits;
$sql=$sql.' where id="'.$id.'" limit 1';
sql($sql);
if(mysql_affected_rows()!=1)$errors=$errors."1";
if($errors)
{ mysql_close();
  $im=imageCreate(88, 31);
  $textcol=imagecolorallocate($im, 0, 0, 0);
  $back=imagecolorallocate($im, 111, 127, 143);
  imagefill($im, 0, 0, $back);
  imagestring($im, 14, 0, 00, '  errors'.$errors, $textcol);
  imagepng($im);
}
else
{
  $mirror=get_mirror();
  ##################   OLD, SAVED FOR COMPATIBILITY
  if(@$_GET['pic'])
  {
    mysql_close();
    Header('location: '.$mirror['url'].'counters/standard/'.@$pic);
  }
  elseif(@$_GET['img'])
  {
    $sql='select today_hosts,today_hits,total_hosts,total_hits from sources where id="'.$id.'" limit 1';
    $result=sql($sql);
    $row=mysql_fetch_array($result);
    mysql_close();
    Header('location: '.$mirror['url'].'counters/count.php?cid='.$img.'&today_hosts='.$row['today_hosts'].'&total_hosts='.$row['total_hosts']);
  }
  ####################   NEW
  elseif(@$cid)
  {
  if(!$today_hits&&!$total_hits&&!$today_hosts&&!$total_hosts){
    mysql_close();
    Header('location: '.$mirror['url'].'counters/standard/'.@$cid);
    }
  else{
  $sql='select today_hosts,today_hits,total_hosts,total_hits from sources where id="'.$id.'" limit 1';
  $result=sql($sql);
  $row=mysql_fetch_array($result);
  mysql_close();
  if($today_hosts&$today_hits&$total_hosts){Header('location: '.$mirror['url'].'counters/count.php?cid='.$cid.'&today_hits='.$row['today_hits'].'&today_hosts='.$row['today_hosts'].'&total_hosts='.$row['total_hosts']);}
  elseif($today_hosts&$total_hosts)Header('location: '.$mirror['url'].'counters/count.php?cid='.$cid.'&today_hosts='.$row['today_hosts'].'&total_hosts='.$row['total_hosts']);
  }
  }
}
?>
