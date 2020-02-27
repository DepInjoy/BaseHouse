from django import forms
from .models import Topic, Entry

class TopicForm(forms.ModelForm):
    # 内嵌Meta类，确定根据哪个模型创建表单以及表单中包含哪些字段
    class Meta:
        model = Topic
        fields = ["name", "deviceId"]
        lables = {
            "name"      :   "",
            "devicesId" :   ""
        }

class EntryForm(forms.ModelForm):
    class Meta:
        model = Entry
        fields = ["description"]
        labels = {
            "description"   :   ""
        }
        widgets = {
            "description" : forms.Textarea(attrs={'cols' : 80})
        }
