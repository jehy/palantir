<?
include('scripts/common.inc');
$id = $_GET['id'];
if (is_numeric($id)) {
    $sql = 'select id,img_type from banners where id=?';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        $row = $result->fetch_array(MYSQLI_ASSOC);
        if (isset($local))
            readfile('/uni/banners/imgs/img_' . $row['id'] . '.' . $row['img_type']);
        else {
            $mirror = get_mirror();
            Header('Location: ' . $mirror['url'] . 'banners/imgs/img_' . $row['id'] . '.' . $row['img_type']);
        }
    } else echo '0';
} ?>
