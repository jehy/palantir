<a href='?page=user&site_id=<?= $site_id; ?>'>Вернуться в систему администрирования</a><br>
<?

?>
<a href="index.php?page=banner&ac=view&site_id=<?= $site_id; ?>">В систему управления банерами</a><br>
<?
$sql = 'select * from banners,sources,users where ((users.login=?)&&(users.password=?)and(users.id=sources.user_id)
and(banners.site_id=sources.id) and(banners.id=?))';


$stmt = $mysqli->prepare($sql);
$stmt->bind_param('ssi', $clogin, $cpassword, $ban_id);
$stmt->execute();
$result = $stmt->get_result();

if ($result->num_rows)
    while ($row = $result->fetch_array(MYSQLI_ASSOC)) {

        if (!@$status) $status = 0;
        if (($status > 2) || ($status < 0)) echo 'Непредусмотреный статус!';
        else {
            $sql = 'update banners set status=? where id=? limit 1';

            $stmt = $mysqli->prepare($sql);
            $stmt->bind_param('ii', $status, $ban_id);
            $stmt->execute();
            $r = 0;
            if ($mysqli->affected_rows) $r = 1;
            $date = date("Y-m-d H:m:s");
            if (($status == 0) && ($r == 1)) {
                echo '<h3>Баннер успешно удалён!</h3>';
            } elseif (($status == 1) && ($r == 1)) echo '<h3>Баннер успешно включен!</h3>';
            elseif (($status == 2) && ($r == 1)) echo '<h3>Баннер успешно отключен!</h3>';
            else echo '<h3>Ошибка в изменении статуса!</h3>';
        }
    } else echo 'Ошибка доступа!';
?>
