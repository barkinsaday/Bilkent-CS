from rest_framework.decorators import api_view
from rest_framework.response import Response
from .models import User
from .serializers import UserSerializer

@api_view(['GET'])
def user_list(request):
    users = User.objects.all()
    serializer = UserSerializer(users, many=True)
    return Response(serializer.data)

def create_user(request):
    with connection.cursor() as cursor:
        cursor.execute("INSERT INTO myapp_user (name, password, languages) VALUES (%s, %s, %s)", ['Name', 'Password', 'Languages'])
    return render(request, 'create_success.html')

def list_users(request):
    with connection.cursor() as cursor:
        cursor.execute("SELECT * FROM myapp_user")
        users = cursor.fetchall()
    return render(request, 'user_list.html', {'users': users})

def update_user(request, user_id):
    with connection.cursor() as cursor:
        cursor.execute("UPDATE myapp_user SET name = %s WHERE id = %s", ['Updated Name', user_id])
    return render(request, 'update_success.html')

def delete_user(request, user_id):
    with connection.cursor() as cursor:
        cursor.execute("DELETE FROM myapp_user WHERE id = %s", [user_id])
    return render(request, 'delete_success.html')
