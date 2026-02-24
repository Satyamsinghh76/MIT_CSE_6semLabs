from django.shortcuts import render, redirect
#Home
def home(request):
    return render(request, 'labExercise/home.html')

# Exercise 1
def car_form(request):
    return render(request, 'labExercise/carForm.html')


def car_result(request):
    if request.method == "POST":
        manufacturer = request.POST.get('manufacturer')
        model = request.POST.get('model')

        context = {
            'manufacturer': manufacturer,
            'model': model
        }

        return render(request, 'labExercise/carResult.html', context)

    return redirect('car_form')

# Exercise 2 (Sessions)

def first_page(request):
    return render(request, 'labExercise/firstPage.html')


def second_page(request):
    if request.method == "POST":
        name = request.POST.get('name')
        roll = request.POST.get('roll')
        subject = request.POST.get('subject')

        request.session['name'] = name
        request.session['roll'] = roll
        request.session['subject'] = subject

        return redirect('second_page')

    # Retrieve session data
    name = request.session.get('name')
    roll = request.session.get('roll')
    subject = request.session.get('subject')

    context = {
        'name': name,
        'roll': roll,
        'subject': subject
    }

    return render(request, 'labExercise/secondPage.html', context)

def grocery_view(request):

    items = {
        "Wheat": 40,
        "Jaggery": 60,
        "Dal": 80
    }

    selected_items = {}

    if request.method == "POST":
        selected = request.POST.getlist('items')

        for item in selected:
            selected_items[item] = items[item]

    context = {
        "items": items,
        "selected_items": selected_items
    }

    return render(request, "labExercise/grocery.html", context)