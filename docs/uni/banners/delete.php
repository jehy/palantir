<?
include_once('../sett.php');
$id = $_GET['id'];
if (!is_numeric($id)) die;
$check = file_get_contents($main_mirror . 'showban.php?id=' . $id);
if ($check == '0')
    foreach (glob('imgs/' . $id . '.*') as $filename)
        ;//unlink ($filename);
?>
