<?
#include('scripts/parasite.inc');
Header('Expires: Mon, 26 Jul 2002 05:00:00 GMT');
HEADER('Last-Modified: ' . gmdate('D, d M Y H:i:s') . 'GMT');
HeAdEr('Cache-Control: no-cache, must-revalidate');
hEaDeR('Pragma: no-cache');
$url = addslashes(@$_GET['url']);
if (!is_numeric($type = $_GET['type'])) exit;
if (!is_numeric($from = $_GET['from'])) exit;
if ((!is_numeric($rand = @$_GET['rand']) and ($rand))) exit;
$ip_w = ip2long($_SERVER['REMOTE_ADDR']);
$id = $from;
#$chanse=0;
include('scripts/common.inc');
$mirror = get_mirror();
//we need to detect id user hasn't uploaded banner - or is it a fictive site ID
$sql = 'SELECT sources.ban_koef FROM sources,banners WHERE ((sources.id=?)AND(banners.site_id=sources.id)AND(banners.status=1)AND(banners.type=?)) LIMIT 1';
$stmt = $mysqli->prepare($sql);
$stmt->bind_param('ii', $from, $type);
$stmt->execute();
$result = $stmt->get_result();
if ($result->num_rows) {
    $sql = 'SELECT sources.ban_koef,sources.id AS target_id,sources.url AS target_url,banners.id AS ban_id,banners.img_type
 AS ext FROM shows,sources,banners WHERE ((shows.type=?)and(banners.status=1)AND(sources.id=shows.site_id)
 AND(banners.site_id=shows.site_id)AND(banners.type=?)AND(sources.id<>?))ORDER BY RAND() LIMIT 1';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('iii', $type, $type, $from);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        $row = $result->fetch_array(MYSQLI_ASSOC);
        $k = $row['ban_koef'];
        $sql = 'update shows set site_id=? where site_id=? and type=? LIMIT 1';
        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('iii', $from, $row['target_id'], $type);
        $stmt->execute();
    } else {
        ##Very bad, neccessary banner not found. Showing our banner for now.
        $sql = 'UPDATE shows SET site_id=? WHERE site_id=? and type=? LIMIT 1';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('iii', $from, $Comission_Site_Id, $type);
        $stmt->execute();

        $sql = 'select sources.id as target_id,banners.id as ban_id,banners.img_type as ext,sources.url as target_url
    from sources,banners where ((banners.status=1)and(sources.id=?)
    and(banners.site_id=sources.id)and(banners.type=?))order by rand() limit 1';

        $stmt = $mysqli->prepare($sql);
        $stmt->bind_param('ii', $Comission_Site_Id, $type);
        $stmt->execute();
        $result = $stmt->get_result();
        $row = $result->fetch_array(MYSQLI_ASSOC);
    }

    $sql = 'insert into go values(?,?,?,?,?,?)';

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('siisss', $rand, $row[ban_id], $row[target_id], $from, $url, $ip_w);
    $stmt->execute();

    Header('Location: ' . $mirror['url'] . 'banners/imgs/img_' . $row['ban_id'] . '.' . $row['ext']);
} else  //site id for show couldn`t be selected
{
    if ($type == 1) $im = imageCreate(88, 31);
    elseif ($type == 2) $im = imageCreate(100, 100);
    elseif ($type == 3) $im = imageCreate(468, 60);
    $textcol = imagecolorallocate($im, 0, 0, 0);
    $back = imagecolorallocate($im, 111, 127, 143);
    imagefill($im, 0, 0, $back);
    Header('Content-type: image/png');
    if ($type == 1) {
        imagestring($im, 5, 1, 0, "Error-your", $textcol);
        imagestring($im, 5, 1, 8, "banner not", $textcol);
        imagestring($im, 5, 1, 18, "uploaded!", $textcol);
    } elseif ($type == 2) {
        imagestring($im, 5, 3, 00, "You have", $textcol);
        imagestring($im, 5, 1, 14, "Error in", $textcol);
        imagestring($im, 5, 3, 28, "banner code", $textcol);
        imagestring($im, 5, 3, 42, "or YOU", $textcol);
        imagestring($im, 5, 3, 56, "DIDN`T", $textcol);
        imagestring($im, 5, 1, 70, "upload YOUR", $textcol);
        imagestring($im, 5, 3, 84, "BANNER!!", $textcol);
    } elseif ($type == 3) {
        imagestring($im, 5, 3, 00, "Banner network error: you have error in code,", $textcol);
        imagestring($im, 5, 3, 20, "your site doesn`t exist in system or ", $textcol);
        imagestring($im, 5, 3, 40, "YOUR OWN BANNER ISN`T UPLOADED!!", $textcol);
    }
    imagepng($im);
}
?>
