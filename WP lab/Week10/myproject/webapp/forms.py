from django import forms
from .models import Category, Page , Works

class CategoryForm(forms.ModelForm):
    class Meta:
        model = Category
        fields = ['name', 'visits', 'likes']


class PageForm(forms.ModelForm):
    class Meta:
        model = Page
        fields = ['category', 'title', 'url', 'views']
        
class WorksForm(forms.ModelForm):
    class Meta:
        model = Works
        fields = ['person_name', 'company_name', 'salary']