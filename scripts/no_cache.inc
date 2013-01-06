<?
if(0)
{
	header('HTTP/1.1 200 OK');
	Header("Expires: Mon, 26 Jul 2002 05:00:00 GMT");
	HEADER("Last-Modified: ".gmdate("D, d M Y H:i:s")."GMT");
	HeAdEr("Cache-Control: no-cache, must-revalidate");
	hEaDeR("Pragma: no-cache");
	#header('Transfer-Encoding: chunked');
}
	header('Content-type: text/html; charset="utf-8"',true);
?>