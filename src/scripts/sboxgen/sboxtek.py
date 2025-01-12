# %%
import xml.etree.ElementTree as ET
import time

gates = ["FALSE", "AND", "A AND NOT B", "A", "NOT A AND B", "B", "XOR", "OR", 
         "NOR", "XNOR", "NOT B", "A OR NOT B", "NOT A", "NOT A OR B", "NAND", "TRUE"]
values = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768]

gate_dict = {gate: value for gate, value in zip(gates, values)}
max_cost_180nm = 820
class Gate:
    def __init__(self,id,type):
        self.inputs = []
        self.id = id
        self.type = type


class InputGate(Gate):
    def __init__(self, value,id,type):
        super().__init__(id,type)
        self.value = value

    def output(self):
        return self.value

class AndGate(Gate):
    def __init__(self, id,type):
        super().__init__(id,type)
    def output(self):
        return all(input_gate.output() for input_gate in self.inputs)

class OrGate(Gate):
    def __init__(self, id,type):
        super().__init__(id,type)
    def output(self):
        return any(input_gate.output() for input_gate in self.inputs)
class NandGate(Gate):
    def __init__(self, id,type):
        super().__init__(id,type)
    def output(self):
        return not all(input_gate.output() for input_gate in self.inputs)
class NorGate(Gate):
    def __init__(self, id,type):
        super().__init__(id,type)
    def output(self):
        return not any(input_gate.output() for input_gate in self.inputs)
class XnorGate(Gate):
    def __init__(self, id,type):
        super().__init__(id,type)
    def output(self):
        return not sum(input_gate.output() for input_gate in self.inputs) % 2
class XorGate(Gate):
    def __init__(self, id,type):
        super().__init__(id,type)
    def output(self):
        return sum(input_gate.output() for input_gate in self.inputs) % 2

class NotGate(Gate):
    def __init__(self, id,type):
        super().__init__(id,type)
    def output(self):
        return not self.inputs[0].output()
    
def build_circuit(xml_data):
    tree = ET.ElementTree(ET.fromstring(xml_data))
    gates = []
    outputs = {}
    index=0
    for gate in tree.findall('gate'):
        if gate.get('type') == 'IN':
            gates.append(InputGate(value=False,id=index,type='IN')) 
        elif gate.get('type') == 'AND':
            gates.append(AndGate(id=index,type='AND'))
        elif gate.get('type') == 'NAND':
            gates.append(NandGate(id=index,type='NAND'))
        elif gate.get('type') == 'OR':
            gates.append(OrGate(id=index,type='OR'))
        elif gate.get('type') == 'NOR':
            gates.append(NorGate(id=index,type='NOR'))
        elif gate.get('type') == 'XOR':
            gates.append(XorGate(id=index,type='XOR'))
        elif gate.get('type') == 'XNOR':
            gates.append(XnorGate(id=index,type='XNOR'))
        elif gate.get('type') == 'NOT':
            gates.append(NotGate(id=index,type='NOT'))
        index+=1

    for gate in tree.findall('gate'):
        gate_index = tree.findall('gate').index(gate)
        for input_gate in gate.findall('input'):
            input_index = int(input_gate.get('gate'))
            gates[gate_index].inputs.append(gates[input_index])

    for output in tree.findall('output'):
        bit = int(output.get('bit'))
        gate_index = int(output.get('gate'))
        outputs[bit] = gates[gate_index]

    return gates, outputs



# %%
def calculate_depth(gate, gate_depths):
    # Base case for input gates
    if isinstance(gate, InputGate) or gate in gate_depths:
        return gate_depths.get(gate, 0)

    # Calculate the depth of each input gate
    input_depths = [calculate_depth(input_gate, gate_depths) for input_gate in gate.inputs]

    # The depth of the current gate is 1 more than the maximum depth of its inputs
    current_depth = 1 + max(input_depths, default=0)
    gate_depths[gate] = current_depth
    return current_depth

def find_circuit_depth(gates, outputs):
    gate_depths = {}
    max_depth = 0
    for output in outputs.values():
        depth = calculate_depth(output, gate_depths)
        if depth > max_depth:
            max_depth = depth
    return max_depth


# %%
def calculate_circuit_cost(gates):
    # Define the costs for each gate type for each technology excluding Software and Multiplicative.
    tech_costs = {
        'UMC 180nm': {'AND': 1.33, 'OR': 1.33, 'NOT': 0.67, 'XOR': 3.00, 'XNOR': 3.00, 'NAND': 1, 'NOR': 1},
        'TSMC 65nm': {'AND': 1.50, 'OR': 1.50, 'NOT': 0.50, 'XOR': 3.00, 'XNOR': 3.00, 'NAND': 1, 'NOR': 1},
        'Depth (GEs)': {'AND': 1.50, 'OR': 1.50, 'NOT': 0.50, 'XOR': 2.00, 'XNOR': 2.00, 'NAND': 1, 'NOR': 1},
        'Depth (Soft.)': {'AND': 1.00, 'OR': 1.00, 'NOT': 1.00, 'XOR': 1.00, 'XNOR': 1.00, 'NAND': 1, 'NOR': 1},
    }

    # Initialize the cost dictionary
    total_costs = {tech: 0 for tech in tech_costs}

    # Count the number of each type of gate
    gate_counts = {'AND': 0, 'OR': 0, 'NOT': 0, 'XOR': 0, 'XNOR': 0, 'NAND': 0, 'NOR': 0}
    for gate in gates:
        if isinstance(gate, AndGate):
            gate_counts['AND'] += 1
        elif isinstance(gate, OrGate):
            gate_counts['OR'] += 1
        elif isinstance(gate, NotGate):
            gate_counts['NOT'] += 1
        elif isinstance(gate, XorGate):
            gate_counts['XOR'] += 1
        elif isinstance(gate, NandGate):
            gate_counts['NAND'] += 1
        elif isinstance(gate, NorGate):
            gate_counts['NOR'] += 1
        elif isinstance(gate, XnorGate):
            gate_counts['XNOR'] += 1
    # print(gate_counts)
        

    # Calculate the total cost for each technology
    for tech, costs in tech_costs.items():
        for gate_type, count in gate_counts.items():
            total_costs[tech] += costs[gate_type] * count

    return total_costs, gate_counts

# %%


import os


# %%


# %%
def create_cirtuit_and_calculate_cost(index, matrixName, xml_path):
    has_xml_file = False
    for file in os.listdir(xml_path):
        if file.endswith(".xml"):
            has_xml_file = True
            break
    if has_xml_file:
        pass
        # os.system("rm -r "+xml_path+"/*xml")
    os.system("cd "+xml_path+" && /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxgen/build/sboxgates /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/data/"+str(matrixName)+".txt -a 194")
    # create folder "iteration" + index and move the xml file to that folder
    # check if the folder exists

    if not os.path.exists("/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxgen/results/"+str(matrixName)+"/"+str(matrixName)+"-"+str(index)):
        os.system("mkdir -p /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/results/"+str(matrixName)+"/"+str(matrixName)+"-"+str(index))
    xml_file_name = ""

    for file in os.listdir(xml_path):
        if file.endswith(".xml") and file.startswith("5"):
            xml_file_name = file
            break

    with open(xml_path+"/"+xml_file_name, 'r') as xml_file:
        xml_data = xml_file.read()

    gates, outputs = build_circuit(xml_data)
    total_cost,gate_counts = calculate_circuit_cost(gates)
    depth = find_circuit_depth(gates, outputs)

    os.system("cd "+xml_path+" && mv *.xml /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/results/"+str(matrixName)+"/"+str(matrixName)+"-"+str(index))
    return total_cost,depth,gates,outputs,gate_counts

# %%
# open file lutResults.txt
# write the results in the file
# close the file

def runSbox(matrixName, xml_path, max_cost):
    max_cost = int(max_cost)
    has_xml_file = False
    for file in os.listdir(xml_path):
        if file.endswith(".xml"):
            has_xml_file = True
            break
    if has_xml_file:
        # os.system("rm -r "+xml_path+"/*xml")
        pass
    os.system("cd "+xml_path+" && /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxgen/build/sboxgates /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/data/"+str(matrixName)+".txt -a 194")
    file_name = '/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxgen/results/' + str(matrixName)+"Results.txt"
    if os.path.exists("/app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxgen/results/"+str(matrixName)+"Results.txt"):
        # os.system("rm /app/crypto/vendor/demirmehmet/yii2-crypto/src/scripts/sboxgen/results/"+str(matrixName)+"Results.txt")
        pass

    file = open(file_name, "w")

    file.write("Index;Cost;Depth;GateCounts;Time(ms)\n")
    total_start_time = time.time()

    for i in range(2):
        start_time = time.time()
        try:
            t,d,gates,outputs,gate_counts = create_cirtuit_and_calculate_cost(i,str(matrixName), xml_path)
            end_time = time.time()
            # print("Cost: ",t)
            # {'UMC 180nm': 50.980000000000004, 'TSMC 65nm': 52.0, 'Depth (GEs)': 39.0, 'Depth (Soft.)': 23.0}
            # if (t['UMC 180nm'] < max_cost):
            #     print("Cost is less than ",max_cost)
            file.write(str(i)+";"+str(t)+";"+str(d)+";"+str(gate_counts)+";"+str((end_time-start_time)*1000)+"\n")
        except Exception as e:
            pass
    if file.closed == False:
        total_end_time = time.time()
        file.write("Total Time: "+str((total_end_time-total_start_time)*1000)+"\n")
        file.close()
        # if d == 5:
            # break
    return file_name