# To Do List


jiejieTop/mqttclient 项目一共引入了 1 个有漏洞的缺陷组件，以下是部分主要信息：

完整报告: https://www.oscs1024.com/cd/1530360935297032192?sign=0b20c088&report=1

缺陷组件：mbedtls@2.16.3-apache - 直接引入

- 漏洞标题：Arm Mbed TLS 安全漏洞
- 影响描述：ARM mbed TLS是英国ARM公司的一款为mbed产品提供安全通讯和加密功能的产品。Arm Mbed TLS 2.23.0之前版本存在安全漏洞，远程攻击者可以利用该漏洞恢复明文数据。
- CVE编号：CVE-2020-36423
- 国家漏洞库信息：
- 影响范围：：(∞, 2.16.9)
- 最小修复版本：2.16.9
- 组件引入路径：
- 漏洞详情：https://www.oscs1024.com/hd/MPS-2021-10705

