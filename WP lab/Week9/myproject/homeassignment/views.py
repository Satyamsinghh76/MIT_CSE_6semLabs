from django.shortcuts import render, redirect

def billing_page1(request):
    return render(request, 'billing_page1.html')


def billing_page2(request):
    if request.method == "POST":
        brand = request.POST.get('brand')
        items = request.POST.getlist('item')
        quantity = int(request.POST.get('quantity'))

        prices = {
            "HP": {"Laptop": 50000, "Mobile": 20000},
            "Nokia": {"Laptop": 40000, "Mobile": 15000},
            "Samsung": {"Laptop": 55000, "Mobile": 25000},
            "Motorola": {"Laptop": 45000, "Mobile": 18000},
            "Apple": {"Laptop": 90000, "Mobile": 60000},
        }

        total_amount = 0
        selected_items = []

        for item in items:
            price = prices[brand][item]
            total_amount += price * quantity
            selected_items.append(f"{brand} {item}")

        context = {
            "selected_items": selected_items,
            "quantity": quantity,
            "total_amount": total_amount
        }

        return render(request, 'bill_result.html', context)

    return redirect('billing_page1')

def feedback_form(request):
    message = None

    if request.method == "POST":
        name = request.POST.get('name')
        message = f"Thanks {name} for your feedback"

    return render(request, 'feedback.html', {'message': message})