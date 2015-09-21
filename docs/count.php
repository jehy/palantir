<?
error_reporting(E_ALL);
$id = $_REQUEST['id'];
$referer = $_REQUEST['referer'];
$img = $_REQUEST['img'];
$pic = $_REQUEST['pic'];
if (!mb_check_encoding($referer, 'UTF-8'))
    $referer = mb_convert_encoding($referer, 'UTF-8');
if ((!strpos($img, '.')) && (($img != ''))) $img .= '.png';
if ((!strpos($pic, '.')) && (($pic != ''))) $pic .= '.png';
$ref = $_SERVER['HTTP_REFERER'];
$agent = $_SERVER['HTTP_USER_AGENT'];
$ip_w = sprintf("%u", ip2long($_SERVER['REMOTE_ADDR']));

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

$set = 'update sources set ';
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

$uphits = 'today_hits=today_hits+1,total_hits=total_hits+1,cid=?';
$uphosts = 'today_hosts=today_hosts+1, total_hosts=total_hosts+1';
if (!$result->num_rows) {
    $time = date("H");
    $sql = 'INSERT INTO addition VALUES (NULL,?,?,?,?,?,?)';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('ssssii', $ip_w, $ref, $referer, $agent, $id, $time);
    $stmt->execute();
    $sql = $set . $uphits . ', ' . $uphosts;
} else $sql = $set . $uphits;
$sql = $sql . ' where id=? limit 1';
$stmt = $mysqli->prepare($sql);
$stmt->bind_param('si', $cid, $id);
$stmt->execute();

if ($mysqli->affected_rows != 1)
    $errors = $errors . "1";
if ($errors) {
    $im = imageCreate(88, 31);
    $textcol = imagecolorallocate($im, 0, 0, 0);
    $back = imagecolorallocate($im, 111, 127, 143);
    imagefill($im, 0, 0, $back);
    imagestring($im, 5, 0, 00, '  errors' . $errors, $textcol);
    imagepng($im);
} else {
    $mirror = get_mirror();
    ##################   OLD, SAVED FOR COMPATIBILITY
    if (@$_GET['pic']) {
        Header('location: ' . $mirror['url'] . 'counters/standard/' . @$pic);
    } elseif (@$_GET['img']) {
        $sql = 'select today_hosts,today_hits,total_hosts,total_hits from sources where id=? limit 1';
        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('i', $id);
        $stmt->execute();
        $result = $stmt->get_result();
        if ($result->num_rows)
            $row = $result->fetch_array(MYSQLI_ASSOC);
        Header('location: ' . $mirror['url'] . 'counters/count.php?cid=' . $img . '&today_hosts=' . $row['today_hosts'] . '&total_hosts=' . $row['total_hosts']);
    } ####################   NEW
    elseif (@$cid) {
        if (!$today_hits && !$total_hits && !$today_hosts && !$total_hosts) {
            Header('location: ' . $mirror['url'] . 'counters/standard/' . @$cid);
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
            } elseif ($today_hosts & $total_hosts)
                Header('location: ' . $mirror['url'] . 'counters/count.php?cid=' . $cid . '&today_hosts=' . $row['today_hosts'] . '&total_hosts=' . $row['total_hosts']);
        }
    }
}
?>
