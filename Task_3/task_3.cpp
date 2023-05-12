#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

void IncreasingPalindromeLength(const std::string& str, std::vector<uint64_t>& subPalindromesCounts, const uint64_t& i, const uint8_t& isOddLength) {
    while ((i - subPalindromesCounts[i] - 1 + isOddLength != static_cast<uint64_t>(-1)) && (i + subPalindromesCounts[i] < str.length()) && (str[i - subPalindromesCounts[i] - 1 + isOddLength] == str[i + subPalindromesCounts[i]]))
        ++subPalindromesCounts[i];
}

std::vector<uint64_t> GetSubPalindromeCount(const std::string& str, const uint8_t& isOddLength) {
    std::vector<uint64_t> subPalindromesCounts(str.length(), isOddLength);
    // half-interval [leftLimit, rightLimit)
    uint64_t leftLimit = 0;
    uint64_t rightLimit = 0;
    for (uint64_t i = 0; i < str.length(); ++i) {
        if (i < rightLimit) {
            uint64_t iSymmetricalElement = leftLimit + rightLimit - i - isOddLength;
            subPalindromesCounts[i] = std::min(rightLimit - i, subPalindromesCounts[iSymmetricalElement]);
        }
        IncreasingPalindromeLength(str, subPalindromesCounts, i, isOddLength);
        if (i + subPalindromesCounts[i] > rightLimit) {
            rightLimit = i + subPalindromesCounts[i];
            leftLimit = i + 1 - subPalindromesCounts[i] - 1 + isOddLength;
        }
    }
    return subPalindromesCounts;
}

uint64_t GetSubPalindromeCount(const std::string& str) {
    uint64_t subPalindromesCount = 0;
    std::vector<uint64_t> oddLengthSubPalindromesCounts = GetSubPalindromeCount(str, 1);
    std::vector<uint64_t> evenLengthSubPalindromesCounts = GetSubPalindromeCount(str, 0);     
    for (uint64_t i = 0; i < str.length(); ++i)
        subPalindromesCount += (evenLengthSubPalindromesCounts[i] + oddLengthSubPalindromesCounts[i] - 1);
    return subPalindromesCount;
}

int32_t main() {
    std::string str = "";
    std::cin >> str;
    std::cout << GetSubPalindromeCount(str) << std::endl;
    return 0;
}

