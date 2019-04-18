from flask import Flask
from flask import render_template
from flask_bootstrap import Bootstrap

app = Flask(__name__)

@app.route('/')
def index():
    return '<p> Welcome! </p>'

@app.route('/buser/<name>')
def buser(name):
    return render_template('bootstrap_user.html', name = name)

# 客户端请求位置页面或路由
@app.errorhandler(404)
def page_not_found(e):
    return render_template('404.html'), 404

# 处理异常显示
@app.errorhandler(500)
def internal_server_error(e):
    return render_template('500.html'), 500

if __name__ == "__main__":
    bootstrap = Bootstrap(app)
    app.run()