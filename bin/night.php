<?
#ob_start();
error_reporting(E_ALL ^ E_NOTICE);
echo "\n Starting refresh script, time ".date('Y-m-d H:i:s').":\n";
$t1=microtime();
DEFINE('MAPFILE','/web/palantir/docs/sitemap.xml');
include('/web/palantir/docs/scripts/common.inc');
#function sql($q)
#{return false;
#}

$c=0;
if (file_exists(MAPFILE))
   if(date('d',filemtime(MAPFILE))!=date('d'))
	{
	    echo "\nGenerating sitemap\n";
		if(touch(MAPFILE))
		{
   			set_time_limit(120);
   			include('/web/palantir/bin/map.inc');
		}
	}

echo "\n Updating banner stats \n";
////drop those who have no active banners but have shows
$sql='SELECT s.site_id FROM shows s LEFT JOIN banners b ON (s.site_id=b.site_id AND b.type=s.type AND b.status=1 )WHERE  b.id IS NULL';
$result=sql($sql);
while($row=mysql_fetch_row($result))
{
  $sql='DELETE FROM `shows` WHERE site_id ='.$row[0];
  sql($sql);
}


////   All/distinct IP stats stats
sql('update sources set ban_koef=0');
#$sql='UPDATE sources s SET ban_koef=(SELECT  COUNT(DISTINCT ip)/COUNT(1) AS cnt FROM go WHERE site_id=s.id)';
#$result=sql($sql);
$sql='SELECT  from_site,COUNT(1)/COUNT(DISTINCT ip) AS cnt FROM go GROUP BY from_site';
$result=sql($sql);
while($row=mysql_fetch_array($result))
  sql('update sources set ban_koef='.ceil($row['cnt']).' where id='.$row['from_site']);

#add if not enough
$sql='SELECT COUNT(*) AS num,type FROM shows GROUP BY TYPE HAVING num <100';
$result=sql($sql);
while($row=mysql_fetch_array($result))
{
  $num=$row['num'];
  while($num<101)
  {
    sql('insert into shows values('.$Comission_Site_Id.','.$row['type'].')');
    $num++;
  }
}
///////// stats for banners
$sql='UPDATE `banners` b SET shown=shown+(SELECT COUNT(banner_id) FROM `go` WHERE banner_id = b.id)';
sql($sql);



echo "\n Resetting counters \n";
////////////////////////////// counter reset
$sql='update `sources` set today_hosts=0,today_hits=0';
sql($sql);

$sql='truncate table `addition`';
sql($sql);
$sql='ALTER TABLE `addition` AUTO_INCREMENT = 1';
sql($sql);

//////// cleaning stats
$sql="truncate table `go`";
sql($sql);
$sql='ALTER TABLE `go` AUTO_INCREMENT = 1';
sql($sql);

$d=date("d");
$sql="delete from `clicks` where ((date<($d-3)) or (date>$d))";
sql($sql);

$t2=microtime();

#echo "\nScript completed in ".(($t2-$t1)/1000/1000)." seconds";
echo "\n Script completed on ".date('Y-m-d H:i:s');


#echo 'Request info: '."\n";
#print_R($_REQUEST);
#echo 'Server info: '."\n";
#print_R($_SERVER);
#$buffer=ob_get_contents();
#ob_end_flush();
#mail('fate@jehy.ru','Refresh counters OK','Happened: '.date('Y-m-d')."\n".'Script output: '.$buffer);

?>
