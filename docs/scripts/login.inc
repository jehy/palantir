<?if($ac=='login')echo'<h2>Неправильная комбинация логин/пароль!</h2>';?>
<FORM METHOD="POST" ACTION="index.php">
<input type='hidden' name='ac' value='login'>
<table align='center'>

<tr><td colspan="2"><hr></td></tr>
<tr><td>Логин:</td><td><input class= "input_text" TYPE="text" NAME="login"></td></tr>

<tr><td>Пароль:</td><td><input class= "input_text" TYPE="password" NAME="password"></td></tr>

    <tr><TD align="center"><input class="button" type="submit" value="Войти"></TD></TR>
</table>
</form>
