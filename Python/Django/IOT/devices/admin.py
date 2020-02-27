from django.contrib import admin
from devices.models import Topic, Entry

# 注册模型
admin.site.register(Topic)
admin.site.register(Entry)
