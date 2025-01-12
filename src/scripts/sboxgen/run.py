# open folder newsboxes
# read all files

# %%
import os
from sboxtek import runSbox
folderPath = "./newsboxes"
index = 0
for file in os.listdir(folderPath):
    if file.endswith(".txt"):
        # remove .txt from the file name
        file = file[:-4]
        print(file)
        runSbox(file)
        print(index)
        index += 1
        
