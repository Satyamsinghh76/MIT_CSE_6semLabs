from django.urls import path
from . import views

urlpatterns = [
    path('arithmetic/', views.arithmetic, name='arithmetic'),
    path('magazine/', views.magazine, name='magazine'),
    path('styler/', views.message_view, name='message_styler'),
    path('book', views.book_home, name='home'),
    path('metadata/', views.book_metadata, name='metadata'),
    path('reviews/', views.book_reviews, name='reviews'),
    path('publisher/', views.book_publisher, name='publisher'),
]
