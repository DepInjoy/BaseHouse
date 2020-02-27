创建虚拟环境

```shell
python -m venv xx_env
```

激活虚拟环境

```shell
xx_env\Scripts\activate
```

停止使用虚拟环境

```shell
deactivate
```

创建新项目

```shell
django-admin startproject monitor .
```

创建数据库

```shell
python manage.py migrate
```

启动服务

```shell
python manage.py runserver
```

创建应用

```shell
python manage.py startapp devices
```

​	应用的目录结构

​	- models.py	定义应用程序中管理的数据

修改数据库，存储模型相关的信息

```powershell
python manage.py makemigrations devices
```

启动Django shell对话

```shell
python manage.py shell
```

## 管理网站

创建超级用户

```shell
python manage.py createsuperuser
```



## 修改样式

[bootstrap](https://getbootstrap.com)

## 部署

[heroku网站](https://heroku.com/)dj-database-url包帮助Django与Heroku使用的数据库进行通信，dj-static和static3包帮助Django正确地管理静态文件，psycopg2帮助Heroku管理活动数据库

<https://toolbelt.heroku.com/>

## 创建启动进程的Procfile













