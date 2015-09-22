<h2>Код счётчика сгенерирован</h2>
Полученный код необходимо разместить на страницах вашего сайта:<br>
Код:<br><br><?
$img = COMMON_URL . 'count.php?id=' . $site_id;
if ($today_hits)
    $img .= '&amp;today_hits=1';
if ($today_hosts)
    $img .= '&amp;today_hosts=1';
if ($total_hits)
    $img .= '&amp;total_hits=1';
if ($total_hosts)
    $img .= '&amp;total_hosts=1';
$img .= '&amp;cid=' . $cid;

function showCNT($t = 0, $img, $site_id)
{
    if ($t) {
        ?>
<a title="Каталог фэнтези сайтов Палантир" href='<?= COMMON_URL . '?from=' . $site_id; ?>' target='_blank'>
<script type="text/javascript">
Mz += "wh=" + screen.width + 'x' + screen.height;
My = "<img src='<?=$img;?>";
My += "&amp;cntc=none&amp;rand=" + Math.random() + "&amp;referer=" + encodeURIComponent(document.referrer);
My += '&amp;pg=' + encodeURIComponent(window.location.href);
My += "'  alt='Palantir' title='Каталог фэнтези сайтов Палантир' border='0' width='88px' height='31px'>";
document.write(My);</script>
<noscript><img src="<?= $img; ?>" alt='Palantir' title="Каталог фэнтези сайтов Палантир" border=0 width="88px"
           height="31px"></noscript>
</a><?
    } else {
?><a title="Каталог фэнтези сайтов Палантир" href='<?= COMMON_URL . '?from=' . $site_id; ?>' target='_blank'>
<img src="<?= $img; ?>" alt='Palantir' title="Каталог фэнтези сайтов Палантир" border=0 width="88px"
     height="31px"></a>
    <?
    }
}

?>
Новый код, с яваскрипт и полной статистикой:<br>
<textarea readonly cols="80" rows="6">
    <? showCNT(1, $img, $site_id); ?>
</textarea>

Старый вариант, без яваскрипта и без расширенной статистики:<br>
<textarea readonly cols="80" rows="6">
    <? showCNT(0, $img, $site_id); ?>
</textarea>
<br>На сайте это будет выглядеть так:<br><br>
<? showCNT(0, $img, $site_id); ?><br>
Приятного вам посчёта!

<br><br>
P.S. Кстати говоря, нам будет очень приятно, если где-нибудь в разделе "ссылки", "друзья" и т.д. вы поставите на нас текстовую ссылку. По нажатию на неё пользователь попадёт на страницу, на которой у нас описан ваш сайт. Код ссылки:
<textarea readonly cols="80" rows="2"><a href='<?= COMMON_URL; ?>index.php?from=<?= $site_id; ?>' title="палантир"
                                         target='_blank'>Каталог фэнтези сайтов Палантир</a></textarea>
<br><br>
P.P.S. И ещё - если вы хотите как-то заработать на своём сайте, или хотя бы его окупить, рекомендую использовать
<br><a target="_blank" href="http://www.sape.ru/r.f6054dfcc2.php"><img src="http://img.sape.ru/bn/3.gif"
                                                                       border="0"/></a><br>
<a href='index.php?page=user'>Вернуться в систему администрирования</a><br>