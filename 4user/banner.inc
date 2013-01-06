<?
#echo $our_user_id.'!!';
//$sql='select id from baners,sources,users where((sources.id=baners.site_id)and(sources.user_id=users.id)and(users.id='.$our_user_id.'))';
$sql='select sources.id from sources,users where((sources.id="'.$site_id.'")and(sources.user_id=users.id)and(users.id="'.$our_user_id.'")) limit 1';
//echo $sql;
if(mysql_num_rows(sql($sql)))
{
if($ac=='code')include('4user/banner/code.inc');
elseif($ac=='view')include('4user/banner/stats.inc');
elseif($ac=='upload')include('4user/banner/upload.inc');
elseif($ac=='status')include('4user/banner/status.inc');
elseif($ac=='clicks')include('4user/banner/refs.inc');
}
else echo'<h2>Неверный идентификатор сайта!</h2>';

?>
