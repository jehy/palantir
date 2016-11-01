<?
if (!$our_user) include 'scripts/login.inc';
elseif ((!$ac) || ($ac == 'login')) include '4user/admmenu.inc';
elseif ($ac == 'changedata') include '4user/userdataupdate.inc';
elseif ($ac == 'changesitedesc') include('4user/changesitedesc.inc');
elseif ($ac = 'countercode') {
    if ($step == 2) include('4user/counter/countercode.inc');
    else include('4user/counter/viewcounters.inc');
}
?>
