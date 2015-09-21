<?
$sql = 'select sources.id from sources,users where((sources.id=?)and(sources.user_id=users.id)and(users.id=?)) limit 1';


$stmt = $mysqli->prepare($sql);
$stmt->bind_param('ii', $site_id, $our_user_id);
$stmt->execute();
$result = $stmt->get_result();
if ($result->num_rows) {
    if ($ac == 'code') include('4user/banner/code.inc');
    elseif ($ac == 'view') include('4user/banner/stats.inc');
    elseif ($ac == 'upload') include('4user/banner/upload.inc');
    elseif ($ac == 'status') include('4user/banner/status.inc');
    elseif ($ac == 'clicks') include('4user/banner/refs.inc');
} else echo '<h2>Неверный идентификатор сайта!</h2>';

?>
