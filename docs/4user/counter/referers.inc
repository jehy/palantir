Имеются в виду страницы, с которых попадали на сайт уникальные посетители<br>

<?

mb_internal_encoding("UTF-8");

function is_blog($url)
{
    $bl = array('liveinternet.ru', 'livejournal.com', 'diary.ru', 'vkontakte.ru', 'ya.ru', 'blogs.mail.ru', 'myspace.com', 'facebook.com', 'twitter.com');
    for ($i = 0; $i < sizeof($bl); $i++) {
        if (mb_strpos($url, $bl[$i]) !== FALSE)
            return $bl[$i];
    }
    return FALSE;
}

$visits = array();
$engines = array();
$blogs = array();
$wpadmin = array();
$sql = 'select count(*) as `quantity`, `referer2` from `addition` where `site_id`=? group by `referer2` order by `quantity` desc,`referer2`';

$stmt = $mysqli->prepare($sql);
$stmt->bind_param('i', $site_id);
$stmt->execute();
$result = $stmt->get_result();
if ($result->num_rows)
    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
        if ($row['referer2']) {
            $p = mb_strpos($row['referer2'], '/', 7);
            $site = mb_substr($row['referer2'], 7, $p - 7 + 1);
            $addr = mb_substr($row['referer2'], $p + 1);
            $query = '';
            $page = '1';
            #### mail.ru
            if ((($s = mb_strpos($addr, 'q=')) !== FALSE) && mb_strpos($site, 'mail.ru') !== FALSE) {
                $s += 2;
                for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);
                $s = mb_strpos($addr, 'sf=');
                if ($s !== FALSE) {
                    $s += 3;
                    for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                        if ($addr[$x] == '&')
                            break;
                    }
                    $page = floor(((int)mb_substr($addr, $s, $x - $s)) / 10) + 1;
                }
                $engines['mail.ru']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity'], 'page' => $page);
                $engines['mail.ru']['count'] += $row['quantity'];
            } ### google
            elseif ((($s = mb_strpos($addr, 'q=')) !== FALSE) && mb_strpos($site, 'google.') !== FALSE) {
                $s += 2;
                for ($x = $s; ($x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);
                $s = mb_strpos($addr, 'start=');
                if ($s !== FALSE) {
                    $s += 6;
                    for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                        if ($addr[$x] == '&')
                            break;
                    }
                    $page = floor((int)mb_substr($addr, $s, $x - $s)) / 10 + 1;
                }
                $engines['google']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity'], 'page' => $page);
                $engines['google']['count'] += $row['quantity'];
            } ### yandex
            elseif ((($s = mb_strpos($addr, 'text=')) !== FALSE) && ((mb_strpos($site, 'yandex.ru') !== FALSE) || ($site == 'ya.ru') || ($site == 'www.ya.ru'))) {
                $s += 5;
                for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);

                $s = mb_strpos($addr, 'p=');
                if ($s !== FALSE) {
                    $s += 2;
                    for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                        if ($addr[$x] == '&')
                            break;
                    }
                    $page = floor((int)mb_substr($addr, $s, $x - $s)) + 1;
                }
                $engines['yandex']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity'], 'page' => $page);
                $engines['yandex']['count'] += $row['quantity'];
            } ### msn
            elseif ((($s = mb_strpos($addr, 'q=')) !== FALSE) && mb_strpos($site, 'search.msn.com') !== FALSE) {
                $s += 2;
                for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);

                $s = mb_strpos($addr, 'first=');
                if ($s !== FALSE) {
                    $s += 6;
                    for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                        if ($addr[$x] == '&')
                            break;
                    }
                    $page = floor(((int)mb_substr($addr, $s, $x - $s)) / 10) + 1;
                }

                $engines['msn']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity'], 'page' => $page);
                $engines['msn']['count'] += $row['quantity'];
            } ### nigma
            elseif ((($s = mb_strpos($addr, 's=')) !== FALSE) && mb_strpos($site, 'nigma.ru') !== FALSE) {
                $s += 2;
                for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);

                $s = mb_strpos($addr, 'startpos=');
                if ($s !== FALSE) {
                    $s += 9;
                    for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                        if ($addr[$x] == '&')
                            break;
                    }
                    $page = floor(((int)mb_substr($addr, $s, $x - $s)) / 10) - 1;
                }

                $engines['nigma.ru']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity'], 'page' => $page);
                $engines['nigma.ru']['count'] += $row['quantity'];
            } ### search.live.com
            elseif ((($s = mb_strpos($addr, 'q=')) !== FALSE) && mb_strpos($site, 'search.live.com') !== FALSE) {
                $s += 2;
                for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);
                $s = mb_strpos($addr, 'first=');
                if ($s) {
                    $page = floor((int)mb_substr($addr, $s + 6) / 10) + 1;
                }
                $engines['search.live.com']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity']);
                $engines['search.live.com']['count'] += $row['quantity'];
            } elseif ((($s = mb_strpos($addr, 'query=')) !== FALSE) && mb_strpos($site, 'rambler.ru') !== FALSE) {
                $s += 6;
                for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);
                $s = mb_strpos($addr, 'page=');
                if ($s !== FALSE) {
                    $s += 5;
                    for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                        if ($addr[$x] == '&')
                            break;
                    }
                    $page = (int)mb_substr($addr, $s, $x - $s);
                }


                $engines['rambler']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity'], 'page' => $page);
                $engines['rambler']['count'] += $row['quantity'];
            } elseif ((($s = mb_strpos($addr, 'q=')) !== FALSE) && mb_strpos($site, 'bing.com') !== FALSE) {
                $s += 2;
                for ($x = $s; (($x < $s + 200) && $x < mb_strlen($addr)); $x++) {
                    if ($addr[$x] == '&')
                        break;
                }
                $query = mb_substr($addr, $s, $x - $s);
                $engines['bing']['queries'][] = array('query' => $query, 'link' => $row['referer2'], 'quantity' => $row['quantity'], 'page' => 0);
                $engines['bing']['count'] += $row['quantity'];
            }
            ################################################################################
            #blogs
            elseif ($bl = is_blog($site)) {
                $blogs[$bl]['count'] += $row['quantity'];
                $blogs[$bl]['urls'][$site . $addr] += $row['quantity'];
            }

            ################################################################################
            #wordpress admin
            elseif (mb_strpos($addr, 'wp-admin') !== FALSE)
                $wpadmin[$site . $addr] += $row['quantity'];
            ################################################################################
            #other
            else {
                $visits[$site]['count'] += $row['quantity'];
                if ($addr)
                    $visits[$site]['urls'][$addr] += $row['quantity'];
            }
        }
    }
mysql_free_result($result);

if (sizeof($visits) || sizeof($engines))
{
echo 'Откуда посещали сайт "<strong>' . GetName($site_id) . '</strong>":<br><br>';
if (sizeof($engines))
{
?>
<div style="background-color:#FFFFFF;color:black;padding:5px;">Нам кажется, к вам волшебно телепортировались с каких-то
    чудных поисковиков:
</div>
<table cellpadding="0" cellspacing="0" width="100%">
    <tr class="bgdark">
        <td colspan="2" style="padding-left:20px;" class="bgdark">Поисковый запрос:</td>
        <td>Номер страницы:</td>
        <td>Кол-во посещений:</td>
    </tr>
    <tr class="bgwhite">
        <td class="bgwhite" colspan="3">&nbsp;</td>
    </tr><?
    foreach ($engines as $name => $content) {
        echo '<tr class="bgdark"><td colspan="3" style="padding-left:20px;"  class="bgdark">' . $name . '</td><td>' . $content['count'] . '</td></tr>';
        for ($i = 0; $i < sizeof($content['queries']); $i++) {
            $query = $content['queries'][$i]['query'];
            $link = $content['queries'][$i]['link'];
            echo '<tr class="bgdark"><td class="bgdark" style="padding-left:20px;" width="60px">+</td><td>' . shortlink($link, urldecode($query)) . '</td><td >' . $content['queries'][$i]['page'] . '</td><td >' . $content['queries'][$i]['quantity'] . '</td></tr>';
        }
        echo '<tr class="bgwhite"><td class="bgwhite" colspan="4">&nbsp;</td></tr>';
    }
    echo '</table><br><br>';
    }
    if (sizeof($blogs))
    {

    ?>
    <div style="background-color:#FFFFFF;color:black;padding:5px;">Заходы с блогов:</div>
    <table cellpadding="0" cellspacing="0" width="100%">
        <tr class="bgdark">
            <td style="padding-left:20px;" colspan="2" class="bgdark">Страница:</td>
            <td>Кол-во посещений:</td>
        </tr>
        <tr class="bgwhite">
            <td class="bgwhite" colspan="3">&nbsp;</td>
        </tr><?
        foreach ($blogs as $site => $urls) {
            if (sizeof($blogs[$site]['urls']) > 1)## If many
            {
                echo '<tr class="bgdark"><td style="padding-left:20px;" colspan="2" class="bgdark">' . shortlink($site) . '</td><td>' . $visits[$site]['count'] . '</td></tr>';
                foreach ($blogs[$site]['urls'] as $addr => $val) {
                    echo '<tr class="bgdark"><td class="bgdark" style="padding-left:20px;" width="60px">+</td><td >' . shortlink($addr) . '</td><td >' . $val . '</td></tr>';
                }
            } elseif (sizeof($blogs[$site]['urls'])) {
                foreach ($blogs[$site]['urls'] as $addr => $val) {
                    echo '<tr class="bgdark"><td class="bgdark" style="padding-left:20px;" colspan="2">' . shortlink($addr) . '</td><td >' . $val . '</td></tr>';
                }
            } else echo '<tr class="bgdark"><td class="bgdark" style="padding-left:20px;" colspan="2">' . shortlink($site) . '</td><td>' . $visits[$site]['count'] . '</td></tr>';
            echo '<tr class="bgwhite"><td class="bgwhite" colspan="4">&nbsp;</td></tr>';
        }


        echo '</table>';

        }
        if (sizeof($wpadmin))
        {
        ?>
        <div style="background-color:#FFFFFF;color:black;padding:5px;">Заходы с админок вордпресса:</div>
        <table cellpadding="0" cellspacing="0" width="100%">
            <tr class="bgdark">
                <td style="padding-left:20px;" colspan="2" class="bgdark">Страница:</td>
                <td>Кол-во посещений:</td>
            </tr>
            <tr class="bgwhite">
                <td class="bgwhite" colspan="3">&nbsp;</td>
            </tr><?
            foreach ($wpadmin as $site => $count) {
                echo '<tr class="bgdark"><td style="padding-left:20px;" colspan="2" class="bgdark">' . shortlink($site) . '</td><td>' . $count . '</td></tr>';
            }
            echo '</table>';
            }
            if (sizeof($visits))
            {
            ?>
            <div style="background-color:#FFFFFF;color:black;padding:5px;">Заходы с других сайтов:</div>
            <table cellpadding="0" cellspacing="0" width="100%">
                <tr class="bgdark">
                    <td style="padding-left:20px;" colspan="2" class="bgdark">Страница:</td>
                    <td>Кол-во посещений:</td>
                </tr>
                <tr class="bgwhite">
                    <td class="bgwhite" colspan="3">&nbsp;</td>
                </tr><?
                foreach ($visits as $site => $urls) {
                    if (sizeof($visits[$site]['urls']) > 1)## If many
                    {
                        echo '<tr class="bgdark"><td style="padding-left:20px;" colspan="2" class="bgdark">' . shortlink($site) . '</td><td>' . $visits[$site]['count'] . '</td></tr>';
                        foreach ($visits[$site]['urls'] as $addr => $val) {
                            echo '<tr class="bgdark"><td class="bgdark" style="padding-left:20px;" width="60px">+</td><td>' . shortlink($site . $addr, $addr) . '</td><td >' . $val . '</td></tr>';
                        }
                    } elseif (sizeof($visits[$site]['urls'])) {
                        foreach ($visits[$site]['urls'] as $addr => $val) {
                            echo '<tr class="bgdark"><td class="bgdark" style="padding-left:20px;" colspan="2">' . shortlink($site . $addr, $site . $addr) . '</td><td >' . $val . '</td></tr>';
                        }
                    } else echo '<tr class="bgdark"><td class="bgdark" style="padding-left:20px;" colspan="2">' . shortlink($site) . '</td><td>' . $visits[$site]['count'] . '</td></tr>';
                    echo '<tr class="bgwhite"><td class="bgwhite" colspan="4">&nbsp;</td></tr>';
                }


                echo '</table>';
                }
                }
                else echo 'Статистики по сайтам, с которых посещали ваш сайт, нету. Вы точно поставили код счётчика нового образца?';
                ?>
