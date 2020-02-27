from django.conf.urls import url
from . import views

urlpatterns = [
    # 主页
    url(r'^$', views.index, name="index"),
    # 显示所有主题
    url(r'^topics/$', views.topics, name='topics'),
    # 显示特定主题的详细页面
    url(r"^topic/(?P<topic_id>\d+)/$", views.topic, name='topic'),
    # 用于添加新主题的页面
    url(r'^add_topic/$', views.add_topic, name="add_topic"),
    # 用于添加新的条目,其中topic_id是匹配的Topic ID
    url(r'^add_entry/(?P<topic_id>\d+)/$', views.add_entry, name="add_entry"),
    # 条目编辑
    url(r'^edit_entry/(?P<entry_id>\d+)/$', views.edit_entry, name="edit_entry"),
]