from django.shortcuts import render
from django.http import HttpResponseRedirect, Http404
from django.urls import reverse
from django.contrib.auth.decorators import login_required
from .models import Topic, Entry
from .forms import TopicForm, EntryForm

# 创建视图
def index(request):
    return render(request, "devices/index.html")

# 只允许已登录的用户请求该页面
@login_required         # 检查用户是否登录，只有登录才会执行下方的代码
def topics(request):
    '''
    导入数据相关联模型
    :param request: 用户请求
        user        保存了用户的相关信息
    :return:
    '''
    # 导入数据相关联模型,通过filter只允许用户访问自己的主题
    topics = Topic.objects.filter(owner=request.user).order_by("date_added")
    # 定义将要发送给模板的上下文
    context = {'topics' : topics}
    return render(request, 'devices/topics.html', context)

@login_required
def topic(request, topic_id):
    topic = Topic.objects.get(id=topic_id)
    # 确认请求主题属于当前用户
    if topic.owner != request.user:
        raise Http404
    entries = topic.entry_set.order_by("-date_added")
    context = {
        "topic"     : topic,
        "entries"   : entries
    }
    return render(request, "devices/topic.html", context)

@login_required
def add_topic(request):
    '''
    添加新主题
    :param request:
    :return:
    '''
    if request.method != "POST":
        # 未提交数据，创建一个新的表单
        form = TopicForm()
    else:
        # POST提交数据，对数据进行处理
        form = TopicForm(request.POST)
        if form.is_valid():
            new_topic = form.save(commit=False)
            # 添加主题时，将主题关联到当前用户
            new_topic.owner = request.user
            new_topic.save()
            # 用户提交数据后将其重定向到topics网页，其中reverse根据指定的URL模型确定URL
            return HttpResponseRedirect(reverse("devices:topics"))
    context = {'form' : form }
    return render(request, "devices/add_topic.html", context)

@login_required
def add_entry(request, topic_id):
    '''
    添加新的条目
    :param request:
    :return:
    '''
    topic = Topic.objects.get(id=topic_id)
    if request.method != "POST":
        form = EntryForm()
    else:
        form = EntryForm(request.POST)
        if form.is_valid():
            # commit=False使得Django创建一个Entry对象,并将其存储于new_entry，但不保存到数据库
            new_entry = form.save(commit=False)
            new_entry.topic = topic
            # 将数据保存到数据库，并将其和正确的Topic关联
            new_entry.save()
            return HttpResponseRedirect(reverse("devices:topic", args=[topic_id]))
    context = {
        "topic"     :   topic,
        "form"      :   form
    }
    return render(request, "devices/add_entry.html", context)

@login_required
def edit_entry(request, entry_id):
    '''
    编辑即有条目
    :param request:
    :param entry_id:
    :return:
    '''
    entry = Entry.objects.get(id=entry_id)
    topic = entry.topic
    if topic.owner != request.user:
        raise Http404

    if request.method != "POST":
        # 初次请求，使用当前条目的内容填充表单
        form = EntryForm(instance=entry)
    else:
        form = EntryForm(instance=entry, data=request.POST)
        if form.is_valid():
            form.save()
            return HttpResponseRedirect(reverse("devices:topic", args=[topic.id]))
    context = {
        'entry'     :   entry,
        'topic'     :   topic,
        'form'      :   form
    }
    return render(request, "devices/edit_entry.html", context)