<?
#$sys_servers=array('217.107.34.101');
#if(!in_array($_SERVER['REMOTE_ADDR'],$sys_servers))//palantir
#	die;
setcookie('redirect_c',$_REQUEST['url'],time()+20,'/');//for 20 seconds
header('Content-type: image/gif');
echo base64_decode('R0lGODlhAQABAIEAAP///////wAAAAAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw==');//1px gif
?>