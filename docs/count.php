<?
error_reporting(E_ALL & ~E_NOTICE);
$id = $_GET['id'];
$referer = $_GET['referer'];
$img = $_GET['img'];
$pic = $_GET['pic'];
$cid = $_GET['cid'];
$today_hits = $_GET['today_hits'];
$total_hits = $_GET['total_hits'];
$today_hosts = $_GET['today_hosts'];
$total_hosts = $_GET['total_hosts'];

if (!mb_check_encoding($referer, 'UTF-8'))
    $referer = mb_convert_encoding($referer, 'UTF-8');
if ((!strpos($img, '.')) && (($img != ''))) $img .= '.png';
if ((!strpos($pic, '.')) && (($pic != ''))) $pic .= '.png';
$ref = $_SERVER['HTTP_REFERER'];
$agent = $_SERVER['HTTP_USER_AGENT'];
$ip_w = ip2long($_SERVER['REMOTE_ADDR']);

function cnt_show_error($error)
{
    $im = imageCreate(88, 31);
    $textcol = imagecolorallocate($im, 0, 0, 0);
    $back = imagecolorallocate($im, 111, 127, 143);
    imagefill($im, 0, 0, $back);
    imagestring($im, 5, 0, 00, $error, $textcol);
    imagepng($im);
    die();
}

$errors = '';

Header('Expires: Mon, 26 Jul 2002 05:00:00 GMT');
Header('Last-Modified: ' . gmdate('D, d M Y H:i:s') . 'GMT');
Header('Cache-Control: no-cache, must-revalidate');
Header('Pragma: no-cache');

include('scripts/common.inc');
$sql = 'select 1 from addition where ((ip=?) and (site_id=?)) limit 1';
$stmt = $mysqli->prepare($sql);
$stmt->bind_param('si', $ip_w, $id);
$stmt->execute();
$result = $stmt->get_result();

if ($cid != '') {
    if (!$today_hits && !$total_hits && !$today_hosts && !$total_hosts) {
        $c = $cid . ' - static ';
    } elseif ($today_hosts & $today_hits & $total_hosts) {
        $c = $cid . ' - num(hosts) ';
    } else {
        $c = $cid . ' - num(hits) ';
    }
} elseif ($pic != '') {
    $c = $pic . ' - static ';
} elseif ($img != '') {
    $c = $img . ' - num(hosts) ';
} else {
    $c = $img . $pic . $cid;
}

$sql = 'update sources set today_hits=today_hits+1,total_hits=total_hits+1,cid=?';
$uphosts = 'today_hosts=today_hosts+1, total_hosts=total_hosts+1';
if (!$result->num_rows) {
    $time = date("H");
    $sql2 = 'INSERT INTO addition VALUES (NULL,?,?,?,?,?,?)';
    $stmt = $mysqli->prepare($sql2);
    $stmt->bind_param('isssii', $ip_w, $ref, $referer, $agent, $id, $time);
    $stmt->execute();
    $sql .= ', ' . $uphosts;
}
$sql = $sql . ' where id=? limit 1';
$stmt = $mysqli->prepare($sql);
$stmt->bind_param('si', $cid, $id);
$stmt->execute();

if ($mysqli->affected_rows != 1)
    cnt_show_error('site not found');
else {
    $mirror = get_mirror();
    ##################   OLD, SAVED FOR COMPATIBILITY
    if ($pic) {
        Header('location: ' . $mirror['url'] . 'counters/standard/' . $pic);
    } elseif ($img) {
        $sql = 'select today_hosts,today_hits,total_hosts,total_hits from sources where id=? limit 1';
        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('i', $id);
        $stmt->execute();
        $result = $stmt->get_result();
        if ($result->num_rows)
            $row = $result->fetch_array(MYSQLI_ASSOC);
        Header('location: ' . $mirror['url'] . 'counters/count.php?cid=' . $img . '&today_hosts=' . $row['today_hosts'] . '&total_hosts=' . $row['total_hosts']);
    } ####################   NEW
    elseif ($cid) {
        if (!$today_hits && !$total_hits && !$today_hosts && !$total_hosts) {
            Header('location: ' . $mirror['url'] . 'counters/standard/' . $cid);
        } else {
            $sql = 'select today_hosts,today_hits,total_hosts,total_hits from sources where id=? limit 1';
            $stmt = $mysqli->prepare($sql);
            $stmt->bind_param('i', $id);
            $stmt->execute();
            $result = $stmt->get_result();
            if ($result->num_rows)
                $row = $result->fetch_array(MYSQLI_ASSOC);
            if ($today_hosts & $today_hits & $total_hosts) {
                Header('location: ' . $mirror['url'] . 'counters/count.php?cid=' . $cid . '&today_hits=' . $row['today_hits'] . '&today_hosts=' . $row['today_hosts'] . '&total_hosts=' . $row['total_hosts']);
            } else#if ($today_hosts & $total_hosts)
                Header('location: ' . $mirror['url'] . 'counters/count.php?cid=' . $cid . '&today_hosts=' . $row['today_hosts'] . '&total_hosts=' . $row['total_hosts']);
        }
    }
}
?>lol hi
