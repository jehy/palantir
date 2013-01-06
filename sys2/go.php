<?
#jehy redirect system

if($_REQUEST['redirect_c']&&$_SERVER['SCRIPT_URL']=='/')
die('<html><head></head><body><script language="javascript">window.location = "'.$_REQUEST['redirect_c'].'";</script></body></html>');
setcookie('redirect_c','',0,'/');
?>