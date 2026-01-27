# Program to reverse the content of a file and store it in another file

# Open and read the original file
with open("input.txt", "r") as infile:
    content = infile.read()

# Reverse the content
reversed_content = content[::-1]

# Write the reversed content into a new file
with open("output.txt", "w") as outfile:
    outfile.write(reversed_content)

print("File has been reversed and saved to 'output.txt'.")
