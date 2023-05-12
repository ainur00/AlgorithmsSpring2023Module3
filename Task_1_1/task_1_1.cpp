#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

std::vector<uint16_t> GetPValues(const std::string& s) {
    std::vector<uint16_t> p(s.length(), 0);
    for (uint16_t i = 1; i < s.length(); ++i) {
        p[i] = p[i - 1];
        while ((p[i] > 0) && (s[p[i]] != s[i]))
            p[i] = p[p[i] - 1];
        if (s[i] == s[p[i]])
            ++p[i];
    }
    return p;
}

std::vector<uint32_t> GetOverlaps(const std::string& pattern, const std::string& text) {
    std::vector<uint32_t> overlaps;
    std::vector<uint16_t> pPatternValues = GetPValues(pattern);
    uint16_t prevTextP = 0;
    for (uint32_t i = 0; i < text.length(); ++i) {
        uint16_t thisTextP = prevTextP;
        while ((thisTextP > 0) && (pattern[thisTextP] != text[i]))
            thisTextP = pPatternValues[thisTextP - 1];
        if (pattern[thisTextP] == text[i])
            ++thisTextP;
        if (thisTextP == pattern.length())
            overlaps.push_back(i - pattern.length() + 1);
        prevTextP = thisTextP;
    }
    return overlaps;
}

int32_t main() {
    std::string pattern;
    std::string text;
    std::cin >> pattern >> text;
    std::vector<uint32_t> overlaps = GetOverlaps(pattern, text);
    for (uint32_t overlap : overlaps)
        std::cout << overlap << " ";
    return 0;
}
