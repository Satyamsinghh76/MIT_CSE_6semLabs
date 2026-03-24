from django.shortcuts import render, redirect
from .models import Category, Page, Works, Lives, Institute
from .forms import CategoryForm, PageForm, WorksForm

# -------------------------
# QUESTION 1 (DIRECTORY)
# -------------------------
def directory_home(request):
    categories = Category.objects.all()
    pages = Page.objects.all()

    cat_form = CategoryForm()
    page_form = PageForm()

    return render(request, 'directory.html', {
        'categories': categories,
        'pages': pages,
        'cat_form': cat_form,
        'page_form': page_form
    })


def add_category(request):
    if request.method == 'POST':
        form = CategoryForm(request.POST)
        if form.is_valid():
            form.save()
    return redirect('directory_home')


def add_page(request):
    if request.method == 'POST':
        form = PageForm(request.POST)
        if form.is_valid():
            form.save()
    return redirect('directory_home')


# -------------------------
# QUESTION 2 (WORKS)
# -------------------------
def works_home(request):
    form = WorksForm()
    results = None
    all_data = Works.objects.all()   # 👈 ADD THIS

    if request.method == 'POST':

        if 'add' in request.POST:
            form = WorksForm(request.POST)
            if form.is_valid():
                form.save()
                return redirect('works_home')   # 👈 IMPORTANT

        if 'search' in request.POST:
            company = request.POST.get('company')

            results = []
            works = Works.objects.filter(company_name__icontains=company)

            for w in works:
                try:
                    city = Lives.objects.get(person_name=w.person_name).city
                except:
                    city = "Not Found"

                results.append({
                    'name': w.person_name,
                    'company': w.company_name,
                    'city': city
                })

    return render(request, 'works.html', {
        'form': form,
        'results': results,
        'all_data': all_data   # 👈 PASS DATA
    })
    
    
# -------------------------
# QUESTION 3 (INSTITUTES)
# -------------------------
def institutes_home(request):
    institutes = Institute.objects.all()
    return render(request, 'institutes.html', {
        'institutes': institutes
    })