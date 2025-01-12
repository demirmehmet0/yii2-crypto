#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <cstdint>
#include <climits>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cmath> 

using namespace std;

// public static readonly Dictionary<char, string> hexCharacterToBinary = new Dictionary<char, string> {
std::unordered_map<char, std::string> hexCharacterToBinary;
// public static readonly Dictionary<int, char> decimalToHexCharacter = new Dictionary<int, char> {
std::unordered_map<int, char> decimalToHexCharacter;
// public static readonly Dictionary<char, int> hexCharacterToDecimal = new Dictionary<char, int> {
std::unordered_map<char, int> hexCharacterToDecimal;
// public static readonly Dictionary<char, int> hexCharacterToAscii = new Dictionary<char, int> {
std::unordered_map<char, int> hexCharacterToAscii;
// public static readonly Dictionary<int, string> hexCharacterToBinary_5bit = new Dictionary<int, string> {
std::unordered_map<int, std::string> hexCharacterToBinary_5bit;
std::vector<std::vector<int>> Moebius = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}};
std::vector<int> coefficients_5_bit = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5};

int HammingWeight(std::string input)
{
    int wt = 0;
    for (char c : input)
    {
        if (c == '1')
        {
            wt++;
        }
    }
    return wt;
}

uint8_t LAT_dot(uint8_t a, uint8_t b)
{
    uint8_t result = 0;
    if ((a >> 7) == 1 && (b >> 7) == 1)
        result = 1;
    for (int i = 0; i < 8; i++)
        if (((a >> i) % 2) == 1 && ((b >> i) % 2) == 1)
            result ^= 1;
        else
            result ^= 0;
    return result;
}
std::vector<std::vector<signed char>> GenerateLAT(std::vector<unsigned char> input)
{
    std::vector<std::vector<signed char>> output(input.size(), std::vector<signed char>(input.size()));
    std::vector<std::vector<unsigned char>> DOT(input.size(), std::vector<unsigned char>(input.size()));
    for (unsigned char p1 = 0; p1 < input.size(); p1++)
        for (unsigned char p2 = 0; p2 < input.size(); p2++)
            DOT[p1][p2] = LAT_dot(p1, p2); // LAT_dot function should be defined
    for (int i = 0; i < input.size(); i++)
        for (int j = 0; j < input.size(); j++)
        {
            for (int k = 0; k < input.size(); k++)
                output[i][j] += static_cast<signed char>(DOT[i][k] ^ DOT[j][hexCharacterToDecimal[input[k]]]); // hexCharacterToDecimal should be defined
            output[i][j] -= static_cast<signed char>(input.size() / 2);
        }
    for (int i = 0; i < output.size(); i++)
        for (int j = 0; j < output[i].size(); j++)
            output[i][j] *= -1;
    return output;
}

std::vector<std::vector<signed char>> GenerateLAT_5bit(std::vector<unsigned char> input)
{
    std::vector<std::vector<signed char>> output(input.size(), std::vector<signed char>(input.size()));
    std::vector<std::vector<unsigned char>> DOT(input.size(), std::vector<unsigned char>(input.size()));
    for (unsigned char p1 = 0; p1 < input.size(); p1++)
        for (unsigned char p2 = 0; p2 < input.size(); p2++)
            DOT[p1][p2] = LAT_dot(p1, p2); // LAT_dot function should be defined
    for (int i = 0; i < input.size(); i++)
        for (int j = 0; j < input.size(); j++)
        {
            for (int k = 0; k < input.size(); k++)
                output[i][j] += static_cast<signed char>(DOT[i][k] ^ DOT[j][input[k]]);
            output[i][j] -= static_cast<signed char>(input.size() / 2);
        }
    for (int i = 0; i < output.size(); i++)
        for (int j = 0; j < output[i].size(); j++)
            output[i][j] *= -1;
    return output;
}
std::vector<std::vector<int>> GenerateDDT(std::vector<unsigned char> input)
{
    std::vector<std::vector<int>> output(input.size(), std::vector<int>(input.size(), 0));
    for (int p1 = 0; p1 < input.size(); p1++)
        for (int p2 = 0; p2 < input.size(); p2++)
        {
            auto xor_in = p1 ^ p2;
            auto xor_out = hexCharacterToDecimal[input[p1]] ^ hexCharacterToDecimal[input[p2]]; // BranchNumber::hexCharacterToDecimal should be defined
            output[xor_in][xor_out]++;
        }
    return output;
}

std::vector<std::vector<int>> GenerateDDT_5bit(std::vector<unsigned char> input)
{
    std::vector<std::vector<int>> output(input.size(), std::vector<int>(input.size(), 0));
    for (int p1 = 0; p1 < input.size(); p1++)
    {
        for (int p2 = 0; p2 < input.size(); p2++)
        {
            int xor_in = p1 ^ p2;
            int xor_out = input[p1] ^ input[p2];
            output[xor_in][xor_out]++;
        }
    }
    return output;
}

int FrequencyOfDifferentialUniformity(std::vector<unsigned char> perm, int maxDDT)
{
    int numberOfFrequencyInDDT = 0;
    auto check = GenerateDDT(perm); // DDT::GenerateDDT should be defined
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (!(i == 0 && j == 0) && check[i][j] == maxDDT)
            {
                numberOfFrequencyInDDT++;
            }
        }
    }
    return numberOfFrequencyInDDT;
}

int FrequencyOfDifferentialUniformity_5bit(std::vector<unsigned char> perm, int maxDDT)
{
    int numberOfFrequencyInDDT = 0;
    auto check = GenerateDDT_5bit(perm);
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (!(i == 0 && j == 0) && check[i][j] == maxDDT)
            {
                numberOfFrequencyInDDT++;
            }
        }
    }
    return numberOfFrequencyInDDT;
}

int FrequencyOfLinearity(std::vector<unsigned char> perm, int maxLAT)
{
    int numberOfFrequencyInLAT = 0;
    auto check = GenerateLAT(perm); // GenerateLAT should be defined
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (!(i == 0 && j == 0) && std::abs(2 * check[i][j]) == std::abs(2 * maxLAT))
            {
                numberOfFrequencyInLAT++;
            }
        }
    }
    return numberOfFrequencyInLAT;
}

int FrequencyOfLinearity_5bit(std::vector<unsigned char> perm, int maxLAT)
{
    int numberOfFrequencyInLAT = 0;
    auto check = GenerateLAT_5bit(perm);
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (!(i == 0 && j == 0) && std::abs(2 * check[i][j]) == std::abs(2 * maxLAT))
            {
                numberOfFrequencyInLAT++;
            }
        }
    }
    return numberOfFrequencyInLAT;
}

int MaxDDT(std::vector<unsigned char> input)
{
    int maxDDT_value = INT_MIN;
    auto DDT = GenerateDDT(input); // GenerateDDT should be defined
    for (int i = 0; i < DDT.size(); i++)
    {
        for (int j = 0; j < DDT[i].size(); j++)
        {
            if (!(i == 0 && j == 0) && DDT[i][j] > maxDDT_value)
            {
                maxDDT_value = DDT[i][j];
            }
        }
    }
    return maxDDT_value;
}

int MaxDDT_5bit(std::vector<unsigned char> input)
{
    int maxDDT_value = INT_MIN;
    auto DDT = GenerateDDT_5bit(input);
    for (int i = 0; i < DDT.size(); i++)
    {
        for (int j = 0; j < DDT[i].size(); j++)
        {
            if (!(i == 0 && j == 0) && DDT[i][j] > maxDDT_value)
            {
                maxDDT_value = DDT[i][j];
            }
        }
    }
    return maxDDT_value;
}

int MaxLAT(std::vector<unsigned char> input)
{
    int maxLAT_value = INT_MIN;
    auto LAT = GenerateLAT(input); // GenerateLAT should be defined
    for (int i = 0; i < LAT.size(); i++)
    {
        for (int j = 0; j < LAT[i].size(); j++)
        {
            if (!(i == 0 && j == 0) && std::abs(LAT[i][j]) > maxLAT_value)
            {
                maxLAT_value = LAT[i][j];
            }
        }
    }
    return maxLAT_value;
}

int MaxLAT_5bit(std::vector<unsigned char> input)
{
    int maxLAT_value = INT_MIN;
    auto LAT = GenerateLAT_5bit(input);
    for (int i = 0; i < LAT.size(); i++)
    {
        for (int j = 0; j < LAT[i].size(); j++)
        {
            if (!(i == 0 && j == 0) && std::abs(LAT[i][j]) > maxLAT_value)
            {
                maxLAT_value = LAT[i][j];
            }
        }
    }
    return maxLAT_value;
}
int LinearBranchNumber_5bit(std::vector<unsigned char> perm)
{
    int linearBranchNumberCount = INT_MAX;
    auto check = GenerateLAT_5bit(perm); // GenerateLAT_5bit function should be defined
    for (int i = 1; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (check[i][j] != 0)
            {
                std::string inputBinaryValue = hexCharacterToBinary_5bit[i];                               // hexCharacterToBinary_5bit should be defined
                std::string outputBinaryValue = hexCharacterToBinary_5bit[j];                              // hexCharacterToBinary_5bit should be defined
                int comparisionValue = HammingWeight(inputBinaryValue) + HammingWeight(outputBinaryValue); // HammingWeight function should be defined
                if (comparisionValue < linearBranchNumberCount)
                {
                    linearBranchNumberCount = comparisionValue;
                }
            }
        }
    }
    return linearBranchNumberCount;
}
int LinearBranchNumber(std::vector<unsigned char> perm)
{
    int linearBranchNumberCount = INT_MAX;
    auto check = GenerateLAT(perm); // GenerateLAT function should be defined
    for (int i = 1; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (check[i][j] != 0)
            {
                std::string inputBinaryValue = hexCharacterToBinary[decimalToHexCharacter[i]];             // hexCharacterToBinary and decimalToHexCharacter should be defined
                std::string outputBinaryValue = hexCharacterToBinary[decimalToHexCharacter[j]];            // hexCharacterToBinary and decimalToHexCharacter should be defined
                int comparisionValue = HammingWeight(inputBinaryValue) + HammingWeight(outputBinaryValue); // HammingWeight function should be defined
                if (comparisionValue < linearBranchNumberCount)
                {
                    linearBranchNumberCount = comparisionValue;
                }
            }
        }
    }
    return linearBranchNumberCount;
}

int DifferentialBranchNumber_5bit(std::vector<unsigned char> perm)
{
    int differentialBranchNumberCount = INT_MAX;
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (i != j)
            {
                int inputDecimalValue = i;
                int outputDecimalValue = j;
                int firstHammingWeight = HammingWeight(hexCharacterToBinary_5bit[inputDecimalValue ^ outputDecimalValue]); // hexCharacterToBinary_5bit and HammingWeight should be defined
                inputDecimalValue = perm[inputDecimalValue];
                outputDecimalValue = perm[outputDecimalValue];
                int secondHammingWeight = HammingWeight(hexCharacterToBinary_5bit[inputDecimalValue ^ outputDecimalValue]); // hexCharacterToBinary_5bit and HammingWeight should be defined
                int comparisionValue = firstHammingWeight + secondHammingWeight;
                if (comparisionValue < differentialBranchNumberCount)
                {
                    differentialBranchNumberCount = comparisionValue;
                }
            }
        }
    }
    return differentialBranchNumberCount;
}

int DifferentialBranchNumber(std::vector<unsigned char> perm)
{
    int differentialBranchNumberCount = INT_MAX;
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (i != j)
            {
                int inputDecimalValue = i;
                int outputDecimalValue = j;
                int firstHammingWeight = HammingWeight(hexCharacterToBinary[decimalToHexCharacter[inputDecimalValue ^ outputDecimalValue]]);  // HammingWeight, hexCharacterToBinary and decimalToHexCharacter should be defined
                inputDecimalValue = hexCharacterToDecimal[perm[inputDecimalValue]];                                                           // hexCharacterToDecimal should be defined
                outputDecimalValue = hexCharacterToDecimal[perm[outputDecimalValue]];                                                         // hexCharacterToDecimal should be defined
                int secondHammingWeight = HammingWeight(hexCharacterToBinary[decimalToHexCharacter[inputDecimalValue ^ outputDecimalValue]]); // HammingWeight, hexCharacterToBinary and decimalToHexCharacter should be defined
                int comparisionValue = firstHammingWeight + secondHammingWeight;
                if (comparisionValue < differentialBranchNumberCount)
                {
                    differentialBranchNumberCount = comparisionValue;
                }
            }
        }
    }
    return differentialBranchNumberCount;
}

std::vector<std::vector<int>> GenerateBCT(std::vector<int> input)
{
    std::vector<std::vector<int>> output(input.size(), std::vector<int>(input.size()));
    for (int p1 = 0; p1 < input.size(); p1++)
        for (int p2 = 0; p2 < input.size(); p2++)
        {
            int BCT_cell_value = 0;
            for (int i = 0; i < input.size(); i++)
            {
                auto check1 = hexCharacterToDecimal[static_cast<signed char>(input[i])] ^ p2; // hexCharacterToDecimal should be defined
                                                                                              //                cout << std::to_string(static_cast<signed char>(input[i]))[0] << endl;
                                                                                              //                cout << input[i] << endl;
                                                                                              //                cout << static_cast<unsigned char>(input[i]) << endl;
                                                                                              //                cout << hexCharacterToAscii[decimalToHexCharacter[check1]] << endl;
                auto control1 = hexCharacterToAscii[decimalToHexCharacter[check1]];           // hexCharacterToAscii and decimalToHexCharacter should be defined
                auto first = std::find(input.begin(), input.end(), control1) - input.begin();
                auto check2 = hexCharacterToDecimal[static_cast<signed char>(input[i ^ p1])] ^ p2; // hexCharacterToDecimal should be defined
                auto control2 = hexCharacterToAscii[decimalToHexCharacter[check2]];                // hexCharacterToAscii and decimalToHexCharacter should be defined
                auto second = std::find(input.begin(), input.end(), control2) - input.begin();
                auto total = first ^ second;
                if (total == p1)
                {
                    BCT_cell_value++;
                }
            }
            output[p1][p2] = BCT_cell_value;
        }
    return output;
}

std::vector<std::vector<int>> GenerateBCT_5bit(std::vector<unsigned char> input)
{
    std::vector<std::vector<int>> output(input.size(), std::vector<int>(input.size()));
    for (int p1 = 0; p1 < input.size(); p1++)
        for (int p2 = 0; p2 < input.size(); p2++)
        {
            int BCT_cell_value = 0;
            for (int i = 0; i < input.size(); i++)
            {
                auto check1 = input[i] ^ p2;
                auto first = std::find(input.begin(), input.end(), check1) - input.begin();
                auto check2 = input[i ^ p1] ^ p2;
                auto second = std::find(input.begin(), input.end(), check2) - input.begin();
                auto total = first ^ second;
                if (total == p1)
                {
                    BCT_cell_value++;
                }
            }
            output[p1][p2] = BCT_cell_value;
        }
    return output;
}

int BCT_Uniformity(std::vector<std::vector<int>> BCT)
{
    int bct_uniformity = INT_MIN;
    for (int i = 0; i < BCT.size(); i++)
    {
        for (int j = 0; j < BCT[i].size(); j++)
        {
            if (i != 0 && j != 0)
            {
                if (BCT[i][j] > bct_uniformity)
                {
                    bct_uniformity = BCT[i][j];
                }
            }
        }
    }
    return bct_uniformity;
}

std::vector<std::vector<int>> GenerateTruthTable(std::vector<unsigned char> input)
{
    int columnNumber = 4;
    std::vector<std::vector<int>> output(input.size(), std::vector<int>(columnNumber));
    for (int i = 0; i < input.size(); i++)
    {
        std::string binaryValue = hexCharacterToBinary[input[i]]; // hexCharacterToBinary should be defined
        for (int j = 0; j < binaryValue.size(); j++)
        {
            output[i][j] = binaryValue[j] - '0';
        }
    }
    return output;
}

int GenerateAlgebraicDegree(std::vector<unsigned char> input)
{
    int columnNumber = 4;
    int rowNumber = 16;
    auto truthTable = GenerateTruthTable(input); // GenerateTruthTable should be defined
    int polynomialMaxDegree = 0;
    int sBoxMinDegree = INT_MAX;
    for (int i = 0; i < columnNumber; i++)
    {
        int x_1 = truthTable[0][i] ^ truthTable[8][i];
        int x_2 = truthTable[0][i] ^ truthTable[4][i];
        int x_3 = truthTable[0][i] ^ truthTable[2][i];
        int x_4 = truthTable[0][i] ^ truthTable[1][i];
        int x_1_2 = truthTable[0][i] ^ truthTable[4][i] ^ truthTable[8][i] ^ truthTable[12][i];
        int x_1_3 = truthTable[0][i] ^ truthTable[2][i] ^ truthTable[8][i] ^ truthTable[10][i];
        int x_1_4 = truthTable[0][i] ^ truthTable[1][i] ^ truthTable[8][i] ^ truthTable[9][i];
        int x_2_3 = truthTable[0][i] ^ truthTable[2][i] ^ truthTable[4][i] ^ truthTable[6][i];
        int x_2_4 = truthTable[0][i] ^ truthTable[1][i] ^ truthTable[4][i] ^ truthTable[5][i];
        int x_3_4 = truthTable[0][i] ^ truthTable[1][i] ^ truthTable[2][i] ^ truthTable[3][i];
        int x_1_2_3 = truthTable[0][i];
        for (int j = 1; j <= 7; j++)
        {
            x_1_2_3 = x_1_2_3 ^ truthTable[2 * j][i];
        }
        int x_1_2_4 = truthTable[0][i] ^ truthTable[1][i];
        for (int j = 1; j <= 3; j++)
        {
            x_1_2_4 = x_1_2_4 ^ truthTable[4 * j][i] ^ truthTable[(4 * j) + 1][i];
        }
        int x_1_3_4 = truthTable[0][i] ^ truthTable[1][i] ^ truthTable[2][i] ^ truthTable[3][i] ^
                      truthTable[8][i] ^ truthTable[9][i] ^ truthTable[10][i] ^ truthTable[11][i];
        int x_2_3_4 = truthTable[0][i];
        for (int j = 1; j <= 7; j++)
        {
            x_2_3_4 = x_2_3_4 ^ truthTable[j][i];
        }
        int x_1_2_3_4 = truthTable[0][i];
        for (int j = 1; j <= 15; j++)
        {
            x_1_2_3_4 = x_1_2_3_4 ^ truthTable[j][i];
        }
        if (x_1_2_3_4 == 1)
        {
            polynomialMaxDegree = 4;
        }
        else if (x_2_3_4 == 1 || x_1_3_4 == 1 || x_1_2_4 == 1 || x_1_2_3 == 1)
        {
            polynomialMaxDegree = 3;
        }
        else if (x_1_2 == 1 || x_1_3 == 1 || x_1_4 == 1 || x_2_3 == 1 || x_2_4 == 1 || x_3_4 == 1)
        {
            polynomialMaxDegree = 2;
        }
        else
        {
            polynomialMaxDegree = 1;
        }
        if (polynomialMaxDegree < sBoxMinDegree)
        {
            sBoxMinDegree = polynomialMaxDegree;
        }
    }
    return sBoxMinDegree;
}

std::vector<std::vector<int>> Transpose(std::vector<std::vector<int>> a)
{
    int m = a.size();    // row
    int n = a[0].size(); // column
    std::vector<std::vector<int>> returnMatrix(n, std::vector<int>(m));

    int temp = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < m; j++)
        {
            returnMatrix[temp][j] = a[j][i];
        }
        temp++;
    }

    return returnMatrix;
}
std::vector<std::vector<int>> ConvertToMatrix(std::vector<unsigned char> sbox)
{
    std::vector<std::vector<int>> result(32, std::vector<int>(5));
    for (int i = 0; i < 32; i++)
    {
        std::bitset<5> bits(sbox[i]);
        for (int j = 0; j < 5; j++)
        {
            result[i][j] = bits[4 - j];
        }
    }
    return result;
}
std::vector<std::vector<int>> Multiply(std::vector<std::vector<int>> a, std::vector<std::vector<int>> b)
{
    int rA = a.size();
    int cA = a[0].size();
    int rB = b.size();
    int cB = b[0].size();
    int temp = 0;
    std::vector<std::vector<int>> result(rA, std::vector<int>(cB));

    for (int i = 0; i < rA; i++)
    {
        for (int j = 0; j < cB; j++)
        {
            temp = 0;
            for (int k = 0; k < cA; k++)
            {
                temp += a[i][k] * b[k][j];
            }
            result[i][j] = temp % 2;
        }
    }
    return result;
}

std::vector<int> CountArrayByModulo2(std::vector<int> arr1, std::vector<int> arr2)
{
    int dimension = arr1.size();
    std::vector<int> result(dimension);
    for (int i = 0; i < dimension; i++)
    {
        result[i] = (arr1[i] + arr2[i]) % 2;
    }
    return result;
}

int ComponentDegree(int num, std::map<int, std::vector<int>> ANF_s, int dimension)
{
    std::string binary5bit = hexCharacterToBinary_5bit[num];
    std::vector<int> totalArray(dimension);
    for (int i = 0; i < binary5bit.length(); i++)
    {
        if (binary5bit[i] == '1')
        {
            totalArray = CountArrayByModulo2(totalArray, ANF_s[i]);
        }
    }
    int degree = INT_MIN;
    for (int i = 0; i < totalArray.size(); i++)
    {
        if (totalArray[i] == 1)
        {
            if (coefficients_5_bit[i] > degree)
            {
                degree = coefficients_5_bit[i];
            }
        }
    }

    return degree;
}
int GenerateAlgebraicDegree_5bit(std::vector<unsigned char> input)
{
    std::vector<std::vector<int>> sboxtruthMatrix = ConvertToMatrix(input);
    sboxtruthMatrix = Transpose(sboxtruthMatrix);
    std::vector<std::vector<int>> result = Multiply(sboxtruthMatrix, Moebius); // Moebius should be defined
    std::map<int, std::vector<int>> ANFs;
    int SboxDegree = INT_MAX;
    for (int j = 0; j < result.size(); j++)
    {
        ANFs[j] = result[j];
    }
    for (int i = 1; i < result[0].size(); i++)
    {
        int degree = ComponentDegree(i, ANFs, result[0].size());
        if (degree < SboxDegree)
        {
            SboxDegree = degree;
        }
    }
    return SboxDegree;
}

int NumberOfBIBO_DDT(std::vector<unsigned char> perm)
{
    int numberOfBiboDdt = 0;
    auto check = GenerateDDT(perm); // DDT::GenerateDDT should be defined
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (check[i][j] != 0)
            {
                int inputHamming = HammingWeight(hexCharacterToBinary[decimalToHexCharacter[i]]);  // HammingWeight, hexCharacterToBinary, decimalToHexCharacter should be defined
                int outputHamming = HammingWeight(hexCharacterToBinary[decimalToHexCharacter[j]]); // BranchNumber::HammingWeight, BranchNumber::hexCharacterToBinary, BranchNumber::decimalToHexCharacter should be defined
                if (inputHamming == outputHamming && inputHamming == 1 && outputHamming == 1)
                {
                    numberOfBiboDdt += 1;
                }
            }
        }
    }
    return numberOfBiboDdt;
}

int NumberOfBIBO_LAT(std::vector<unsigned char> perm)
{
    int numberOfBiboLat = 0;
    auto check = GenerateLAT(perm); // GenerateLAT should be defined
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (check[i][j] != 0)
            {
                int inputHamming = HammingWeight(hexCharacterToBinary[decimalToHexCharacter[i]]);  // HammingWeight, hexCharacterToBinary, decimalToHexCharacter should be defined
                int outputHamming = HammingWeight(hexCharacterToBinary[decimalToHexCharacter[j]]); // HammingWeight, hexCharacterToBinary, decimalToHexCharacter should be defined
                if (inputHamming == outputHamming && inputHamming == 1 && outputHamming == 1)
                {
                    numberOfBiboLat += 1;
                }
            }
        }
    }
    return numberOfBiboLat;
}

int NumberOfBIBO_PATTERNS(std::vector<unsigned char> perm)
{
    return NumberOfBIBO_DDT(perm) + NumberOfBIBO_LAT(perm); // NumberOfBIBO_DDT and NumberOfBIBO_LAT should be defined
}

std::vector<unsigned char> decimalToAsciiConvert(std::vector<unsigned char> input)
{
    std::vector<unsigned char> output(input.size());
    for (int i = 0; i < input.size(); i++)
    {
        output[i] = hexCharacterToAscii[decimalToHexCharacter[input[i]]]; // hexCharacterToAscii and BranchNumber::decimalToHexCharacter should be defined
    }
    return output;
}

int DLCT_Uniformity(std::vector<std::vector<int>> DLCT)
{
    int dlct_uniformity = INT_MIN;
    for (int i = 0; i < DLCT.size(); i++)
    {
        for (int j = 0; j < DLCT[i].size(); j++)
        {
            if (std::abs(DLCT[i][j]) > dlct_uniformity)
            {
                dlct_uniformity = std::abs(DLCT[i][j]);
            }
        }
    }
    return dlct_uniformity;
}
std::vector<std::vector<int>> GenerateDLCT(std::vector<unsigned char> input)
{
    std::vector<std::vector<int>> output(input.size(), std::vector<int>(input.size()));
    for (int p1 = 0; p1 < input.size(); p1++)
    {
        for (int p2 = 0; p2 < input.size(); p2++)
        {
            int DLCT_cell_value = 0;
            int DLCT_cell_counter = 0;
            for (int i = 0; i < input.size(); i++)
            {
                unsigned char check1 = LAT_dot(p2, hexCharacterToDecimal[input[i]]);      // LAT_dot and hexCharacterToDecimal should be defined
                unsigned char check2 = LAT_dot(p2, hexCharacterToDecimal[input[i ^ p1]]); // LAT_dot and hexCharacterToDecimal should be defined
                if (check1 == check2)
                {
                    DLCT_cell_counter++;
                }
            }
            DLCT_cell_value = DLCT_cell_counter - (std::pow(2, std::log2(input.size()) - 1));
            output[p1][p2] = DLCT_cell_value;
        }
    }
    return output;
}

int FindFixedPoint_5bit(std::vector<unsigned char> perm)
{
    int fixedPointCount = 0;
    for (int i = 0; i < perm.size(); i++)
    {
        int decimalValue = perm[i];
        if (decimalValue == i)
        {
            fixedPointCount++;
        }
    }
    return fixedPointCount;
}

int FindFixedPoint(std::vector<unsigned char> perm)
{
    int fixedPointCount = 0;
    for (int i = 0; i < perm.size(); i++)
    {
        int decimalValue = hexCharacterToDecimal[perm[i]]; // hexCharacterToDecimal should be defined
        if (decimalValue == i)
        {
            fixedPointCount++;
        }
    }
    return fixedPointCount;
}

int NumberOfBIBO_DDT_5bit(std::vector<unsigned char> perm)
{
    int numberOfBiboDdt = 0;
    std::vector<std::vector<int>> check = GenerateDDT_5bit(perm);
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (check[i][j] != 0)
            {
                int inputHamming = HammingWeight(hexCharacterToBinary_5bit[i]);
                int outputHamming = HammingWeight(hexCharacterToBinary_5bit[j]);
                if (inputHamming == outputHamming && inputHamming == 1 && outputHamming == 1)
                {
                    numberOfBiboDdt += 1;
                }
            }
        }
    }

    return numberOfBiboDdt;
}

int NumberOfBIBO_LAT_5bit(std::vector<unsigned char> perm)
{
    int numberOfBiboLat = 0;
    auto check = GenerateLAT_5bit(perm);
    for (int i = 0; i < perm.size(); i++)
    {
        for (int j = 0; j < perm.size(); j++)
        {
            if (check[i][j] != 0)
            {
                int inputHamming = HammingWeight(hexCharacterToBinary_5bit[i]);
                int outputHamming = HammingWeight(hexCharacterToBinary_5bit[j]);
                if (inputHamming == outputHamming && inputHamming == 1 && outputHamming == 1)
                {
                    numberOfBiboLat += 1;
                }
            }
        }
    }

    return numberOfBiboLat;
}

int NumberOfBIBO_PATTERNS_5bit(std::vector<unsigned char> perm)
{
    return NumberOfBIBO_DDT_5bit(perm) + NumberOfBIBO_LAT_5bit(perm);
}
unsigned char LAT_dot_5bit(unsigned char a, unsigned char b)
{
    unsigned char result = 0;
    if ((a >> 15) == 1 && (b >> 15) == 1)
        result = 1;
    for (int i = 0; i < 16; i++)
        if (((a >> i) % 2) == 1 && ((b >> i) % 2) == 1)
            result ^= 1;
    return result;
}
std::vector<std::vector<int>> GenerateDLCT_5bit(std::vector<unsigned char> input)
{
    std::vector<std::vector<int>> output(input.size(), std::vector<int>(input.size()));
    for (int p1 = 0; p1 < input.size(); p1++)
    {
        for (int p2 = 0; p2 < input.size(); p2++)
        {
            int DLCT_cell_value = 0;
            int DLCT_cell_counter = 0;
            for (int i = 0; i < input.size(); i++)
            {
                unsigned char check1 = LAT_dot_5bit((unsigned char)p2, (unsigned char)input[i]);
                unsigned char check2 = LAT_dot_5bit((unsigned char)p2, (unsigned char)input[i ^ p1]);

                if (check1 == check2)
                {
                    DLCT_cell_counter++;
                }
            }

            DLCT_cell_value = (int)(DLCT_cell_counter - (std::pow(2, std::log2(input.size()) - 1)));
            output[p1][p2] = DLCT_cell_value;
        }
    }

    return output;
}

bool isInvolution(std::vector<unsigned char> perm)
{
    for (int i = 0; i < perm.size(); i++)
    {
        if (perm[perm[i]] != i)
        {
            return false;
        }
    }
    return true;
}

int calculateNLM(std::vector<unsigned char> perm)
{
    int nlm = 0;
    int maxLAT = MaxLAT(perm);
    nlm = std::pow(2, 3) - maxLAT;
    return nlm;
}
int calculateNLM_5bit(std::vector<unsigned char> perm)
{
    int nlm = 0;
    int maxLAT = MaxLAT_5bit(perm);
    nlm = std::pow(2, 4) - maxLAT;
    return nlm;
}
void initialize()
{
    hexCharacterToBinary['0'] = "0000";
    hexCharacterToBinary['1'] = "0001";
    hexCharacterToBinary['2'] = "0010";
    hexCharacterToBinary['3'] = "0011";
    hexCharacterToBinary['4'] = "0100";
    hexCharacterToBinary['5'] = "0101";
    hexCharacterToBinary['6'] = "0110";
    hexCharacterToBinary['7'] = "0111";
    hexCharacterToBinary['8'] = "1000";
    hexCharacterToBinary['9'] = "1001";
    hexCharacterToBinary['A'] = "1010";
    hexCharacterToBinary['B'] = "1011";
    hexCharacterToBinary['C'] = "1100";
    hexCharacterToBinary['D'] = "1101";
    hexCharacterToBinary['E'] = "1110";
    hexCharacterToBinary['F'] = "1111";

    decimalToHexCharacter[0] = '0';
    decimalToHexCharacter[1] = '1';
    decimalToHexCharacter[2] = '2';
    decimalToHexCharacter[3] = '3';
    decimalToHexCharacter[4] = '4';
    decimalToHexCharacter[5] = '5';
    decimalToHexCharacter[6] = '6';
    decimalToHexCharacter[7] = '7';
    decimalToHexCharacter[8] = '8';
    decimalToHexCharacter[9] = '9';
    decimalToHexCharacter[10] = 'A';
    decimalToHexCharacter[11] = 'B';
    decimalToHexCharacter[12] = 'C';
    decimalToHexCharacter[13] = 'D';
    decimalToHexCharacter[14] = 'E';
    decimalToHexCharacter[15] = 'F';

    hexCharacterToDecimal['0'] = 0;
    hexCharacterToDecimal['1'] = 1;
    hexCharacterToDecimal['2'] = 2;
    hexCharacterToDecimal['3'] = 3;
    hexCharacterToDecimal['4'] = 4;
    hexCharacterToDecimal['5'] = 5;
    hexCharacterToDecimal['6'] = 6;
    hexCharacterToDecimal['7'] = 7;
    hexCharacterToDecimal['8'] = 8;
    hexCharacterToDecimal['9'] = 9;
    hexCharacterToDecimal['A'] = 10;
    hexCharacterToDecimal['B'] = 11;
    hexCharacterToDecimal['C'] = 12;
    hexCharacterToDecimal['D'] = 13;
    hexCharacterToDecimal['E'] = 14;
    hexCharacterToDecimal['F'] = 15;

    hexCharacterToAscii['0'] = 48;
    hexCharacterToAscii['1'] = 49;
    hexCharacterToAscii['2'] = 50;
    hexCharacterToAscii['3'] = 51;
    hexCharacterToAscii['4'] = 52;
    hexCharacterToAscii['5'] = 53;
    hexCharacterToAscii['6'] = 54;
    hexCharacterToAscii['7'] = 55;
    hexCharacterToAscii['8'] = 56;
    hexCharacterToAscii['9'] = 57;
    hexCharacterToAscii['A'] = 65;
    hexCharacterToAscii['B'] = 66;
    hexCharacterToAscii['C'] = 67;
    hexCharacterToAscii['D'] = 68;
    hexCharacterToAscii['E'] = 69;
    hexCharacterToAscii['F'] = 70;

    hexCharacterToBinary_5bit[0] = "00000";
    hexCharacterToBinary_5bit[1] = "00001";
    hexCharacterToBinary_5bit[2] = "00010";
    hexCharacterToBinary_5bit[3] = "00011";
    hexCharacterToBinary_5bit[4] = "00100";
    hexCharacterToBinary_5bit[5] = "00101";
    hexCharacterToBinary_5bit[6] = "00110";
    hexCharacterToBinary_5bit[7] = "00111";
    hexCharacterToBinary_5bit[8] = "01000";
    hexCharacterToBinary_5bit[9] = "01001";
    hexCharacterToBinary_5bit[10] = "01010";
    hexCharacterToBinary_5bit[11] = "01011";
    hexCharacterToBinary_5bit[12] = "01100";
    hexCharacterToBinary_5bit[13] = "01101";
    hexCharacterToBinary_5bit[14] = "01110";
    hexCharacterToBinary_5bit[15] = "01111";
    hexCharacterToBinary_5bit[16] = "10000";
    hexCharacterToBinary_5bit[17] = "10001";
    hexCharacterToBinary_5bit[18] = "10010";
    hexCharacterToBinary_5bit[19] = "10011";
    hexCharacterToBinary_5bit[20] = "10100";
    hexCharacterToBinary_5bit[21] = "10101";
    hexCharacterToBinary_5bit[22] = "10110";
    hexCharacterToBinary_5bit[23] = "10111";
    hexCharacterToBinary_5bit[24] = "11000";
    hexCharacterToBinary_5bit[25] = "11001";
    hexCharacterToBinary_5bit[26] = "11010";
    hexCharacterToBinary_5bit[27] = "11011";
    hexCharacterToBinary_5bit[28] = "11100";
    hexCharacterToBinary_5bit[29] = "11101";
    hexCharacterToBinary_5bit[30] = "11110";
    hexCharacterToBinary_5bit[31] = "11111";
}
void run(unsigned char arr[])
{
    std::vector<unsigned char> data2(arr, arr + sizeof(arr) / sizeof(arr[0]));
    std::vector<unsigned char> each_sbox(data2.size());
    for (int j = 0; j < data2.size(); j++)
    {
        each_sbox[j] = data2[j];
    }
    int choosen = 5;
    if (choosen == 4)
    {
        std::vector<unsigned char> input = decimalToAsciiConvert(each_sbox); // decimalToAsciiConvert function should be defined
        std::vector<int> input2;
        for (int i = 0; i < input.size(); i++)
        {
            input2.push_back((int)input[i]);
        }

        int MaxDDTValue = MaxDDT(input);
        std::cout << "MaxDDT: " << MaxDDTValue << std::endl;
        int MaxLATValue = MaxLAT(input);
        std::cout << "MaxLAT: " << MaxLATValue << std::endl;
        int AlgebraicDegree = GenerateAlgebraicDegree(input);
        std::cout << "Algebraic Degree: " << AlgebraicDegree << std::endl;
        int FixedPoints = FindFixedPoint(input);
        cout << "Fixed Point: " << FixedPoints << endl;
        int BIBO_Patern = NumberOfBIBO_PATTERNS(input);
        std::cout << "BIBO_Pattern: " << BIBO_Patern << std::endl;
        auto LinearBranchNumberValue = LinearBranchNumber(input); // LinearBranchNumber_5bit should be defined
        std::cout << "Linear Branch Number: " << LinearBranchNumberValue << std::endl;
        auto DifferentialBranchNumberValue = DifferentialBranchNumber(input); // DifferentialBranchNumber_5bit should be defined
        std::cout << "Differential Branch Number: " << DifferentialBranchNumberValue << std::endl;
        int FrequencyOfDifferentialUnif = FrequencyOfDifferentialUniformity(input, MaxDDTValue);
        std::cout << "Frequency of Differential Uniformity: " << FrequencyOfDifferentialUnif << std::endl;
        int FrequencyOfLinearityValue = FrequencyOfLinearity(input, MaxLATValue);
        std::cout << "Frequency of Linearity: " << FrequencyOfLinearityValue << std::endl;
        auto BCT = GenerateBCT(input2);        // GenerateBCT function should be defined
        auto uniformity = BCT_Uniformity(BCT); // BCT_Uniformity function should be defined
        std::cout << "The BCT Uniformity of S-Box " << uniformity << std::endl;
        int DLCT_Unif = DLCT_Uniformity(GenerateDLCT(input)); // DLCT::DLCT_Uniformity and DLCT::GenerateDLCT should be defined
        std::cout << "Differential Linear Connectivity Table Uniformity: " << DLCT_Unif << std::endl;
        int NLM = calculateNLM(input);
        std::cout << "NLM: " << NLM << std::endl;
        int nlmPercentage = (NLM * 100) / 6;
        std::cout << "NLM Percentage: " << nlmPercentage << std::endl;
    }
    else if (choosen == 5)
    {
        std::vector<int> input2;
        for (int i = 0; i < each_sbox.size(); i++)
        {
            input2.push_back((int)each_sbox[i]);
        }
        // auto BCT = GenerateBCT_5bit(each_sbox); // GenerateBCT_5bit function should be defined
        int MaxDDTValue = MaxDDT_5bit(each_sbox);
        std::cout << "MaxDDT: " << MaxDDTValue << std::endl;
        int MaxLATValue = MaxLAT_5bit(each_sbox);
        std::cout << "MaxLAT: " << MaxLATValue << std::endl;
        int AlgebraicDegree = GenerateAlgebraicDegree_5bit(each_sbox);
        std::cout << "Algebraic Degree: " << AlgebraicDegree << std::endl;
        int FixedPoints = FindFixedPoint_5bit(each_sbox);
        cout << "Fixed Point: " << FixedPoints << endl;
        int BIBO_Patern = NumberOfBIBO_PATTERNS_5bit(each_sbox);
        std::cout << "BIBO_Pattern: " << BIBO_Patern << std::endl;
        auto LinearBranchNumberValue = LinearBranchNumber_5bit(each_sbox); // LinearBranchNumber_5bit should be defined
        std::cout << "Linear Branch Number: " << LinearBranchNumberValue << std::endl;
        auto DifferentialBranchNumberValue = DifferentialBranchNumber_5bit(each_sbox); // DifferentialBranchNumber_5bit should be defined
        std::cout << "Differential Branch Number: " << DifferentialBranchNumberValue << std::endl;
        int FrequencyOfDifferentialUnif = FrequencyOfDifferentialUniformity_5bit(each_sbox, MaxDDTValue);
        std::cout << "Frequency of Differential Uniformity: " << FrequencyOfDifferentialUnif << std::endl;
        int FrequencyOfLinearityValue = FrequencyOfLinearity_5bit(each_sbox, MaxLATValue);
        std::cout << "Frequency of Linearity: " << FrequencyOfLinearityValue << std::endl;
        auto BCT = GenerateBCT_5bit(each_sbox); // GenerateBCT function should be defined
        auto uniformity = BCT_Uniformity(BCT);  // BCT_Uniformity function should be defined
        std::cout << "The BCT Uniformity of S-Box " << uniformity << std::endl;
        int DLCT_Unif = DLCT_Uniformity(GenerateDLCT_5bit(each_sbox)); // DLCT::DLCT_Uniformity and DLCT::GenerateDLCT should be defined
        std::cout << "Differential Linear Connectivity Table Uniformity: " << DLCT_Unif << std::endl;
        int NLM = calculateNLM_5bit(each_sbox);
        std::cout << "NLM: " << NLM << std::endl;
        int nlmPercentage = (NLM * 100) / 12;
        std::cout << "NLM Percentage: " << nlmPercentage << std::endl;
        bool involution = isInvolution(each_sbox);
        std::cout << "Is Involution: " << involution << std::endl;
    }
}

std::string replaceAll(std::string str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return str;
}

int main(int argc, char *argv[])
{

    initialize();

    /*
        1-0-5-17-28-2-29-12-31-22-27-7-20-4-25-19-11-15-24-3-10-6-16-13-18-14-23-9-30-21-8-26-
        1-0-22-7-29-19-13-8-26-2-31-16-14-27-30-20-3-4-5-28-15-24-12-21-25-9-17-10-18-6-11-23-
        2-4-0-10-1-17-29-21-18-22-3-23-27-30-24-26-31-5-8-25-28-7-9-11-14-19-15-12-20-6-13-16-
        2-5-0-10-17-1-29-21-18-22-3-23-27-30-24-26-31-4-8-25-28-7-9-11-14-19-15-12-20-6-13-16-
        2-7-28-25-29-20-11-4-27-13-6-22-17-8-16-19-30-12-26-1-21-31-5-14-10-24-18-3-23-15-0-9-
        2-12-0-22-19-16-30-13-17-10-9-23-1-7-24-18-5-8-15-4-29-26-3-11-14-28-21-31-25-20-6-27-
        2-24-26-7-25-22-12-10-13-3-27-20-15-11-8-30-18-31-16-23-21-6-5-9-28-29-17-14-19-4-0-1-
        3-26-28-0-18-21-13-24-9-8-27-31-16-6-25-23-12-30-4-29-22-5-20-15-7-14-1-10-2-19-17-11-
    */
    // filename is ./new-sbox2.txt
    // read file
    if (argc < 2)
    {
        std::cout << "Please provide a filename" << endl;
        return 1;
    }
    
    std::string filename = argv[1];
    int choosen = argc > 2 ? atoi(argv[2]) : 5;
    
    ifstream file("./" + filename);

    int lineSize = 0;
    string line;
    while (getline(file, line))
    {
        lineSize++;
    }
    file.close();
    std::vector<unsigned char> sbox_vectors[lineSize];
    ifstream file2("./" + filename);
    int i = 0;
    while (getline(file2, line))
    {
        std::vector<unsigned char> sbox_vector;
        std::stringstream ss(line);
        int j;
        while (ss >> j)
        {
            sbox_vector.push_back(j);
            if (ss.peek() == '-')
                ss.ignore();
        }
        sbox_vectors[i] = sbox_vector;
        i++;        
    }
    file2.close();
    // cout << "OKUDUK" << endl;
    // open file for writing
    ofstream file3;
    file3.open("./" + filename.substr(0, filename.size() - 4) + "_results.txt");
    file3 << "Sbox;MaxDDT;MaxLAT;AlgebraicDegree;FixedPoints;BIBO_Pattern;LinearBranchNumber;DifferentialBranchNumber;FrequencyOfDifferentialUnif;FrequencyOfLinearity;BCT_Uniformity;DLCT_Uniformity;NLM;NLM_Percentage;IsInvolution" << endl;
    for (int i = 0; i < lineSize; i++)
    {
        string result = "";
        for (int j = 0; j < sbox_vectors[i].size(); j++)
        {
            // cout << (int)sbox_vectors[i][j] << "-";
            result += to_string((int)sbox_vectors[i][j]) + ",";
        }
        // cout << endl;
        unsigned char arr[sbox_vectors[i].size()];
        for (int j = 0; j < sbox_vectors[i].size(); j++)
        {
            arr[j] = sbox_vectors[i][j];
        }
        std::vector<unsigned char> data2(arr, arr + sizeof(arr) / sizeof(arr[0]));
        std::vector<unsigned char> each_sbox(data2.size());
        for (int j = 0; j < data2.size(); j++)
        {
            each_sbox[j] = data2[j];
        }
        if (choosen == 4)
        {
            std::vector<unsigned char> input = decimalToAsciiConvert(each_sbox); // decimalToAsciiConvert function should be defined
            std::vector<int> input2;
            for (int i = 0; i < input.size(); i++)
            {
                input2.push_back((int)input[i]);
            }

            int MaxDDTValue = MaxDDT(input);
            // std::cout << "MaxDDT: " << MaxDDTValue << std::endl;
            result += to_string(MaxDDTValue) + ";";
            int MaxLATValue = MaxLAT(input);
            // std::cout << "MaxLAT: " << MaxLATValue << std::endl;
            result += to_string(MaxLATValue) + ";";
            int AlgebraicDegree = GenerateAlgebraicDegree(input);
            // std::cout << "Algebraic Degree: " << AlgebraicDegree << std::endl;
            result += to_string(AlgebraicDegree) + ";";
            int FixedPoints = FindFixedPoint(input);
            // std::cout << "Fixed Point: " << FixedPoints << endl;
            result += to_string(FixedPoints) + ";";
            int BIBO_Patern = NumberOfBIBO_PATTERNS(input);
            // std::cout << "BIBO_Pattern: " << BIBO_Patern << std::endl;
            result += to_string(BIBO_Patern) + ";";
            auto LinearBranchNumberValue = LinearBranchNumber(input); // LinearBranchNumber_5bit should be defined
            // std::cout << "Linear Branch Number: " << LinearBranchNumberValue << std::endl;
            result += to_string(LinearBranchNumberValue) + ";";
            auto DifferentialBranchNumberValue = DifferentialBranchNumber(input); // DifferentialBranchNumber_5bit should be defined
            // std::cout << "Differential Branch Number: " << DifferentialBranchNumberValue << std::endl;
            result += to_string(DifferentialBranchNumberValue) + ";";
            int FrequencyOfDifferentialUnif = FrequencyOfDifferentialUniformity(input, MaxDDTValue);
            // std::cout << "Frequency of Differential Uniformity: " << FrequencyOfDifferentialUnif << std::endl;
            result += to_string(FrequencyOfDifferentialUnif) + ";";
            int FrequencyOfLinearityValue = FrequencyOfLinearity(input, MaxLATValue);
            // std::cout << "Frequency of Linearity: " << FrequencyOfLinearityValue << std::endl;
            result += to_string(FrequencyOfLinearityValue) + ";";
            auto BCT = GenerateBCT(input2);        // GenerateBCT function should be defined
            auto uniformity = BCT_Uniformity(BCT); // BCT_Uniformity function should be defined
            // std::cout << "The BCT Uniformity of S-Box " << uniformity << std::endl;
            result += to_string(uniformity) + ";";
            int DLCT_Unif = DLCT_Uniformity(GenerateDLCT(input)); // DLCT::DLCT_Uniformity and DLCT::GenerateDLCT should be defined
            // std::cout << "Differential Linear Connectivity Table Uniformity: " << DLCT_Unif << std::endl;
            result += to_string(DLCT_Unif) + ";";
            int NLM = calculateNLM(input);
            // std::cout << "NLM: " << NLM << std::endl;
            result += to_string(NLM) + ";";
            int nlmPercentage = (NLM * 100) / 6;
            // std::cout << "NLM Percentage: " << nlmPercentage << std::endl;
            result += to_string(nlmPercentage) + ";";
            bool involution = isInvolution(each_sbox);
            // std::cout << "Is Involution: " << involution << std::endl;
            result += to_string(involution) + ";";
            // cout << result << endl;
            // write to file
            // replace ,; with ;
            result = replaceAll(result, ",;", ";");
            file3 << result << endl;
        }
        else if (choosen == 5)
        {
            std::vector<int> input2;
            for (int i = 0; i < each_sbox.size(); i++)
            {
                input2.push_back((int)each_sbox[i]);
            }
            result += ";";
            // auto BCT = GenerateBCT_5bit(each_sbox); // GenerateBCT_5bit function should be defined
            int MaxDDTValue = MaxDDT_5bit(each_sbox);
            // std::cout << "MaxDDT: " << MaxDDTValue << std::endl;
            result += to_string(MaxDDTValue) + ";";
            int MaxLATValue = MaxLAT_5bit(each_sbox);
            // std::cout << "MaxLAT: " << MaxLATValue << std::endl;
            result += to_string(MaxLATValue) + ";";
            int AlgebraicDegree = GenerateAlgebraicDegree_5bit(each_sbox);
            // std::cout << "Algebraic Degree: " << AlgebraicDegree << std::endl;
            result += to_string(AlgebraicDegree) + ";";
            int FixedPoints = FindFixedPoint_5bit(each_sbox);
            // cout << "Fixed Point: " << FixedPoints << endl;
            result += to_string(FixedPoints) + ";";
            int BIBO_Patern = NumberOfBIBO_PATTERNS_5bit(each_sbox);
            // std::cout << "BIBO_Pattern: " << BIBO_Patern << std::endl;
            result += to_string(BIBO_Patern) + ";";
            auto LinearBranchNumberValue = LinearBranchNumber_5bit(each_sbox); // LinearBranchNumber_5bit should be defined
            // std::cout << "Linear Branch Number: " << LinearBranchNumberValue << std::endl;
            result += to_string(LinearBranchNumberValue) + ";";
            auto DifferentialBranchNumberValue = DifferentialBranchNumber_5bit(each_sbox); // DifferentialBranchNumber_5bit should be defined
            // std::cout << "Differential Branch Number: " << DifferentialBranchNumberValue << std::endl;
            result += to_string(DifferentialBranchNumberValue) + ";";
            int FrequencyOfDifferentialUnif = FrequencyOfDifferentialUniformity_5bit(each_sbox, MaxDDTValue);
            // std::cout << "Frequency of Differential Uniformity: " << FrequencyOfDifferentialUnif << std::endl;
            result += to_string(FrequencyOfDifferentialUnif) + ";";
            int FrequencyOfLinearityValue = FrequencyOfLinearity_5bit(each_sbox, MaxLATValue);
            // std::cout << "Frequency of Linearity: " << FrequencyOfLinearityValue << std::endl;
            result += to_string(FrequencyOfLinearityValue) + ";";
            auto BCT = GenerateBCT_5bit(each_sbox); // GenerateBCT function should be defined
            auto uniformity = BCT_Uniformity(BCT);  // BCT_Uniformity function should be defined
            // std::cout << "The BCT Uniformity of S-Box " << uniformity << std::endl;
            result += to_string(uniformity) + ";";
            int DLCT_Unif = DLCT_Uniformity(GenerateDLCT_5bit(each_sbox)); // DLCT::DLCT_Uniformity and DLCT::GenerateDLCT should be defined
            // std::cout << "Differential Linear Connectivity Table Uniformity: " << DLCT_Unif << std::endl;
            result += to_string(DLCT_Unif) + ";";
            int NLM = calculateNLM_5bit(each_sbox);
            // std::cout << "NLM: " << NLM << std::endl;
            result += to_string(NLM) + ";";
            int nlmPercentage = (NLM * 100) / 12;
            // std::cout << "NLM Percentage: " << nlmPercentage << std::endl;
            result += to_string(nlmPercentage) + ";";
            // cout << result << endl;
            bool involution = isInvolution(each_sbox);
            // std::cout << "Is Involution: " << involution << std::endl;
            result += to_string(involution) + ";";
            result = replaceAll(result, ",;", ";");
            // write to file
            file3 << result << endl;
        }
    }
    file3.close();
}
