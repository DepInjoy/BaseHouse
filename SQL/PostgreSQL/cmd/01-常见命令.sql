-- 查看数据库内匹配关系，包括schema，name，type，owner
	-- 列出当前数据库中所有表
	\d
	
	-- 显示表名为tableName的相关结构定义
	\d tableName;
	
	-- 显示name表的索引信息，primary key
	\d tableName_pkey;

	/**
		通配符，模糊匹配

		*		不限制字数
		?		一个字符
	**/
	\d 't*'
	\t 's?'
-- 查看帮助信息
	-- 显示所有SQL命令
	\h
	-- 显示全部命令
	\h *
	-- 显示相应命令名称的帮助说明
	\h 命令名称

-- 设置客户端的编码
	\encoding gbk
	\encoding utf8 -- 一般中文用utf8

-- 创建用户
	-- 创建用户
	CREATE USER username;
	-- 创建角色
	/** CREATE USER创建的用户默认是有登录权限的，而CREATE ROLE没有 **/
	CREATE ROLE rolename;
	-- 创建用户且设置密码为password
	
	CREATE USER username WITH PASSWORD password;
	/*
		设置用户的权限

		SUPERUSER | NOSUPERUSER → 超级用户，只有超级用户可以创建超级用户
		CREATEDB | NOCREATEDB → 创建出来的用户是否有执行 CREATE DATABASE 的权限
		CREATEROLE | NOCREATEROLE → 创建出来的用户是否有创建其他角色的权限
		LOGIN | NOLOGIN → 创建出来的用户是否有Login的权限
		INHERIT | NOINHERIT → 如果创建的一个用户拥有某一个或某几个角色，若指定INHERIT，则表示该用户自动拥有相应角色的权限
		CONNECTION LIMIT connlimit → 该用户可以使用的并发连接数量，默认值为-1，表示没有限制
	*/
	CREATE ROLE role_name WITH optional_permissions;

-- 修改用户
	-- 修改用户权限
	ALTER USER username WITH new_optional_permission;
	ALTER ROLE username WITH new_optional_permission;
	-- 修改用户的密码
	ALTER USER username WITH PASSWORD newpassword;
	ALTER ROLE u1 WITH PASSWORD newpassword;

-- 删除用户
	DROP USER username;
	-- 删除角色
	DROP ROLE rolename;

-- 创建数据库
	CREATE DATABASE dbname;
	CREATE DATABASE dbname WITH ENCODING 'utf8';

-- 修改数据库
	-- 修改列的数据类型
	ALTER TABLE table_name ALTER COLUMN column_name TYPE datatype;

-- 切换数据库/用户
	-- 切换至databasename的数据库
	\c databasename;
	-- 现有database，切换用户
	\c - username;
	-- 切换database并切换用户
	\c database username;
	

