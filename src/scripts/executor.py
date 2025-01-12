import os
from sboxgen.sboxtek import runSbox

def sbox_gen():
    try:
        # check folder xml_2-4-1
        if not os.path.exists("/opt/data/xml_2-4-1"):
            os.system("mkdir -p /opt/data/xml_2-4-1")
        # runSbox('2-4-1.txt')
        xml_path = "/opt/data/xml_2-4-1"
        sbox = "2-4-1"
        runSbox(sbox, xml_path)
    except KeyError:
        print('No file')

    return 'Hello, World!'
sbox_gen()