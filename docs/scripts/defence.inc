<?

function myslashes($str)
{
    if (is_array($str))
        foreach ($str as $key => $value)
            $str[$key] = myslashes($value);
    else {
        $str = str_replace("'", '&rsquo;', $str);
        $str = str_replace('%00', '', $str);
        $str = str_replace('/*', '&#47;&#42;', $str);
        $str = str_replace('#', '&#35;', $str);
        $str = str_replace('"', '&quot;', $str);
        $str = addslashes($str);
    }
    return $str;
}

$vars = array_merge($_GET,$_POST,$_COOKIE);
#unset($_GET,$_COOKIE,$_POST,$_REQUEST,$HTTP_COOKIE_VARS,$HTTP_GET_VARS,$HTTP_POST_VARS,$_FILES,$_ENV,$HTTP_ENV_VARS,$_SERVER,$HTTP_SERVER_VARS,$HTTP_POST_FILES);


if (!$page) $page = $vars['page'];
$allowed = 'QUERY_STRING,REQUEST_URI,katid,page,action,frompage,ac,site_id,step,sid,if_hacker,from,rand,url,reg,add,update,nid,id,login,password,step,session,clogin,cpassword,ifhacookie,lastv,show';
if ($vars['page'] == 'admin') {
    if ($vars['ac'] == 'types') $allowed .= ',name,name_eng,parent';
    if ($vars['ac'] == 'meta') $allowed .= ',title,keywords,description,parent,delete,import';
    if ($vars['ac'] == 'showsrc') $allowed .= ',show,action,show_id,edit';
    if ($vars['ac'] == 'news') $allowed .= ',news,nid';
}
if ($vars['page'] == 'reg') $allowed .= ',from';
if ($vars['page'] == 'reveal') $allowed .= ',reveal';
if ($vars['page'] == 'banner') $allowed .= ',ban_id';
if ($vars['page'] == 'mail') $allowed .= ',subject,text,send,from1,very_secret_code';
if ($vars['page'] == 'user') {
    if (($vars['ac'] == 'countercode') && ($vars['step'] == 2))
        $allowed .= ',today_hits,total_hits,today_hosts,total_hosts,type,cid';
    if (($vars['ac'] == 'changedata') && ($vars['step'] == 2))
        $allowed .= ',loginx,nickx,passwordx,emailx';
}
if ($vars['page'] == 'banner') {
    if ($vars['ac'] == 'status') $allowed .= ',status';
    if (($vars['ac'] == 'upload') && ($vars['step'] == 2)) $allowed .= ',size,name,fimg,fimg_type,fimg_size';
} elseif (($vars['ac'] == 'changesitedesc') && ($vars['step'] == 2)) $allowed .= ',name,url,description';


$allowed = array_unique(explode(',', $allowed));
$restricted = '';
foreach ($vars as $key => $val) {
    ;
    if (in_array($key, $allowed))
        $$key=($val);//	$$key=myslashes($val);
    else {
        $restricted .= ' $' . $key;
        unset($$key);
    }
}
#if($restricted)
#error_addlog('variables from somewhere...\n'.$restricted);

?>
