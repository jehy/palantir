<?

$Comission_Site_Id=2;
mb_internal_encoding('UTF-8');

function masktags($str)
{
  #$str=str_replace('&','&amp;',$str);
  $str=str_replace('>','&gt;',$str);
  $str=str_replace('<','&lt;',$str);
  #$str=str_replace("'",'"',$str);
  #$str=str_replace('"','&quot',$str);
return $str;
}

function GetName($site_id)
{
$sql='select name from sources where id="'.$site_id.'" LIMIT 1';
$row=mysql_fetch_row(sql($sql));
return $row[0];
}

function MaskLink($url)
{
$url=str_replace('http://','',masktags($url));
//$url=urlencode($url);
return COMMON_URL.'goto/'.($url);
}


function is_utf8($string) {
   
   // From http://w3.org/International/questions/qa-forms-utf-8.html
   return preg_match('%^(?:
         [\x09\x0A\x0D\x20-\x7E]            # ASCII
       | [\xC2-\xDF][\x80-\xBF]             # non-overlong 2-byte
       |  \xE0[\xA0-\xBF][\x80-\xBF]        # excluding overlongs
       | [\xE1-\xEC\xEE\xEF][\x80-\xBF]{2}  # straight 3-byte
       |  \xED[\x80-\x9F][\x80-\xBF]        # excluding surrogates
       |  \xF0[\x90-\xBF][\x80-\xBF]{2}     # planes 1-3
       | [\xF1-\xF3][\x80-\xBF]{3}          # planes 4-15
       |  \xF4[\x80-\x8F][\x80-\xBF]{2}     # plane 16
   )*$%xs', $string);
   
} // function is_utf8

function shortlink($url,$show='')
{
  	$url=urldecode($url);
  	//die($url2.' VS '.$url);
	if(!$show)
		$show=($url);
	
	#if((!is_utf8($url)))
	#	$url=iconv('CP1251','UTF-8',$url);
	#if((!is_utf8($show)))
#		$show=iconv('CP1251','UTF-8',$show);
	
  	#$link=iconv('CP1251','UTF-8',urldecode($addr));
  	#if(!$link)
  	//$link=$url;
  	#$link=urldecode($addr);
  	if(mb_strlen($show)>80)
  		$show=mb_substr($show,0,80).'[...]';
  	#$link=urlencode($link);
  	$url=MaskLink($url);
  	//die($url);
  	//echo '<a href="'.$url.'">'.$url.'</a>';die;
  	return '<a href="'.$url.'">'.$show.'</a>';
}

function f_connect()
{
  #$db = @mysql_connect('localhost', 'seoman', 'm1]3vdnk[0');
  #@mysql_select_db('seoman', $db);
  $db = @mysql_connect('localhost', 'palantir', 'gfkfynbh');
  @mysql_select_db('palantir', $db);
  #mysql_query('set names utf8');
}
f_connect();
DEFINE('DEBUG',1);
if(DEBUG)
  error_reporting(E_ALL ^ E_NOTICE);
else
  error_reporting(0);

DEFINE (TOP,30);
DEFINE (COMMON_URL,'http://palantir.in/');
#TOP=30;
$max_banner_size=20;
$news_to_show=3;
$show_news_on_other_pages=8;
$show_links_for_news=8;

$network[1]['name']='88*31';
$network[1]['width']=88;
$network[1]['height']=31;

$network[2]['name']='100*100';
$network[2]['width']=100;
$network[2]['height']=100;

$network[3]['name']='468*60';
$network[3]['width']=468;
$network[3]['height']=60;

$networks=3;

##################################################################
function error_addlog($text)
{
$text.="\n\nREQUEST data:".print_R($_REQUEST,true)."\n\nSERVER data:".print_R($_SERVER,true);
$sql='INSERT INTO error_log values("","'.$_SERVER['PHP_SELF'].' ('.$_SERVER['REQUEST_URI'].')", CONCAT(CURDATE()," ",CURTIME()), "'.addslashes($_SERVER['QUERY_STRING']).'", "'.addslashes($text).'")';
@mysql_query($sql);//if here is a bug - we shouldn't make endless wheel of fortune
}


function show_error($text)
{
    echo '<div class="error">'.$text.'</div>';
}
function sql($sql)
{
  $result=@mysql_query($sql);
  if($e=mysql_error())
  {
    error_addlog($sql.'\n'.$e);
    if(constant('DEBUG'))
      show_error('MySQL error: '.$e.'<br>'.htmlspecialchars($sql));
  }
return $result;
}
#####################################################

function get_mirror()
{
  $sql='select * from mirrors order by status desc,priority desc limit 1';
  return mysql_fetch_array(sql($sql));
}

if(!function_exists('file_get_contents'))
{
  #Echo '<br>Warning: no PHP function file_get_contents or url wrappers disabled. Trying to implement. Only direct http download';
  function file_get_contents($SrcUrl)
  {
    $handle = fopen($SrcUrl, "r");
    if($hadle===FALSE)
      return FALSE;
    $contents = fread($handle, 1000000);
    fclose($handle);
    return $contents;
  }
}

if(!function_exists('file_put_contents'))
{
   #Echo '<br>Warning: no PHP function file_put_contents. Trying to implement.';
  function file_put_contents($DstUrl,$Data)
  {
    if (!$handle = fopen($DstUrl, 'w'))
        return FALSE;
   if ($n=fwrite($handle, $Data) === FALSE)
       return FALSE;
   else return $n;
   }
}


function showlev($n)
{
  $kats=array();
  $sql='select id from types where parent="'.$n.'"';
  #echo $sql."\n";
  $result=sql($sql);
  if(mysql_num_rows($result))
  {
    while ($row = mysql_fetch_array($result))
    {
        $kats=array_merge($kats,showlev($row['id']));//sources can be registered only in upper level
    }
  }
  else
    $kats[]=$n;
  return $kats;
}

function GetKats($kat_id,$ifstring)
{
  $kats=showlev($kat_id);
  if(!$ifstring)
    return $kats;
  else
  {
    $kats='"'.implode('","',$kats).'"';
    return $kats;
  }
}

function CountPages($kat_id)
{
  $kats=GetKats($kat_id,1);
  $sql='select count(1) from `sources` where `parent` in('.$kats.')';
  $result=sql($sql);
  $row=mysql_fetch_row($result);
  $s_num=$row[0];
  return ceil($s_num/TOP);
}




?>