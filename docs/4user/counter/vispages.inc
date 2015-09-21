Постраничное посещение сайта "<strong><?= GetName($site_id); ?></strong>":<br>
(Имеются в виду страницы вашего сайта, на которые попадали уникальные посетители)<br>
<table>
    <tr class="bgdark">
        <td style="padding-left:20px;" class="bgdark">Посещённая страничка:</td>
        <td>Кол-во посещений:</td>
    </tr>
    <?
    $sql = 'select count(*) as quantity, referer from addition where site_id=? group by referer order by quantity desc,referer';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $site_id);
    $stmt->execute();
    $result = $stmt->get_result();
    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
        if (!$row['referer'])
            ;#{$show='<strong>Чёрт его знает</strong>';$link='';}
        else {
            /*
              #$link=iconv('utf8','cp1251',urldecode($row['referer']));
              $link=urldecode($row['referer']);
              if(strlen($link)>250)
                  $show=substr($link,0,250).'...';
              else
                  $show=$link;*/
            echo '<tr class="bgdark"><td style="padding-left:20px;" class="bgdark">' . shortlink($row['referer']) . '</td><td>' . $row['quantity'] . '</td></tr>';
        }
        #$link=urlencode($link);

    }
    ?>
</table>
