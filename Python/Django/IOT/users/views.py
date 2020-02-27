from django.http import HttpResponseRedirect
from django.shortcuts import render
from django.urls import reverse
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth import logout, login, authenticate

def logout_view(request):
    '''
    注销用户
    :param request:
    :return:
    '''
    logout(request)
    return HttpResponseRedirect(reverse("devices:index"))

def register(request):
    '''
    注册新用户
    :param request:
    :return:
    '''
    if request.method != "POST":
        # 显示空的注册表单
        form = UserCreationForm()
    else:
        # 处理填好的表单
        form = UserCreationForm(data=request.POST)
        # 检查数据是否有效：用户名是否包含非法字符;输入两个密码相同;用户无试图做恶意的事项
        if form.is_valid():
            # 将用户名和密码的散列值保存至数据库
            new_user = form.save()
            # 让用户自动登录，再重新定向到主页
            authenticate_user = authenticate(username=new_user.username, \
                password=request.POST['password1'])
            login(request, authenticate_user)
            return HttpResponseRedirect(reverse("devices:index"))
    context = {'form': form}
    return render(request, "users/register.html", context)