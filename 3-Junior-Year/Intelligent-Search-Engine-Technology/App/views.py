from django.http import HttpRequest
from django.shortcuts import redirect, render

from django.urls import reverse
from utils.searchengine import search_by
# Create your views here.


def home(request: HttpRequest):
    if request.method == 'POST':
        word = request.POST.get('wd')
        return redirect(reverse('App:search'), kwargs={'wd': word})
    else:
        return render(request, template_name='home.html')


def search(request: HttpRequest):
    word = request.POST.get('wd')
    results = search_by('idf', word)
    print(results)
    return render(request, template_name='search.html', context={'results': results,'word':word})


def manage(requset, path):
    return redirect('/home/')
