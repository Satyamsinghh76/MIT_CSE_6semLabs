from django.db import models

class Category(models.Model):
    name = models.CharField(max_length=100)
    visits = models.IntegerField(default=0)
    likes = models.IntegerField(default=0)

    def __str__(self):
        return self.name


class Page(models.Model):
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
    title = models.CharField(max_length=100)
    url = models.URLField()
    views = models.IntegerField(default=0)

    def __str__(self):
        return self.title
    
class Works(models.Model):
    person_name = models.CharField(max_length=100)
    company_name = models.CharField(max_length=100)
    salary = models.IntegerField()

    def __str__(self):
        return self.person_name


class Lives(models.Model):
    person_name = models.CharField(max_length=100)
    street = models.CharField(max_length=100)
    city = models.CharField(max_length=100)

    def __str__(self):
        return self.person_name
    
    
# QUESTION 3 (INSTITUTES)
class Institute(models.Model):
    institute_id = models.IntegerField()
    name = models.CharField(max_length=100)
    no_of_courses = models.IntegerField()

    def __str__(self):
        return self.name