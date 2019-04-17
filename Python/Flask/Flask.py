from flask import Flask
from flask import request
from flask import make_response
from flask import redirect
from flask import abort

from flask_script import Manager
'''
创建程序实例
Web服务器使用 WSGI协议吧接收的来自客户端的请求都在转交给该对象处理
'''
app = Flask(__name__)

'''
定义路由
Flask定义路由最简单的方式就是利用实例提供的app.route修饰器，将修饰器函数注册为路由
'''
@app.route('/')
def index():
    '''
    视图函数
    index()的返回值为响应，客户端收到的内容
    将index()作为程序根地址处理程序，这样通过web浏览器访问时，会自动执行index函数
    该index函数名可以更换为hello或者其他
    '''
    return '<h1>Hello World</h1>'

#指定动态输入，默认格式为字符串
@app.route('/next/<info>')
def next(info):
    return '<h1>Next Page is opened with %s </h1>' % info

# 指定动态输入部分的数据格式
@app.route('/user/<int:id>')
def user(id):
    return '<h1>Input id: %s </h1>' % id

# 引入请求对象处理请求
@app.route('/user/')
def getUserAgent():
    user_agent = request.headers.get("User_Agent")
    return  '<p>Your Brower is %s </p>' % user_agent

@app.route('/res/')
def getRespone():
    respone = make_response('<h1>This Document carries a cookie！</h1>')
    respone.set_cookie('answer', '42')
    return respone

@app.route('/res2/')
def getRespone2():
    return redirect('https://www.baidu.com/')

@app.route("/error/")
def getError():
    abort(200)
    return 'Error'
'''
启动服务器
确保只有执行该脚本才会启动Web服务器
如果该脚本由其他脚本引入，则不会出现运行app.run()导致启动服务器
'''
if __name__ == '__main__':
    if 0:
        # 支持命令行输入参数
        manager = Manager(app)
        manager.run()
    else:
        app.run()