<?php
//只能通过引用访问
!defined('is_include') && die();
//遍历载入include文件夹的php和inc文件
$list = scandir('include',0);
for($i = 0;$i < count($list);$i++){
    if(preg_match('#^(index.php)$#i',$list[$i])){
    }
    elseif(preg_match('#.+\.(php|inc)$#i',$list[$i])){
        include_once(getcwd().'/include/'.$list[$i]);
    }
}
?>