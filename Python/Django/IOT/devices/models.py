from django.db import models
from django.contrib.auth.models import User

'''
https://docs.djangoproject.com/en/3.0/ref/models/fields/
'''
class Topic(models.Model):
    name = models.CharField(max_length=32)
    deviceId = models.CharField(max_length=16)
    date_added = models.DateTimeField(auto_now_add=True)
    # 建立和User的外键关系，实现将数据关联到用户
    owner = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        # 模型的字符串表示
        return self.name + self.deviceId

class Entry(models.Model):
    # 外键
    topic = models.ForeignKey(Topic, on_delete=models.CASCADE, default="")
    description = models.TextField()
    date_added = models.DateTimeField(auto_now_add=True)

    class Meta:
        '''
            存储管理模型的额外信息
        '''
        verbose_name_plural = 'entries'

    def __str__(self):
        # 设置显示条目的信息
        return self.description[0:32] + "..."
