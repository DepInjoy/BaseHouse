- **uname: 获取当前系统的相关信息，如内核版本号、硬件架构、主机名称和操作系统类型等等。**

  - ```-a或-all:显示全部信息```

    ```shell
    uname -a
    
    Linux XXXX-virtual-machine 3.16.0-30-generic #40~14.04.1-Ubuntu SMP Thu Jan 15 17:43:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
    ```

  - ```-m或--machine:显示电脑类型。```

    ```shell
    uname -m
    
    x86_64
    ```

  - ```-s或--sysname：显示操作系统名称```

    ```shell
    uname -s
    
    Linux
    ```


- **ifconfig:用于配置和显示Linux内核中网络接口的网络参数**

  ```shell
  ifconfig
  eth0      Link encap:Ethernet  HWaddr 00:0c:29:f8:0a:77  
            inet addr:192.168.145.128  Bcast:192.168.145.255  Mask:255.255.255.0
            inet6 addr: fe80::20c:29ff:fef8:a77/64 Scope:Link
            UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
            RX packets:288 errors:0 dropped:0 overruns:0 frame:0
            TX packets:252 errors:0 dropped:0 overruns:0 carrier:0
            collisions:0 txqueuelen:1000 
            RX bytes:118280 (118.2 KB)  TX bytes:27360 (27.3 KB)
  
  lo        Link encap:Local Loopback  
            inet addr:127.0.0.1  Mask:255.0.0.0
            inet6 addr: ::1/128 Scope:Host
            UP LOOPBACK RUNNING  MTU:65536  Metric:1
            RX packets:343 errors:0 dropped:0 overruns:0 frame:0
            TX packets:343 errors:0 dropped:0 overruns:0 carrier:0
            collisions:0 txqueuelen:0 
            RX bytes:26525 (26.5 KB)  TX bytes:26525 (26.5 KB)
  ```

  其中：

  ```eth0```表示第一块网卡，```HWaddr```表示网卡物理地址，```inet addr```表示网卡的IP地址。

  ​	第三行：```UP```表示网卡开启，```RUNNING```表示网卡网线已连接，```MULTICAST```表示支持组播，```MTU```表示最大传输单元，

  ```lo```表示主机的回环地址，一般用于网络测试。