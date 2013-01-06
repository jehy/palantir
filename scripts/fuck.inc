<?php

$cheaters=array(3474);
if(in_array($id,$cheaters))
{
    header('WWW-Authenticate: Basic realm="'.str_repeat("ISCELI SEBJA SAM!",50).'"');
    header('HTTP/1.0 401 Unauthorized');
die;
}

$fuckup=array(2332,14231);
if(in_array($id,$fuckup))
{
    header('location: http://anidb.ru/uni/huj.png');
	die;
}
?>
