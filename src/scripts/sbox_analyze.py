import sys
import os
from sboxgen.sboxtek import runSbox
import subprocess
import json
import csv

try:
    # ([('filename', 'Ekran Resmi 2024-04-22 14.14.22.png'), ('populationsize', 'saf'), ('mutationRatio', 'sadsa'), ('mutationRepeat', 'dasd'), ('searchoption', 'asda'), ('outputfilename', 'asd'), ('fixedpoint', 'asd')])
    filename = sys.argv[1]
    bit_num = sys.argv[2]
    # file.save(os.path.join('/opt/data', filename))
    file = open( filename, 'rb')
    data = {
        'filename': filename,
        'bit_num': bit_num
    }
    filename_without_extension = filename.split('.')[0]
    filename_without_extension = filename_without_extension.split('/')[-1]
    os.system(
        "cd /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxanalyze && g++ -std=c++11 s-box-parameter-nlm-perctange.cpp -o analyze && ./analyze " + filename_without_extension + ".txt " +
        data['bit_num'])
    file_path = "/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxanalyze/" + filename_without_extension + "_results.txt"

    with open(file_path, 'r') as file:
        data = file.read()

    data = data.replace(";\n", "\n")
    with open(file_path, 'w') as file:
        file.write(data)
    # convert to json from csv
    csv_file = open(file_path, 'r')
    csv_reader = csv.DictReader(csv_file, delimiter=';')
    json_data = json.dumps([row for row in csv_reader])
    # return json_data
    print(json_data)

except KeyError:
    pass