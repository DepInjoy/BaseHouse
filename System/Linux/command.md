Linux常用命令
- 解/压缩文件
	- tar.gz压缩文件
	```shell
    压缩
    tar -zcvf 压缩文件名.tar.gz   <被压缩文件名>
    
    解压
    tar -zxvf 压缩文件名.tar.gz                  #解压到当前文件夹下
    tar -zxvf 压缩文件名.tar.gz -C targetDir	    #解压到targetDir文件夹下
    ```
