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
if __name__ == "__main__":
    bootstrap = Bootstrap(app)
    app.run()