from django.shortcuts import render

# Global variables to store votes (for lab/demo purpose)
good_votes = 0
satisfactory_votes = 0
bad_votes = 0

def home(request):
    return render(request, 'home.html')
def register(request):
    if request.method == "POST":
        username = request.POST.get('username')
        password = request.POST.get('password')
        email = request.POST.get('email')
        contact = request.POST.get('contact')

        context = {
            'username': username,
            'email': email,
            'contact': contact
        }

        return render(request, 'success.html', context)

    return render(request, 'register.html')


def success(request):
    return render(request, 'success.html')


def vote(request):
    global good_votes, satisfactory_votes, bad_votes

    show_result = False
    good_percent = satisfactory_percent = bad_percent = 0

    if request.method == "POST":
        choice = request.POST.get('choice')

        if choice == "good":
            good_votes += 1
        elif choice == "satisfactory":
            satisfactory_votes += 1
        elif choice == "bad":
            bad_votes += 1

        total = good_votes + satisfactory_votes + bad_votes

        if total > 0:
            good_percent = round((good_votes / total) * 100)
            satisfactory_percent = round((satisfactory_votes / total) * 100)
            bad_percent = round((bad_votes / total) * 100)

        show_result = True

    context = {
        'show_result': show_result,
        'good_percent': good_percent,
        'satisfactory_percent': satisfactory_percent,
        'bad_percent': bad_percent
    }

    return render(request, 'vote.html', context)

def cgpa_page1(request):
    if request.method == "POST":
        name = request.POST.get('name')
        total_marks = request.POST.get('marks')

        if total_marks:
            cgpa = float(total_marks) / 50
        else:
            cgpa = 0

        # Store data in session
        request.session['name'] = name
        request.session['cgpa'] = round(cgpa, 2)

        return redirect('cgpa_page2')

    return render(request, 'cgpa_page1.html')


from django.shortcuts import redirect

def cgpa_page2(request):
    name = request.session.get('name')
    cgpa = request.session.get('cgpa')

    return render(request, 'cgpa_page2.html', {
        'name': name,
        'cgpa': cgpa
    })