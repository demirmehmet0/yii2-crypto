# data = "9f509a408e1b7f4faab2a44c88c3bd39949774153045f9ba835d13d5ad61b591fe1465d78df82d0b079be5c1f5bdceea26785e81a1e93f6b34469162a8dc71259bb577123a35b22e583325cbe0d6c9f3f0cea10ac1b7bc6cde9ee0cc7b1b3abbb68165369a6e3d52018915f9b2c747e32fb0b4ef5d778bbfc1267d8bcf3b248d8090288320d13d15759047ac12962e0cfa8e93f27017132abf67486419b78dcfe3c24b7efd19b71a19beb046a5016e89cf3b9063dd85786bae78e4a276b361b62e80a8fc66765842f272dad0106f054f6a8a6c10074832faaa0b85809da9ea2981d7a2177eb24e83078a3baf806a8d3266096c119abd0d6c40c31c7b118480cf163766554619fdf7faec05b8723add5463e1ad5b62e6678ddb0b0398d05acb15d94007204b9927a973139570c43b579fbd2ddc418bc006886e2778109363ec9ae74b29ef90d1f09bbaa9989f3022bc264a62261e8a445e9382956138e6fd898f2024989b70117ee66e98383f9bb6e91c7887a0b7f71753c00d2d5448cad176bc31102286bd58b821ec897b5bfab6be348f11868ba7e84d6db25144fd312deb9086e18d515ce3bce3b94a51403c0fab6119e2375d78a9093df2931459ba827f984e7f3ade263df70478b05947b005f6244896c826ea4ae616caba8ce9dad1488cfd2284c4c0d5da80de424b25a48a9340c8510f5ad0483125f03c3bd5968a656a72c88205fad9954f3861efd075331c537ceea3da2f8c9d01f6a82c798d9b3fc7144eaab6e9c2482fc4eec01e4fb45e8d075eaafed835836d228cd8c78b7006c53aac333e407da393061dfa23cf4376e83b9cb703167341660d4bcd91f104768e88f77196cc74364e0a614cac8c888e6c3b84c36efd8f1f82df207b72510c03aa626bd15438da84fd9cf5209002e152bf4c6b2355e01e3fb851652341402cc2622160aac40ffcd6c6babe4a1e36b5fc1856b82621f3bd6ebca40894dd4fac46523bf553b07d9f36e6549f7ba3b03ac10aea5dea4b094cde297a2a07386d75eade1f63afc545b6f8c8d63bc83728eb2656337efcbfe71f21f0d9480d285a91a2ec08a53e70ca8c11441adaf3c715cb5de5d"
binaryData = ""
data = ""

with open("1RO_3INV_2DDR.txt", "r") as f:
    data = f.read()
    
print(len(data))
# data is first 10 million hex digits
data = data[:2000000]
def hexToBinary(hexData):
    binaryData = ""
    for i in hexData:
        binaryData += bin(int(i, 16))[2:].zfill(4)
    return binaryData


for i in data:
    binaryData += hexToBinary(i)
    
# print(binaryData)
binaryData5Bits = []
# print binaryData 5 bits at a time
for i in range(0, len(binaryData), 5):
    # print(binaryData[i:i+5])
    binaryData5Bits.append(binaryData[i:i+5])
if (len(binaryData5Bits[-1]) < 5):
    binaryData5Bits.pop(-1)
# print(binaryData5Bits)
def appendToFile(data, filename):
    with open(filename, "a") as f:
        f.write(data)
        
sboxes = []
other = []
def binaryToDecimal(binary):
    decimal = 0
    for i in range(len(binary)):
        decimal += int(binary[i]) * 2**(len(binary)-1-i)
    return decimal
# print(binaryData5Bits)
convertedBinaryData5Bits = []
for i in range(len(binaryData5Bits)):
    sbox = []
    dat = ""
    for j in range(len(binaryData5Bits[i])):
        dat += binaryData5Bits[i][j]
    # print(dat)
    convertedBinaryData5Bits.append(binaryToDecimal(dat))
# print(convertedBinaryData5Bits)
# exit()
say = 0
while True:
    sbox = []
    for i in range(len(convertedBinaryData5Bits)):
        if not convertedBinaryData5Bits or len(sbox) == 32:
            if len(sbox) != 32:
                for k in sbox:
                    other.append(k)
                sbox = []
            break
        if sbox.count(convertedBinaryData5Bits[0]) == 0:
            sbox.append(convertedBinaryData5Bits.pop(0))
        else:
            other.append(convertedBinaryData5Bits.pop(0))
        if len(sbox) == 32:
            appendToFile(str(sbox) + "\n", "sbox11.txt")
            break
    # print(len(sbox))
    sboxes.append(sbox)
    say += 1
    print(say)
    if not convertedBinaryData5Bits and not other:
        break
    if not convertedBinaryData5Bits:
        convertedBinaryData5Bits = other
        other = []
    if not convertedBinaryData5Bits:
        break
    
    
print(sboxes)
print(other)
availableSboxes = []
for i in range(len(sboxes)):
    if len(sboxes[i]) != 32:
        # print("Sbox ", i, " has ", len(sboxes[i]), " elements")
        pass
    else:
        availableSboxes.append(sboxes[i])

print(availableSboxes)

convertedSboxes = []
for i in range(len(availableSboxes)):
    sbox = []
    for j in range(len(availableSboxes[i])):
        sbox.append(availableSboxes[i][j])
    convertedSboxes.append(sbox)
    
print(convertedSboxes)

with open("sbox1n.txt", "w") as f:
    for i in range(len(convertedSboxes)):
        for j in range(len(convertedSboxes[i])):
            f.write(str(convertedSboxes[i][j]) + "-")
        f.write("\n")