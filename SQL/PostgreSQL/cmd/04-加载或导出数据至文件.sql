
-- 数据导入
	/*
		COPY table_name [ ( column_name [, ...] ) ]
    		FROM { 'filename' | PROGRAM 'command' | STDIN }
    		[ [ WITH ] ( option [, ...] ) ] 
	*/

	CREATE TABLE data(编号 int);  
	-- 从csv文件中将数据导出
	-- 注意，需要创建和源数据一致的表头名称及数据类型
	-- COPY表示从服务端寻找文件，\COPY是从客户端上寻找文件
	\COPY data FROM 'C:\二手房信息.csv' WITH CSV HEADER ENCODING 'utf8';
	
-- 数据导出
	/**
		COPY { table_name [ ( column_name [, ...] ) ] | ( query ) }
    		TO { 'filename' | PROGRAM 'command' | STDOUT }
    		[ [ WITH ] ( option [, ...] ) ] 
	*/
	-- 将数据导出为csv文件
	\COPY data TO 'E:\二手房信息清洗结果.csv' WITH CSV HEADER;