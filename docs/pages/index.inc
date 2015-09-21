<div align="center">
    <br>
    <table border="0px" width="90%" align="center" cellpadding="4" cellspacing="4">
        <tr>
            <td style="text-align:justify">
                <h1 style="font-size: 18px;">Добро пожаловать в каталог и баннерную систему "Palantir" для фэнтези,
                    ролевых, аниме ресурсов!</h1><br>
                Теперь вы можете воспользоваться нашими сервисами. Мы предлагем бесплатные точные счётчики, поставив
                которые,
                вы автоматически будете участвовать в нашем рейтинге, и баннерную систему.
                Преимущество нашего каталога состоит в том, что он узко специализирован на фэнтезийной, ролевой и
                близкой по значению тематике - и поэтому каталогом с радостью пользуются многие любители жанра фэнтези.
                Комиссии в системе нет - так что сколько вы покажете чужих баннеров - столько же покажут и ваш. Так же
                доступна всевозможная статистика. Дерзайте=)
                <br><br>
                *Для начинающих: В книгах Джона Рональда Руэла Толкиена <b>Палантиры (Palantiri)</b> - семь магических
                видящих камней, привезённых Элендилом и его сыновьями из Нуменора. Были предположительно сделаны в Амане
                Феанором. С их помощью можно увидеть, что происходит сейчас в другом месте, события прошлого, или
                поговорить с находящимся далеко собеседником (при условии, что у него тоже есть палантир).
            </td>
        </tr>
    </table>
    <table class="tab_all" border="0px" width="90%" align="center" cellpadding="4" cellspacing="4">
        <?
        $news_to_show = 10;
        #echo"<tr><td align='center' >Архив новостей:";
        $news_to_select = $show_links_for_news * $show_news_on_other_pages;
        $sql = "select * from p_news order by `date` desc limit $news_to_show, $news_to_select";
        $result = sql($sql);
        $rows_selected = $result->num_rows;
        $links = $rows_selected / $show_news_on_other_pages;
        if (!isset($news_page)) $news_page = 1;
        ?>
        <tr>
            <td bgcolor="#3D3E46" align="center">Новости рейтинга:</td>
        </tr><?
        $sql = "select * from p_news order by `id` desc limit 0,$news_to_show";
        $result = sql($sql);
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
            $row['url_name'] = stripslashes($row['url_name']);
            $row['text'] = str_replace('&quot;', '"', stripslashes($row['text']));
            echo '
  <tr><td bgcolor="#3D3E46" style="text-align:justify">' . $row['text'] . '<div align="right">' . $row['date'] . '</div>' . '</td></tr>';
        }
        ?></table>
</div><br><br>
<?
$map_main = array();
$map_sec = array();
function ReCurse($n)
{
    global $map_main, $map_sec;
    $sql = 'select * from types where parent="' . $n . '"';
    $result = sql($sql);
    if ($result->num_rows) {
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
            $map_main[] = COMMON_URL . 'top/' . $row['name_eng'] . '.html';
            //now - for kat's pages.
            $s_num = CountPages($row['id']);
            if ($s_num > 1) {
                for ($i = 2; $i <= $s_num; $i++) {
                    $map_sec[] = COMMON_URL . 'top/' . $row['name_eng'] . '/' . $i . '.html';
                }
            }
            #$map2=
            ReCurse($row['id']);
            #if(is_array($map2)&&sizeof($map2))
            #$map=array_merge($map,$map2);
        }
    }
    #return $map;
}

$map = ReCurse(0);
echo 'Страницы: ';
for ($i = 0; $i < sizeof($map_main); $i++) {
    echo ' <a href="' . $map_main[$i] . '">' . ($i + 1) . '</a>';
}

for (; $i < 150; $i++) {
    echo ' <a href="' . $map_sec[$i] . '">' . ($i + 1) . '</a>';
}
?>