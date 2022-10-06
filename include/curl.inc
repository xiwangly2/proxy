<?php
function curl($url,$curl_data = array(),$method = 'get',$ssl = null,$follow = -1,$referer = null,$header = array(),$useragent = null,$timeout = 60,$ipresolve = null,$cacertfile = null){
    //初始化curl对象
    $curl_object = curl_init();
    //curl选项
    $curl_options = array();
    //请求的URL
    $curl_options[CURLOPT_URL] = $url;
    //请求方法
    if($method == 'get' || empty($method)){
        $curl_options[CURLOPT_POST] = 0;
    }
    elseif($method == 'post' || !empty($curl_data)){
        $curl_options[CURLOPT_POST] = 1;
    }
    elseif($method == 'json'){
        $curl_options[CURLOPT_POST] = 1;
        array_push($header,'Content-Type: application/json;charset=utf-8');
    }
    elseif($method == 'xml'){
        $curl_options[CURLOPT_POST] = 1;
        array_push($header,'Content-Type: text/xml;charset=utf-8');
    }
    elseif($method == 'file'){
        $curl_options[CURLOPT_POST] = 1;
        $file_name = @basename(parse_url($curl_data)['path']);
        $file_mime = 'application/octet-stream';
        $curl_data['file'] = array(new CURLFile($url,$file_mime,$file_name));
        //$curl_data['file'][length] = filesize($url);
        array_push($header,'Content-Type: multipart/form-data;charset=utf-8');
    }
    //发送的数据
    if($method != 'get'){
        $curl_options[CURLOPT_POSTFIELDS] = $curl_data;
    }
    //将结果输出到变量而不是直接输出
    $curl_options[CURLOPT_RETURNTRANSFER] = 1;
    //跟踪重定向
    if(!empty($follow)){
        $curl_options[CURLOPT_FOLLOWLOCATION] = 1;
        //重定向自动填充referer
        $curl_options[CURLOPT_AUTOREFERER] = 1;
        //最大重定向次数
        $curl_options[CURLOPT_MAXREDIRS] = $follow;
    }
    else{
        $curl_options[CURLOPT_FOLLOWLOCATION] = 0;
    }
    //指定header
    if(!empty($header)){
        $curl_options[CURLOPT_HTTPHEADER] = $header;
    }
    //指定referer
    if(!empty($referer)){
        $curl_options[CURLOPT_REFERER] = $referer;
    }
    //指定user-agent，可能会覆盖header的user-agent
    if(!empty($useragent)){
        $curl_options[CURLOPT_USERAGENT] = $useragent;
    }
    //指定超时时间
    if(!empty($timeout)){
        $curl_options[CURLOPT_TIMEOUT] = $timeout;
    }
    //指定使用IP协议版本
    if($ipresolve == '4'){
        //只使用IPV4
        $curl_options[CURLOPT_IPRESOLVE] = CURL_IPRESOLVE_V4;
    }
    elseif($ipresolve == '6'){
        //只使用IPV6
        $curl_options[CURLOPT_IPRESOLVE] = CURL_IPRESOLVE_V6;
    }
    else{
        //IPV4或IPV6都可以使用
        $curl_options[CURLOPT_IPRESOLVE] = CURL_IPRESOLVE_WHATEVER;
    }
    //指定SSL验证
    if(empty($ssl)){
        $ssl = parse_url($url)['scheme'] == 'https' ? true : false;
    }
    if($ssl == true){
        //只信任CA颁布的证书
        $curl_options[CURLOPT_SSL_VERIFYPEER] = true;
        if(!empty($cacertfile)){
            //本地CA证书,用来验证网站的证书是否是CA颁布的
            //从http://curl.haxx.se/ca/cacert.pem可以下载此证书文件
            $curl_options[CURLOPT_CAINFO] = basename($cacertfile);
        }
        //验证域名是否匹配
        $curl_options[CURLOPT_SSL_VERIFYHOST] = 2;
    }
    else{
    //忽略证书验证,信任任何证书
        $curl_options[CURLOPT_SSL_VERIFYHOST] = false;
        $curl_options[CURLOPT_SSL_VERIFYPEER] = false;
    }
    curl_setopt_array($curl_object,$curl_options);
    $curl_return_data = curl_exec($curl_object);
    if($curl_return_data === false){
        $curl_return_data = 'Curl error: ' . curl_error($curl_object);
    }
    return $curl_return_data;
}
?>