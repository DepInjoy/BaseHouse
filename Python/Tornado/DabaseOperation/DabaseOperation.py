# import base64
# import uuid
#
# secret = base64.b64encode(uuid.uuid4().bytes + uuid.uuid4().bytes)
# print(secret)
import torndb
import tornado.web
import tornado.options
import tornado.ioloop
import tornado.options
import tornado.httpserver
from tornado.options import define,options

import os.path

from handler import IndexHandler,CalculateHandler

HANDLERS = [(r'/', IndexHandler),
            (r'/calcute',CalculateHandler),]

define("port",default=8000,help="run on given port",type=int)
define("mysql_host",default="127.0.0.1:3306",help="blog database host")
define("mysql_database",default="test",help="blog database name")
define("mysql_user",default="root",help="Blog database user")
define("mysql_password",default="",help="Blog database password")

class Application(tornado.web.Application):
    def __init__(self):
        handler = HANDLERS
        settings= dict(
            template_path = os.path.join(os.path.dirname(__file__), "templates"),
            xsrf_cookies = False,
            cookie_secret = "vCvsxYMxQPyGhhh4JxzizogDOrB8eUo+s1e6DmhQq1U=",
        )
        tornado.web.Application.__init__(self,handler,**settings)
        self.db = torndb.Connection(
            host=options.mysql_host, database=options.mysql_database,
            user=options.mysql_user, password=options.mysql_password)

if __name__ == "__main__":
    tornado.options.parse_command_line()
    httpServer = tornado.httpserver.HTTPServer(Application())
    httpServer.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()