<?php
$key = $_REQUEST['key'];
if($key != 'key'){
    die('403 Forbidden');
}
// 定义is_include常量，用于限制include/index.php只能通过引用访问
define('is_include',true);
include_once(getcwd().'/include/index.php');
// Debug，设置是否输出详细的错误
if($debug == true){
    error_reporting(E_ALL);
    ini_set('display_errors',1);
}
else{
    @error_reporting(0);
    @ini_set('display_errors',0);
}
header('content-type:text/html;charset=UTF-8');
$user_agent = $_SERVER['HTTP_USER_AGENT'];
if(preg_match('#v2ray#i',$user_agent)){
    $type = 'v2ray';
}
else{
    $type = $_REQUEST['type'];
}
// 旧的单个私人订阅方案
if($type == 'old'){
    $vmess_url = 'vmess://';
    die(base64_encode($vmess_url."\n"));
}
// 判断是否v2ray客户端
if($type == 'v2ray' || $type == 'v2' || preg_match('#v2ray#i',$user_agent)){
    $v2ray_data_txt = 'data/v2ray-data.txt';
    $v2ray_data_md5 = 'data/v2ray-data.md5';
    $v2ray_data_bin = 'data/v2ray-data.bin';
    $v2ray_data_subscription = 'data/v2ray-subscription.txt';
    $v2ray_data_subscription_md5 = 'data/v2ray-subscription.md5';
    if($use_v2ray_remarks == true){
        $v2ray_data_subscription_str = file_get_contents($v2ray_data_subscription);
        if(!empty($v2ray_data_subscription_str) && md5_file($v2ray_data_subscription) != file_get_contents($v2ray_data_subscription_md5)){
            $v2ray_data_subscription_list = explode("\n",$v2ray_data_subscription_str);
            foreach($v2ray_data_subscription_list as $list){
                file_put_contents($v2ray_data_txt,base64_decode(curl($list)),FILE_APPEND);
            }
            file_put_contents($v2ray_data_subscription_md5,md5_file($v2ray_data_subscription));
        }
    }
    if(md5_file($v2ray_data_txt) != file_get_contents($v2ray_data_md5)){
        $result = str_replace(array("\r\n\r\n","\r\r","\n\n"),"",file_get_contents($v2ray_data_txt));
        $encrypt_result = aesencryption(base64_encode($result),DATA_KEY);
        file_put_contents($v2ray_data_bin,$encrypt_result);
        if($delete_v2ray_txt == true){
            file_put_contents($v2ray_data_txt,'');
        }
        file_put_contents($v2ray_data_md5,md5_file($v2ray_data_txt));
    }
    echo(aesdecryption(file_get_contents($v2ray_data_bin),DATA_KEY));
}
// 判断是否ssr客户端
elseif($type == 'ssr'){
    // 咕咕咕咕
}
//判断是否clash客户端
elseif($type == 'clash'){
    // 咕咕咕咕
}
?>