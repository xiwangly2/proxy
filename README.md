# Xiwangly的简易聚合订阅程序

## 文件说明

```markdown
.
├── cacert.pem
├── data
│   ├── v2ray-data.bin
│   ├── v2ray-data.md5
│   ├── v2ray-data.txt
│   ├── v2ray-subscription.md5
│   └── v2ray-subscription.txt
├── include
│   ├── aes.inc
│   ├── config.inc
│   ├── curl.inc
│   ├── index.php
│   └── test.inc
├── index.php
├── index.php.bak
├── logs
└── README.md
```

cacert.pem用于curl的SSL验证

v2ray-data.bin用于存储v2ray加密后的订阅数据

v2ray-data.md5用于存储v2ray-data.txt的md5

v2ray-data.txt用于存储单个节点的订阅数据，一行一个，例如：

```markdown
vmess://……
vmess://……
```

v2ray-subscription.md5用于存储v2ray-subscription.txt的md5

v2ray-subscription.txt用于存储订阅数据，一行一个，例如：

```
https://……
http://……
```

config.inc用于保存配置信息

index.php是程序的主入口，例如你的程序存放在网站根目录的proxy目录下，则订阅地址为`http://xxx.com/proxy/index.php?key=***`或`http://xxx.com/proxy/?key=***`，key等参数由你自己定义