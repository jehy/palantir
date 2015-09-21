<?if (isset($send)) {//echo $very_secret_code;
    if ($very_secret_code == 'false') {


        $text = 'From IP:
<b>' . $REMOTE_ADDR . '</b>
 and email 
    <a href="mailto: ' . $from1 . '">' . $from1 . '</a><br><br>' . $text . '<br><br>';

        $to = 'fate@jehy.ru';
        $headers = 'MIME-Version: 1.0' . "\r\n";
        $headers .= 'Content-type: text/html; charset=utf-8' . "\r\n";
        $headers .= 'From: feedback@palantir.in' . "\r\n" .
            'Reply-To: ' . $from1;
        $r = mail($to, $subject, $text, $headers);
        if ($r)
            echo 'Сообщение успешно отослано!';
        else
            echo "Не удалось отправить сообщение!<br />";
    }

} else {
    ?><br>
    Внимание, если у вас не включён javascript, ваше письмо мне не прийдёт!<br>
    Так же, если вы не укажете ваш Е-мейл, я вам НЕ СМОГУ ответить.<br>
    <br>
    Почтовый контакт:<br>
    <form action="index.php" method="post">
        <input type="hidden" name="page" value="mail">
        <script
            language="javascript">document.write('<inp' + 'ut type="hid' + 'den" name="very_se' + 'cret_code" va' + 'lue="false">');</script>
        <input type="text" name="from1" value="Ваш е-мейл" class="input_text" style="width:396"><br>
        <input type="text" name="subject" value="Тема" class="input_text" style="width:396"><br>
        <textarea wrap="virtual" name="text" class="input_text" rows="5" style="width:400">Текст
            сообщения</textarea><br>
        <INPUT name="send" type="submit" value="Отправить" class="input_text" style="width:100">
        <INPUT type="reset" value="Очистить" class="input_text" style="width:100">
    </form><? } ?>
