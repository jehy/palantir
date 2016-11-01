<?
die('Old shit!');

?><h2>Загрузка баннера к пользовательскому сайту:</h2>
<a href='?page=42'>Вернуться в админ центр</a><br>
<form action='http://valar.ru/2b/cavupload.php' method='post' enctype='multipart/form-data'>
    Стандарт баннерной сети для закачиваемого баннера:<br>
    <select name="size">
        <option value='1'>88*31
        <option value='2'>100*100
        <option value='3'>468*60
    </select><br><br>
    Файл вашего баннера:<br><input type='file' name='thefile'><br><br>
    ID сайта, к которому закачиваете баннер:<br><input type='text' name='my_id'><br>
    Название баннера:<br><input type='text' name='name' value='next_time_upload_yourself!'><br><br>
    <input type='hidden' name='login' value='<?= $login; ?>'>
    <input type='hidden' name='pas' value='<?= $password; ?>'>
    <input type='hidden' name='page' value='32'>
    <input type='submit' value='Закачать' class="button">
</form>
