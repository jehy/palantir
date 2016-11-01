<?
$ext = $_GET['ext'];
$id = $_GET['id'];
$allowed = array('gif', 'jpeg', 'png');
if (!in_array($ext, $allowed)) exit;
if (!is_numeric($id)) exit;
else {
    $fname = 'http://fantasy.d2.ru/4user/baners/img_' . $id . '.' . $ext;
    copy($fname, 'imgs/img_' . $id . '.' . $ext);
    /*
    $fd = fopen ($fname, "r");
    $contents = fread ($fd, 3072);// 30 KByte
    fclose ($fd);
    $fd=fopen('img_'.$id.'.'.$ext);
    fwrite($fd, $contents);
    fclose($fd);
    */
}
?>
