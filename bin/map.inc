<?
DEFINE('TEMPLATE', 'http://palantir.in/etc/sitemap.xsl');
function MakeUrl($url, $changefreq, $priority, $lastmod = 0)
{
    $m = '
<url>
  <loc>' . $url . '</loc>
  <priority>' . $priority . '</priority>
  <changefreq>' . $changefreq . '</changefreq>';
    if ($lastmod) $m .= '
  <lastmod>' . $lastmod . '</lastmod>';
    $m .= '
</url>';
    return $m;
}

function ReCurse($n)
{
    global $host, $today, $map, $mysqli;
    $sql = 'select * from types where parent=?';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $n);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
            $row['name'] . '<br>';
            $map .= MakeUrl($host . 'top/' . $row['name_eng'] . '.html', 'always', 0.7, $today);
            //now - for kat's pages.
            $s_num = CountPages($row['id']);
            if ($s_num > 1) {
                for ($i = 2; $i <= $s_num; $i++) {
                    $map .= MakeUrl($host . 'top/' . $row['name_eng'] . '/' . $i . '.html', 'always', 0.5, $today);
                }
            }
            ReCurse($row['id']);
        }
    }
}

function MakeSitemap()
{
    global $map, $host;
    $map = '<?xml version="1.0" encoding="UTF-8"?><?xml-stylesheet type="text/xsl" href="' . TEMPLATE . '"?>
   <!-- generated-on="' . date('F j, Y g: i a') . '" -->
   <urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">';

    $host = COMMON_URL;
    $pages = ',1,reg.html,0.1,login.html,0.1,about.html,0.9,faq.html,0.8,mail.html,0.1';
    $pages = explode(',', $pages);
    $today = 0;#date('Y-m-d');
    for ($i = 0; $i < sizeof($pages) / 2; $i++) {
        $map .= MakeUrl($host . $pages[2 * $i], 'weekly', $pages[2 * $i + 1], $today);
    }
    ReCurse(0);
    $map .= "\n" . '</urlset>';
    #echo $map;
    file_put_contents(MAPFILE, $map);
}

MakeSitemap();
?>
