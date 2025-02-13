#!/usr/bin/python3
import os

# Get query string
query = os.environ.get("QUERY_STRING", "")
params = dict(param.split("=") for param in query.split("&") if "=" in param)

# Extract "name" parameter
name = params.get("name", "Guest")
age = params.get("age", "15")

# Print CGI response (must include headers)
print("Content-Type: text/html")
print()  # Empty line separates headers from body
print(f"<html><body><h1>Hello, {name}, aged {age}!</h1></body></html>")
