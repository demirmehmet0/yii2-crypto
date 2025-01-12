""" 
1-0-3-15-9-16-26-14-4-20-11-25-21-19-30-18-5-8-17-31-12-22-2-6-28-27-13-24-10-7-23-29-
1-0-5-17-28-2-29-12-31-22-27-7-20-4-25-19-11-15-24-3-10-6-16-13-18-14-23-9-30-21-8-26-
1-0-6-12-20-15-31-13-9-26-27-19-16-22-17-2-30-3-29-4-14-18-11-7-8-28-23-24-10-21-25-5-
1-0-8-28-9-16-30-14-20-4-11-21-15-19-7-31-5-3-17-18-12-25-10-6-13-27-22-24-2-26-23-29-
1-0-9-11-27-16-13-14-29-4-15-25-26-17-7-18-31-8-19-5-12-22-20-6-28-3-21-24-2-30-23-10-
1-0-11-15-9-16-13-22-10-4-28-25-26-17-7-18-8-31-19-5-12-14-20-30-27-3-21-24-6-2-23-29-
1-0-14-11-23-9-2-13-15-8-27-19-16-31-28-22-12-7-6-4-30-29-24-26-18-5-20-25-17-21-3-10-
convert hex and write to file line by line
"""
# %%
# read file
# %%
import os

def read_file(file_name):
    with open(file_name, 'r') as file:
        data = file.read()
    return data

def write_file(file_name, data):
    with open(file_name, 'w') as file:
        file.write(data)

# print(read_file("./newsboxes/5x5-46-1.txt"))

data = read_file("./5x5-46-1.txt")

index = 0
for line in data.split("\n"):
    # print(line)
    # "1-0-3-15-9-16-26-14-4-20-11-25-21-19-30-18-5-8-17-31-12-22-2-6-28-27-13-24-10-7-23-29-"
    # split by "-"
    # convert to hex
    # write to file
    hex_line = ""
    for number in line.split("-"):
        if number == "":
            continue
        hex_line += hex(int(number))[2:] + " "
    print(hex_line)
    # write_file("./newsboxes/5x5-46-1-hex.txt", hex_line)
    file = open("./newsboxes/5x5-46-1-"+str(index)+".txt", "w")
    file.write(hex_line)
    file.close()
    index += 1
# %%