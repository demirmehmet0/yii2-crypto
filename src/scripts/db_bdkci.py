import sys
import os
from sboxgen.sboxtek import runSbox
import subprocess
import json
import csv

try:
    os.system("rm -r /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/dB_BDKCI/matrix/*")
    os.system("rm -r /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/dB_BDKCI/result_db/*")
    os.system("rm -r /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/dB_BDKCI/run_file/*")
    # ([('filename', 'Ekran Resmi 2024-04-22 14.14.22.png'), ('populationsize', 'saf'), ('mutationRatio', 'sadsa'), ('mutationRepeat', 'dasd'), ('searchoption', 'asda'), ('outputfilename', 'asd'), ('fixedpoint', 'asd')])
    filename = sys.argv[1]
    max_iteration = sys.argv[2]

    # file.save(os.path.join('/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/data', filename))
    
    data = {
        'filename': filename,
        'max_iteration': max_iteration
    }
    filename_without_extension = filename.split('.')[0]
    # python3 run_bp_xor3.py -xor4c 2.4 -xor3c 1.625 -xor2c 1.0 -iterations 10000 -path matrices -matrix GH_1.txt
    os.system(
        "cd /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/dB_BDKCI && python3 /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/dB_BDKCI/run_bp_xor3.py -xor4c 2.4 -xor3c 1.625 -xor2c 1.0 -iterations " +
        data['max_iteration'] + " -matrix " + filename_without_extension + ".txt")
    file_path = ""
    # get first file in the folder
    for file in os.listdir("/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/dB_BDKCI/result_db/"):
        if file.endswith(".log"):
            file_path = "/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/dB_BDKCI/result_db/" + file
            break

    with open(file_path, 'r') as file:
        data = file.read()
    print(data)
    """ with open(file_path, 'w') as file:
        file.write(data) """


except KeyError:
    print('No file')