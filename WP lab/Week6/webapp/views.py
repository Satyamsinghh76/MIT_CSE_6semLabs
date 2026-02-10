from django.shortcuts import render

# Create your views here.

def arithmetic(request):
    result = None
    if request.method == "POST":
        a = int(request.POST.get("num1"))
        b = int(request.POST.get("num2"))
        op = request.POST.get("operation")

        if op == "add":
            result = a + b
        elif op == "sub":
            result = a - b
        elif op == "mul":
            result = a * b
        elif op == "div":
            result = a / b if b != 0 else "Cannot divide by zero"

    return render(request, "arithmetic.html", {"result": result})


def magazine(request):
    context = {}
    if request.method == "POST":
        context = {
            "title": request.POST.get("title"),
            "tagline": request.POST.get("tagline"),
            "headline": request.POST.get("headline"),
            "bgcolor": request.POST.get("bgcolor"),
            "fontcolor": request.POST.get("fontcolor"),
            "fontsize": request.POST.get("fontsize"),
            "fontfamily": request.POST.get("fontfamily"),
            "align": request.POST.get("align"),
        }
    return render(request, "magazine.html", context)

def book_home(request):
    return render(request, "book_home.html")

def book_metadata(request):
    return render(request, "book_metadata.html")

def book_reviews(request):
    return render(request, "book_reviews.html")

def book_publisher(request):
    return render(request, "book_publisher.html")

from django.shortcuts import render

from django.shortcuts import render

def message_view(request):
    context = {}
    if request.method == "POST":
        action = request.POST.get('action')
        
        if action == "display":
            # Capture inputs
            name = request.POST.get('name', '')
            msg = request.POST.get('message', '')
            
            # Pass data for the label
            context['name_display'] = name
            context['msg_display'] = msg
            
            # Formatting Logic
            context['bold'] = 'bold' if request.POST.get('bold') else ''
            context['italic'] = 'italic' if request.POST.get('italic') else ''
            context['underline'] = 'underline' if request.POST.get('underline') else ''
            context['color'] = request.POST.get('color', 'black')
            
            # Keep inputs filled in the text boxes
            context['name'] = name
            context['message'] = msg
            
        elif action == "clear":
            return render(request, 'msg_form.html', {})

    return render(request, 'msg_form.html', context)