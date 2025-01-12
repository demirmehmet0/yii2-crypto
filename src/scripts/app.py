from fastapi import FastAPI, File, UploadFile, Form, Request
import os
from sboxgen.sboxtek import runSbox
import subprocess
import json
import csv

# app = Flask(__name__)
app = FastAPI()


# set 0.0.0.0 to make it accessible from outside the container


@app.post('/')
def hello():  # put application's code here
    return 'Hello, World!'


@app.post('/sbox-gen')
async def sbox_gen(file: UploadFile = File(...), max_cost: str = Form(...)):
    try:
        # ([('filename', 'Ekran Resmi 2024-04-22 14.14.22.png'), ('populationsize', 'saf'), ('mutationRatio', 'sadsa'), ('mutationRepeat', 'dasd'), ('searchoption', 'asda'), ('outputfilename', 'asd'), ('fixedpoint', 'asd')])
        filename = file.filename
        # file.save(os.path.join('/opt/data', filename))
        with open("/opt/data/" + filename + ".txt", 'wb') as f:
            f.write(file.file.read())
        data = {
            'filename': filename,
            'max_cost': max_cost
        }
        filename_without_extension = filename.split('.')[0]
        if not os.path.exists("/opt/data/xml_" + filename_without_extension):
            os.system("mkdir -p /opt/data/xml_" + filename_without_extension)
        # runSbox('2-4-1.txt')
        xml_path = "/opt/data/xml_" + filename_without_extension
        sbox = filename_without_extension
        file_path = runSbox(sbox, xml_path, data['max_cost'])
        with open(file_path, 'r') as file:
            data = file.read()

        # convert to json from csv
        csv_file = open(file_path, 'r')
        csv_reader = csv.DictReader(csv_file, delimiter=';')
        json_data = json.dumps([row for row in csv_reader])
        return json_data
        return data
    except KeyError:
        print('No file')

    return 'No file'


@app.post('/sbox-analyze')
async def sbox_gen(file: UploadFile = File(...), bit_num: str = Form(...)):
    try:
        # ([('filename', 'Ekran Resmi 2024-04-22 14.14.22.png'), ('populationsize', 'saf'), ('mutationRatio', 'sadsa'), ('mutationRepeat', 'dasd'), ('searchoption', 'asda'), ('outputfilename', 'asd'), ('fixedpoint', 'asd')])
        filename = file.filename
        # file.save(os.path.join('/opt/data', filename))
        with open("/opt/sboxanalyze/" + filename + ".txt", 'wb') as f:
            f.write(file.file.read())
        data = {
            'filename': filename,
            'bit_num': bit_num
        }
        filename_without_extension = filename.split('.')[0]
        os.system(
            "cd /opt/sboxanalyze && g++ -std=c++11 s-box-parameter-nlm-perctange.cpp -o analyze && ./analyze " + filename_without_extension + ".txt " +
            data['bit_num'])
        file_path = "/opt/sboxanalyze/" + filename_without_extension + "_results.txt"

        with open(file_path, 'r') as file:
            data = file.read()
        print(data)
        data = data.replace(";\n", "\n")
        with open(file_path, 'w') as file:
            file.write(data)
        # convert to json from csv
        csv_file = open(file_path, 'r')
        csv_reader = csv.DictReader(csv_file, delimiter=';')
        json_data = json.dumps([row for row in csv_reader])
        return json_data

    except KeyError:
        print('No file')

    return 'No file'


@app.post('/sbp')
async def sbp(file: UploadFile = File(...), max_time: str = Form(...), chosen_param: str = Form(...),
              threshold: str = Form(...), depth_limit: str = Form(...)):
    try:
        # ([('filename', 'Ekran Resmi 2024-04-22 14.14.22.png'), ('populationsize', 'saf'), ('mutationRatio', 'sadsa'), ('mutationRepeat', 'dasd'), ('searchoption', 'asda'), ('outputfilename', 'asd'), ('fixedpoint', 'asd')])
        filename = file.filename
        # file.save(os.path.join('/opt/data', filename))
        with open("/opt/SBP/matrix/" + filename + ".txt", 'wb') as f:
            f.write(file.file.read())
        data = {
            'filename': filename,
            'max_time': max_time,
            'chosen_param': chosen_param,
            'threshold': threshold,
            'depth_limit': depth_limit
        }
        filename_without_extension = filename.split('.')[0]
        os.system("cd /opt/SBP && g++ algorithm/SBPs/main.cpp && ./a.out " + filename_without_extension + " " + data[
            'max_time'] + " " + chosen_param + " " + threshold + " " + depth_limit)
        print("cd /opt/SBP && g++ algorithm/SBPs/main.cpp && ./a.out " + filename_without_extension + " " + data[
            'max_time'] + " " + chosen_param + " " + threshold + " " + depth_limit)
        file_path = "/opt/SBP/matrix/" + filename_without_extension + ".txt"

        with open(file_path, 'r') as file:
            data = file.read()
        print(data)
        with open(file_path, 'w') as file:
            file.write(data)
        return data

    except KeyError:
        print('No file')

    return 'No file'


@app.post('/db-bdkci')
async def db_bdkci(file: UploadFile = File(...), max_iteration: str = Form(...)):
    try:
        os.system("rm -r /opt/dB_BDKCI/matrix/*")
        os.system("rm -r /opt/dB_BDKCI/result_db/*")
        os.system("rm -r /opt/dB_BDKCI/run_file/*")
        # ([('filename', 'Ekran Resmi 2024-04-22 14.14.22.png'), ('populationsize', 'saf'), ('mutationRatio', 'sadsa'), ('mutationRepeat', 'dasd'), ('searchoption', 'asda'), ('outputfilename', 'asd'), ('fixedpoint', 'asd')])
        filename = file.filename
        # file.save(os.path.join('/opt/data', filename))
        with open("/opt/dB_BDKCI/matrix/" + filename + ".txt", 'wb') as f:
            f.write(file.file.read())
        data = {
            'filename': filename,
            'max_iteration': max_iteration
        }
        filename_without_extension = filename.split('.')[0]
        # python3 run_bp_xor3.py -xor4c 2.4 -xor3c 1.625 -xor2c 1.0 -iterations 10000 -path matrices -matrix GH_1.txt
        os.system(
            "cd /opt/dB_BDKCI && python3 /opt/dB_BDKCI/run_bp_xor3.py -xor4c 2.4 -xor3c 1.625 -xor2c 1.0 -iterations " +
            data['max_iteration'] + " -matrix /opt/dB_BDKCI/matrix/" + filename_without_extension + ".txt")
        print(
            "cd /opt/dB_BDKCI && python3 /opt/dB_BDKCI/run_bp_xor3.py -xor4c 2.4 -xor3c 1.625 -xor2c 1.0 -iterations " +
            data['max_iteration'] + " -matrix /opt/dB_BDKCI/matrix/" + filename_without_extension + ".txt")
        file_path = ""
        # get first file in the folder
        for file in os.listdir("/opt/dB_BDKCI/result_db/"):
            if file.endswith(".log"):
                file_path = "/opt/dB_BDKCI/result_db/" + file
                break
        print(file_path)
        with open(file_path, 'r') as file:
            data = file.read()
        print(data)
        with open(file_path, 'w') as file:
            file.write(data)

        return data

    except KeyError:
        print('No file')

    return 'No file'
