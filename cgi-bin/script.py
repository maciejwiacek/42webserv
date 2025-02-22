# --- GET REQUEST ---

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

# --- POST REQUEST ---

# #!/usr/bin/python3
# import os
# import sys

# # Print the required CGI header
# print("Content-Type: text/html")
# print()  # Empty line to separate headers from the body

# # Read the POST data from stdin
# content_length = os.environ.get("CONTENT_LENGTH", "0")

# try:
#     post_length = int(content_length)
#     if post_length > 0:
#         post_data = sys.stdin.read(post_length)  # Read the actual POST data
#         params = dict(param.split("=") for param in post_data.split("&") if "=" in param)
#     else:
#         params = {}
# except ValueError:
#     params = {}

# # Extract "name" and "age" parameters
# name = params.get("name", "Guest")
# age = params.get("age", "15")

# # Print response
# print(f"<html><body><h1>Hello, {name}, aged {age}!</h1></body></html>")
