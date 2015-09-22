<table width="100%" border="0" cellpadding='4' cellspacing='4'>
    <tr>
        <td>
            <table border="0" cellpadding="0" cellspacing="0" class="user-menu">
                <tr>
                    <td><span style="color:white;font-weight: bold;">Меню пользователя
                            <?

                            $sql = 'select nick from users where id=? limit 1';
                            $row = bind_int_return_row($sql, $our_user_id);
                            echo $row[0];
                            $javasc = '><a style="COLOR:C8C8BF;"';
                            $sql = 'select id from sources where user_id=?';

                            $stmt = $mysqli->prepare($sql);
                            $stmt->bind_param('i', $our_user_id);
                            $stmt->execute();
                            $result = $stmt->get_result();
                            if (!$result->num_rows)
                                $spec = '<span class="smaller">&nbsp;Подсказка: Добавьте&nbsp;свой&nbsp;первый&nbsp;сайт!</span>'; else $spec = '';

                            ?>:</span></td>
                </tr>
                <tr>
                    <td <?= $javasc; ?> href="<?= COMMON_URL; ?>index.php?page=user&ac=changedata">
                        Изменить&nbsp;профиль</a></td>
                </tr>
                <tr>
                    <td <?= $javasc; ?>
                        href="<?= COMMON_URL; ?>index.php?page=reg&ac=addsite">
                        Добавить&nbsp;сайт</a><?= $spec; ?>
                    </td>
                </tr>
                <tr>
                    <td <?= $javasc; ?> href="<?= COMMON_URL; ?>index.php?page=index&ac=logout">
                        Выйти</a></td>
                </tr>
            </table>
        </td>
    </tr>
    <tr>
        <td>
            <hr>
        </td>
    </tr>
    <tr>
        <td>
            <table border="0" cellpadding="0" cellspacing="0" align="left" class="your-sites">
                <tr>
                    <td bgcolor="#3D3E46" align="left"><strong style="color:white;">Ваши сайты:</strong><br></td>
                </tr>
                <?

                $sql = 'select * from sources where user_id=?';
                $stmt = $mysqli->prepare($sql);
                $stmt->bind_param('i', $our_user_id);
                $stmt->execute();
                $result = $stmt->get_result();
                if ($result->num_rows) {
                    while ($row2 = $result->fetch_array(MYSQLI_ASSOC)) {
                        echo('
  <tr><td><table  width="100%"  border="0"
   align="center" cellpadding="0" cellspacing="0" class="sites">
  <tr><td align="center" colspan="3">
  <em><b><a href="' . masktags($row2['url']) . '">' . masktags($row2['name']) . '</a> (сегодня ' . $row2['today_hosts'] . '
   посещений)</em></b></td></tr>
 <tr><td bgcolor="#4D3E46" ><b>Сайт:</b></td>
 <td bgcolor="#5D3E46"><b>Счётчик:</b></td>
 <td bgcolor="#6D3E46"><b>Баннеры:</b></td></tr>

  <tr><td bgcolor="#4D3E46"' . $javasc . '><a style="COLOR:C8C8BF;"
  href="' . COMMON_URL . 'index.php?page=user&ac=changesitedesc&site_id=' . $row2['id'] . '">Изменить описание</a></td>
  <td bgcolor="#5D3E46"' . $javasc . ' href="' . COMMON_URL . 'index.php?page=user&ac=countercode&site_id=' . $row2['id'] . '">
  <b>Получить код счётчика</b></a></td>
  <td bgcolor="#6D3E46"' . $javasc . ' href="' . COMMON_URL . 'index.php?page=banner&ac=upload&site_id=' . $row2['id'] . '">Закачать баннер</a></td></tr>
  <tr><td>&nbsp;</td><td  bgcolor="#5D3E46"' . $javasc . ' href="' . COMMON_URL . 'index.php?page=stats&site_id=' . $row2['id'] . '">
  Cтатистика по счётчику</a></td>
  <td bgcolor="#6D3E46"' . $javasc . ' href="' . COMMON_URL . 'index.php?page=banner&ac=code&site_id=' . $row2['id'] . '">Получить код баннера</a></td></tr>
<tr><td>&nbsp;</td><td>&nbsp;</td><td  bgcolor="#6D3E46" ' . $javasc . ' href="' . COMMON_URL . 'index.php?page=banner&ac=view&site_id=' . $row2['id'] . '">
Управление банерами</a></td></tr>
</table></td></tr>
<tr><td width="100%">&nbsp;</td></tr>
  ');
                    }
                } else echo '<tr><td style="color:#fff"><b>Подсказка:</b>У вас ещё нет сайтов, зарегестрированных в системе.
 Добавить сайт вы можете <a href="' . COMMON_URL . 'index.php?page=reg&ac=addsite">здесь</a>,
  или нажав на ссылку пользовательского меню "Добавить ещё сайт".
   Это сделано для того, чтобы вы могли зарегестрировать в системе несколько сайтов
    под одного пользователя. После добавления сайта следует поставить на свой сайт картинку со счёчиком.</td></tr>';
                ?>
            </table>
        </td>
    </tr>
</table>