from django.urls import path
from . import views

urlpatterns = [
    path('', views.home, name='home'),   # Home is now default
    path('register/', views.register, name='register'),
    path('success/', views.success, name='success'),
    path('vote/', views.vote, name='vote'),
    path('cgpa/', views.cgpa_page1, name='cgpa_page1'),
    path('cgpa_result/', views.cgpa_page2, name='cgpa_page2'),
]