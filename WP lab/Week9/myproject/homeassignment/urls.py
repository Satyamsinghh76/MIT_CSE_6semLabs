from django.urls import path
from . import views

urlpatterns = [
    path('', views.billing_page1, name='billing_page1'),
    path('result/', views.billing_page2, name='billing_page2'),
    path('feedback/', views.feedback_form, name='feedback_form'),
]