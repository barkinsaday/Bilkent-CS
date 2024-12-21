from django.db import models

# Create your models here.
class User(models.Model):
    uName = models.CharField(max_length=100)
    password = models.CharField(max_length=100)
    # For languages, assuming a list of strings is stored
    languages = models.JSONField(blank=True, null=True)
    
    def __str__(self):
        return self.uName

print("Hello")
john = User(uName = "John Jones", password = "1234", languages = None)
print(john)

