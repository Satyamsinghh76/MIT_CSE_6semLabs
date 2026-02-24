from django.shortcuts import redirect
from django.urls import path
from . import views

urlpatterns = [
    path('', views.home, name='home'),  

    path('car/', views.car_form, name='car_form'),
    path('car/result/', views.car_result, name='car_result'),

    path('first/', views.first_page, name='first_page'),
    path('second/', views.second_page, name='second_page'),

    path('grocery/', views.grocery_view, name='grocery'),
]