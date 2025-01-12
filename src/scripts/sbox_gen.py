import sys
import os
from sboxgen.sboxtek import runSbox
import subprocess
import json
import csv

try:
    filename = sys.argv[1]
    # ([('filename', 'Ekran Resmi 2024-04-22 14.14.22.png'), ('populationsize', 'saf'), ('mutationRatio', 'sadsa'), ('mutationRepeat', 'dasd'), ('searchoption', 'asda'), ('outputfilename', 'asd'), ('fixedpoint', 'asd')])
    max_cost = sys.argv[2]
    
    file = open( filename, 'rb')
    
    data = {
        'filename': filename,
        'max_cost': max_cost
    }
    filename_without_extension = filename.split('.')[0]
    filename_without_extension = filename_without_extension.split('/')[-1]
    if not os.path.exists("/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/data/xml_" + filename_without_extension):
        os.system("mkdir -p /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/data/xml_" + filename_without_extension)
    # runSbox('2-4-1.txt')
    xml_path = "/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/data/xml_" + filename_without_extension
    sbox = filename_without_extension
    file_path = runSbox(sbox, xml_path, data['max_cost'])
    with open(file_path, 'r') as file:
        data = file.read()

    # convert to json from csv
    csv_file = open(file_path, 'r')
    csv_reader = csv.DictReader(csv_file, delimiter=';')
    json_data = json.dumps([row for row in csv_reader])
    print(json_data)
except KeyError:
    pass
