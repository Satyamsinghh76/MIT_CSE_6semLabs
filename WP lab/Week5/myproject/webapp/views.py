from django.shortcuts import render
from datetime import date
import calendar
from calendar import HTMLCalendar

def index(request, year=date.today().year, month=date.today().month):
    # 1. Convert inputs to integers
    year = int(year)
    month = int(month)
    
    # 2. Validate the year (default to current year if out of range)
    if year < 1900 or year > 2099:
        year = date.today().year
        
    # 3. Get the month name (e.g., "January")
    month_name = calendar.month_name[month]
    
    # 4. Create the page title
    title = "MyClub Event Calendar - %s %s" % (month_name, year)
    
    # 5. Generate the Calendar HTML
    # formatmonth returns an HTML table string representing the month
    cal = HTMLCalendar().formatmonth(year, month)
    
    # 6. Return the rendered template
    # We pass the 'title' and 'cal' variables to the template via the context dictionary
    return render(request, 'base.html', {'title': title, 'cal': cal})

def student_form(request):
    """View to render the Student Details Lab Exercise."""
    return render(request, 'student_form.html')
# ... keep existing index and student_form views ...

def promotion_check(request):
    """View to render the Employee Promotion Eligibility form."""
    return render(request, 'promotion.html')
def captcha_ex(request):
    """View to render the Captcha Exercise."""
    return render(request, 'captcha.html')