<?
DEFINE(LINK_SEP, 'goto');
function Redirect()
{
    $goto = '';
    $p = strpos($_SERVER['REQUEST_URI'], '/' . LINK_SEP . '/');
    if ($_REQUEST[LINK_SEP])
        $goto = $_REQUEST[LINK_SEP];
    elseif ($p !== FALSE)
        $goto = substr($_SERVER['REQUEST_URI'], $p + strlen(LINK_SEP) + 2);
    else {
        $url = $_SERVER['REQUEST_URI'];
        $url = explode('/', $url);
        if ($url[sizeof($url) - 2] == LINK_SEP)
            $goto = $url[sizeof($url) - 1];
    }
    if (!strpos($goto, '://'))
        $goto = str_replace(':/', '://', $goto);
    if ($goto)
        redirect2($goto);
}

function redirect2($url)
{
    header('Content-type: text/html; charset="utf-8"', true);
    if ($url)
        @header('Location: http://' . $url);
    ?>
    <html>
<head><title>Перенаправляем</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <meta name="robots" content="noindex,nofollow"/>
    <?php if ($url) echo '<meta http-equiv="refresh" content="0; url=http://' . $url . ';" />'; ?>
</head>
<body style="margin:0;">
<div align="center" style="margin-top: 15em;">
    <?php
    if ($url)
        echo '<noindex>Если вас не перенаправило автоматически, пожалуйста, нажмите <a href="http://' . $url . '">эту ссылку</a> для перехода на сайт ' . $url . '</noindex>';
    else
        echo('Неправильный редирект!');?>
</div>
</body></html><?php die();
}

Redirect();
?>
