#!/usr/bin/python
#-*-coding:utf-8 -*-
import tornado.web

class BaseHandler(tornado.web.RequestHandler):
    @property
    def db(self):
        return self.application.db

    def existTable(self,name):
        self.cursor = self.db.cursor()
        try:
            existed = self.cursor.excute("SHOW DATABASE %s" % name)
            self.db.commit()
            if existed:
                print ("database %s is existed",name)
                return True
            else:
                print ("database %s is not existed",name)
                return False
        except self.db.Error:
            # print("Caught error！")
            self.db.rollback()
            # return False

    def createTable(self,name):
        if self.existTable(name):
            return
class IndexHandler(BaseHandler):
    def get(self):
        self.render('index.html')

class CalculateHandler(BaseHandler):
    def post(self):
        math = self.get_argument("math")
        english = self.get_argument("english")
        chinese = self.get_argument("chinese")
        overall = 0
        if((math == "") or (english == "") or (chinese == "")):
            self.render("calcute.html",math=math,english=english,
                        chinese=chinese,overall=overall)
            return
        overall = math + chinese + english

        dataBase = "achives"
        if not self.existTable(dataBase):
            self.createTable(dataBase)
        self.db.execute('INSERT INTO achives (math,english,chinese,overall) VALUES(%s %s %s)'
                        ,math,english,chinese,overall)
        self.render("calcute.html",math=math,english=english,
                        chinese=chinese,overall=overall)

