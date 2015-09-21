<b style="color:black; margin-right: 63px;">Навигация:</b><br>
<a class="bb" href="<?= COMMON_URL; ?>">Главная</a><br>
<a class="bb" href="<?= COMMON_URL; ?>top/Fantasy.html"><b>Каталог</b></a><br>

<?
if ($admin_user)
    echo '<a class="bb" href="' . COMMON_URL . 'admin.html">Админ.&nbspЦентр</a><br>';
if ($our_user)
    echo '<a  style="color:#2222ff" class="bb" href="' . COMMON_URL . 'user.html"><i>Мои сайты</i> </a><br>';
elseif ((!$our_user) && (!$admin_user))
    echo '<a  class="bb" href="' . COMMON_URL . 'reg.html">Регистрация</a><br><a  class="bb" href="' . COMMON_URL . 'login.html">Вход</a><br>';

?><!---->
<a class="bb" href="<?= COMMON_URL; ?>about.html">О проекте</a><br>
<a class="bb" title="Часто задаваемые вопросы" href="<?= COMMON_URL; ?>faq.html">FAQ</a><br>
<a class="bb" href="<?= COMMON_URL; ?>mail.html">Связь с авторами</a><br>
<?
if (!isset($katid))
    $katid = 13;
$sql = 'select parent from types where id=?';

$stmt = $mysqli->prepare($sql);
$stmt->bind_param('i', $katid);
$stmt->execute();
$result = $stmt->get_result();
if (!$result->num_rows)
    echo 'такого каталога нет!';
else {
    echo('<br><b style="color:black">Подкаталоги:</b><br>');
    $row = $result->fetch_row();
    $sql = 'select name_eng from `types` where id=?';
    $row = bind_int_return_row($sql, $row[0]);
    if ($katid != 13) {
        echo '<a  class="bb" href="' . COMMON_URL . 'top/' . $row[0] . '.html">.. Выше</a><br>';
    }
    $sql = 'select name,id,name_eng from types where parent=?';
    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param('i', $katid);
    $stmt->execute();
    $result = $stmt->get_result();
    if ($result->num_rows) {
        while ($row = $result->fetch_array(MYSQLI_ASSOC)) {
            echo('<a  class="bb" href="' . COMMON_URL . 'top/' . $row['name_eng'] . '.html">' . $row['name'] . '</a><br>');
        }
    }
}
?>
