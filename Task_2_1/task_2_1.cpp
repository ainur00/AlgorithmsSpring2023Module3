#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

std::string GetString(const std::vector<uint64_t>& pValues) {
    if (pValues.empty())
        return "";
    std::string str = "a";
    for (uint64_t i = 1; i < pValues.size(); ++i) {
        if (pValues[i] == 0) {
            uint64_t pValuesMaxDiff = pValues[i - 1] - pValues[i] + 1;
            // if pValues[i] == 0 and i != 0, then str[i] != 'a'
            for (int8_t symbol = 98; symbol <= 122; ++symbol) {
                bool isFind = true;
                str.push_back(symbol);
                for (uint64_t pValuesDiff = 1; pValuesDiff <= pValuesMaxDiff; ++pValuesDiff)
                    if (str.substr(0, pValuesDiff) == str.substr(str.size() - pValuesDiff, pValuesDiff)) {
                        isFind = false;
                        break;
                    }
                if (isFind)
                    break;
                str.pop_back();
            }
        }
        else
            str += str[pValues[i] - 1];
    }
    return str;
}

int32_t main() {
    std::vector<uint64_t> pValues;
    uint64_t pValue = 0;
    while (std::cin >> pValue)
        pValues.push_back(pValue);
    std::cout << GetString(pValues) << std::endl;
    return 0;
}
