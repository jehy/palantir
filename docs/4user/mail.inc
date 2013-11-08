<?if (isset($send))
{//echo $very_secret_code;
if($very_secret_code=='false')
{
  
  
  
  
$text='From IP:
<b>'.$REMOTE_ADDR.'</b>
and email <a href="mailto: '.$from1.'">'.$from1.'</a><br><br>'.$text.'<br><br>';

// Подключаем SMTP класс для работы с почтой
include_once('smtp_class.php');

// Конфигурационный массив
/*
$SenderConfig = array(
    "SMTP_server"   =>  "smtp.jino.ru",
    "SMTP_port"     =>  "465",
    "SMTP_email"    =>  "mailer@jehy.myjino.ru",
    "SMTP_pass"     =>  "tutturu",
    "SMTP_type"     =>  "ssl"
);*/


$SenderConfig = array(
    "SMTP_server"   =>  "smtp.gmail.com",
    "SMTP_port"     =>  "465",
    "SMTP_email"    =>  "no-reply@jehy.ru",
    "SMTP_pass"     =>  "1v8WTeUBA4ac06RK6flY",
    "SMTP_type"     =>  "ssl"
);

// Email получателя/Получателей
$Receiver = 'fate@jehy.ru';
// Тема сообщения
$Subject = $subject;
// Текст сообщения (в HTML)
$Text = $text;
// Вложение в письме - адрес к файлу
$Attachment = '';

/* $mail = new KM_Mailer(сервер, порт, пользователь, пароль, тип); */
/* Тип может быть: null, tls или ssl */
$mail = new KM_Mailer($SenderConfig['SMTP_server'], $SenderConfig['SMTP_port'], $SenderConfig['SMTP_email'], $SenderConfig['SMTP_pass'], $SenderConfig['SMTP_type']);
if($mail->isLogin) {
    // Прикрепить файл


    /* $mail->send(От, Для, Тема, Текст, Заголовок = опционально) */
    $SendMail = $mail->send($SenderConfig['SMTP_email'], $Receiver, $Subject, $Text);
    
    // Очищаем список получателей
    $mail->clearRecipients();
    $mail->clearCC();
    $mail->clearBCC();
    $mail->clearAttachments();
}
 else {
    echo "Возникла ошибка во время подключения к SMTP-серверу<br />";
 }

  
  
  
  
  
  
  
  
  
  
  
  /*
$to='jehy88@gmail.com,jehy@mail.ru,gargaro@mail.ru';
$headers  = 'MIME-Version: 1.0' . "\r\n";
$headers .= 'Content-type: text/html; charset=utf-8' . "\r\n";
$from1=str_replace('"','',$from1);
$headers .= 'From: Palantir user <'.$from1.'>' . "\r\n";

//$headers='Content-Type: text/plain; charset=windows-1251'.'\r\n';
$text='From IP:
<b>'.$REMOTE_ADDR.'</b>
and email <a href="mailto: '.$from1.'">'.$from1.'</a><br><br>
'.$text.'<br><br><a href="mailto: '.$from1.'?subject=Re:'.$subject.'">Reply to subject</a>';
mail($to,$subject,$text,$headers);*/
}
echo ('<h2>Письмо отправлено</h2>');
}
else
{
?><br>
Внимание, если у вас не включён javascript, ваше письмо мне не прийдёт!<br>
Так же, если вы не укажете ваш Е-мейл, я вам НЕ СМОГУ ответить.<br>
<noscript><font color="red" size="+5">Я сказал - НЕ ПРИЙДЁТ!!!</font></noscript>
<br>
Почтовый контакт:<br>
<form action="index.php" method="post">
<input type="hidden" name="page" value="mail">
<script language="javascript">document.write('<inp'+'ut type="hid'+'den" name="very_se'+'cret_code" va'+'lue="false">');</script>
<input type="text" name="from1" value="Ваш е-мейл" class="input_text" style="width:396"><br>
<input type="text" name="subject" value="Тема" class="input_text" style="width:396"><br>
<textarea wrap="virtual" name="text" class="input_text" rows="5" style="width:400">Текст сообщения</textarea><br>
<INPUT name="send"  type="submit" value="Отправить" class="input_text" style="width:100">
<INPUT  type="reset" value="Очистить" class="input_text" style="width:100">
</form><?}?>
