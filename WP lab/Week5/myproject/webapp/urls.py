from django.urls import path, re_path
from . import views

urlpatterns = [
    path('', views.index, name='home'),  # <-- changed 'home' to 'index'
    re_path(r'^(?P<year>[0-9]{4})/(?P<month>0?[1-9]|1[0-2])/', views.index, name='index'),
    path('student/', views.student_form, name='student_form'),
    # New route for Lab Exercise 2
    path('promotion/', views.promotion_check, name='promotion_check'),
    path('captcha/', views.captcha_ex, name='captcha_ex'),
]

