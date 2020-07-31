<?

DEFINE('DEBUG', 1);
if (DEBUG)
    error_reporting(E_ALL ^ E_NOTICE);
else
    error_reporting(0);

$Comission_Site_Id = 2;
mb_internal_encoding('UTF-8');

function masktags($str)
{
    $str = str_replace('>', '&gt;', $str);
    $str = str_replace('<', '&lt;', $str);
    return $str;
}

function GetName($site_id)
{
    global $mysqli;
    $sql = 'select name from sources where id=? LIMIT 1';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $site_id);
    $stmt->execute();
    $result = $stmt->get_result();
    $row = $result->fetch_row();
    return $row[0];
}

function MaskLink($url)
{
    $url = str_replace(array('http://', 'https://'), '', masktags($url));
    return COMMON_URL . 'goto/' . ($url);
}


function is_utf8($string)
{

    // From http://w3.org/International/questions/qa-forms-utf-8.html
    return preg_match('%^(?:
         [\x09\x0A\x0D\x20-\x7E]            # ASCII
       | [\xC2-\xDF][\x80-\xBF]             # non-overlong 2-byte
       |  \xE0[\xA0-\xBF][\x80-\xBF]        # excluding overlongs
       | [\xE1-\xEC\xEE\xEF][\x80-\xBF]{2}  # straight 3-byte
       |  \xED[\x80-\x9F][\x80-\xBF]        # excluding surrogates
       |  \xF0[\x90-\xBF][\x80-\xBF]{2}     # planes 1-3
       | [\xF1-\xF3][\x80-\xBF]{3}          # planes 4-15
       |  \xF4[\x80-\x8F][\x80-\xBF]{2}     # plane 16
   )*$%xs', $string);

} // function is_utf8

function shortlink($url, $show = '')
{
    $url = urldecode($url);
    if (!$show)
        $show = ($url);

    if (mb_strlen($show) > 80)
        $show = mb_substr($show, 0, 80) . '[...]';
    $url = MaskLink($url);
    return '<a href="' . $url . '">' . $show . '</a>';
}

include_once('db.inc');

DEFINE('TOP', 30);
DEFINE('COMMON_URL', 'https://palantir.in/');
$max_banner_size = 20;
$news_to_show = 3;
$show_news_on_other_pages = 8;
$show_links_for_news = 8;

$network[1]['name'] = '88*31';
$network[1]['width'] = 88;
$network[1]['height'] = 31;

$network[2]['name'] = '100*100';
$network[2]['width'] = 100;
$network[2]['height'] = 100;

$network[3]['name'] = '468*60';
$network[3]['width'] = 468;
$network[3]['height'] = 60;

$networks = 3;

function error_addlog($text)
{
    global $mysqli;
    $text .= "\n\nREQUEST data:" . var_dump($_REQUEST, true) . "\n\nSERVER data:" . var_dump($_SERVER, true);
    $sql = 'INSERT INTO error_log values("",?, CONCAT(CURDATE()," ",CURTIME()), ?, ?)';
    $where = $_SERVER['PHP_SELF'] . ' (' . $_SERVER['REQUEST_URI'] . ')';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('sss', $where, $_SERVER['QUERY_STRING'], $text);
    $stmt->execute();
}


function show_error($text)
{
    echo '<div class="error">' . $text . '</div>';
}

function sql($sql)
{
    global $mysqli;
    $result = @$mysqli->query($sql);
    if ($result === FALSE) {
        $e = $mysqli->error;
        error_addlog($sql . '\n' . $e);
        if (constant('DEBUG'))
            show_error('MySQL error: ' . $e . '<br>' . htmlspecialchars($sql));
    }
    return $result;
}


function get_mirror()
{
    $sql = 'select * from mirrors order by status desc,priority desc limit 1';
    $result = sql($sql);
    $row = $result->fetch_array(MYSQLI_ASSOC);
    return $row;
}

function showlev($n)
{
    global $mysqli;
    $kats = array();
    $sql = 'select id from types where parent=?';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $n);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
            $kats = array_merge($kats, showlev($row['id']));//sources can be registered only in upper level
        }
    } else
        $kats[] = $n;
    return $kats;
}

function GetKats($kat_id, $returnString)
{
    $kats = showlev($kat_id);
    if ($returnString){
        $kats = implode(',', $kats);
        return $kats;
    }
    else
        return $kats;
}

function CountPages($kat_id)
{
    global $mysqli;
    $kats = GetKats($kat_id, 1);
    $sql = 'select count(1) from `sources` where `parent` in('.$kats.')';
    $stmt = $mysqli->prepare($sql);
    #$stmt->bind_param('s', $kats);
    $stmt->execute();
    $result = $stmt->get_result();
    $row = $result->fetch_row();
    $s_num = $row[0];
    return ceil($s_num / TOP);
}

function bind_int_return_row($sql, $var)
{
    global $mysqli;

    $stmt = $mysqli->prepare($sql);
    $r = $stmt->bind_param('i', $var);
    if (!$r)
        show_error($sql);
    $stmt->execute();
    $result = $stmt->get_result();
    $row = $result->fetch_row();
    return $row;
}

function bind_int_return_array($sql, $var)
{
    global $mysqli;

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $var);
    $stmt->execute();
    $result = $stmt->get_result();
    $row = $result->fetch_array(MYSQLI_ASSOC);
    return $row;
}

f_connect();
?>
