#include <iostream>
#include <cctype>
#include <stdexcept>
#include <map>
#include <regex>

static const std::map<std::string, char> digits{
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

char get_first_digit(const std::map<std::string, char>& digit_map, const std::regex& regex, const std::string& line){
    auto matched_key = std::sregex_iterator(line.cbegin(), line.cend(), regex)->str();
    return matched_key.size() == 1? (matched_key[0] - '0') : (digit_map.at(matched_key));
}

std::regex digits_to_regex(const std::map<std::string, char>& digit_map){

    std::string regex_str;
    for(const auto& digit : digit_map){
        regex_str += digit.first + "|";
    }
    regex_str += "\\d";

    return std::regex(regex_str, std::regex::icase);
}

int main(int argc, char **argv) {
    int sum = 0;

    std::regex first_regex = digits_to_regex(digits);

    std::map<std::string, char> reverse_digits;
    for(const auto& digit_value : digits){
        std::string digit(digit_value.first);
        std::reverse(digit.begin(), digit.end());
        reverse_digits[digit] = digit_value.second;
    }

    std::regex second_regex = digits_to_regex(reverse_digits);

    for(std::string line; std::getline(std::cin, line);){
        int first_digit = get_first_digit(digits, first_regex, line);

        std::reverse(line.begin(), line.end());
        int second_digit = get_first_digit(reverse_digits, second_regex, line);

        sum += first_digit*10 + second_digit;
    }
    std::cout << sum << std::endl;
    return 0;
}
