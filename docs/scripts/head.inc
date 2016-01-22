<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
    <LINK REL="SHORTCUT ICON" HREF="<?= COMMON_URL; ?>favicon.ico">
    <meta http-equiv="content-type" content="text/html; charset=UTF-8">
    <meta name='yandex-verification' content='53816566f67c50d7'>
    <meta name='yandex-verification' content='7524fb51cb1def33'>
    <meta name="verify-v1" content="zxdRsPVLYr6H4N3hHRloXU23BNsX5ffu9nDJGOgWAWs=">
    <meta name="verify-v1" content="xzEA/8SNtvV3ZnVQKNYVTvuYX2u1/2zhJ5sUjfUcKlw=">
    <?
    if ($page != 'admin') {
        $title1 = $keywords1 = $description1 = '';
        if ($page == 'top') {

            if ((!isset($frompage)) || ($frompage < 1))
                $frompage = 1;
            $from2 = ($frompage - 1) * TOP;
            $sql = 'select * from types_meta where `type_id`=? order by `id` LIMIT ?,1';
            $stmt = $mysqli->prepare($sql);
            $limit = ($frompage - 1);
            $stmt->bind_param('ii', $katid, $limit);
            $stmt->execute();
            $result = $stmt->get_result();
            if ($result->num_rows) {
                $row = $result->fetch_array(MYSQLI_ASSOC);
                $title1 = $row['title'];
                $description1 = $row['description'];
                $keywords1 = $row['keywords'];
            }
            $sql = 'select name from types where id=?';
            $stmt = $mysqli->prepare($sql);
            $stmt->bind_param('i', $katid);
            $stmt->execute();
            $result = $stmt->get_result();
            if ($result->num_rows) {
                $row = $result->fetch_row();
                if ($title1)
                    $title1 = $row[0] . ' - ' . $title1;
                else $title1 = $row[0];
            }
        }
        if (!$title1)
            $title1 = 'Палантир - каталог фэнтези сайтов с банерной системой';
        else $title1 = 'Палантир - ' . $title1;
        if (!$description1)
            $description1 = 'Палантир - каталог фэнтези сайтов, ролевая банерная система';
        if (!$keywords1)
            $keywords1 = 'фэнтези каталог,банерная система,Palantir,fantasy,tolkien,top,list,site,source,resource,палантир,каталог,фэнтези,ресурсы,сайты';
    }
    ?>
    <title><?= $title1; ?></title>
    <meta name="Description" content="<?= $description1; ?>">
    <meta name="Keywords" content="<?= $keywords1; ?>">
    <link rel="stylesheet" href="<?= COMMON_URL; ?>etc/stl.css" type="text/css">
    <script type="text/javascript" src="<?= COMMON_URL; ?>etc/top.js"></script>

</head>
<body>
<table class="main" cellpadding="0" cellspacing="0" border="0" align="center">
    <tr>
        <td class="menubg" height="102" valign="top" colspan="2"><a href="<?= COMMON_URL; ?>"><img class="logo"
                                                                                                   alt="Палантир: каталог фентези, ролевых, аниме ресурсов. Банерная система."
                                                                                                   src="<?= COMMON_URL; ?>graphic/logo_small.png"
                                                                                                   border=0></a>
        </td>
        <td width="6" bgcolor="#3D3E46">&nbsp;</td>
    </tr>
    <tr>
        <td valign="top" align="left" class="menubg" width="238">


            <div class="navi">
                <?
                include('scripts/menu.inc');
                ?>
            </div>

            <div class="navi-links">
            <span
                class="smaller">Cайтов в каталоге:</span><?
                $result = $mysqli->query("select count(*) from sources");
                $row = $result->fetch_row();
                echo $row[0]; ?><br>
            <span
                class="smaller">За сегодня показов банеров:</span>&nbsp;<?
                $result = $mysqli->query("select count(*) from go");
                $row = $result->fetch_row();
                echo $row[0]; ?>

                <br>

                <div style="margin-top:10px;margin-bottom: 10px">
                    <a title="Каталог фэнтези сайтов Палантир" href='https://palantir.in/?from=2' target='_blank'>
                        <script type="text/javascript">
                            Mz = "wh=" + screen.width + 'x' + screen.height;
                            My = "<img src='https://palantir.in/count.php?id=2&today_hits=1&today_hosts=1&total_hosts=1&cid=special_blue.png";
                            My += "&cntc=none&rand=" + Math.random() + "&referer=" + encodeURIComponent(document.referrer);
                            My += '&pg=' + encodeURIComponent(window.location.href);
                            My += "'  alt='Palantir' title='Каталог фэнтези сайтов Палантир' border='0' width='88px' height='31px'>";
                            document.write(My);</script>
                        <noscript><img src="https://palantir.in/count.php?id=2&today_hits=1&today_hosts=1&total_hosts=1&cid=special_blue.png" alt='Palantir' title="Каталог фэнтези сайтов Палантир" border=0 width="88px"
                                       height="31px"></noscript>
                    </a>
                </div>

                <img border=0 src="<?= COMMON_URL; ?>graphic/copyright.gif" alt="&copy;"></a><br>

                <?
                if (!defined('_SAPE_USER')) {
                    define('_SAPE_USER', '2679d8db6fb58eb88c77b607fa55e7ac');
                }
                require_once(_SAPE_USER . '/sape.php');

                $uri = $_SERVER['REQUEST_URI'];
                $opt = array();
                $opt['request_uri'] = $uri;
                $opt['charset'] = 'UTF-8';

                $sape = new SAPE_client($opt);
                $x = $sape->return_links();
                if ($x) echo 'Спонсоры каталога:<li>' . $x . '</li>';
                ?>
            </div>
        </td>
        <td width=800 valign=top>
