#include <iostream>
#include <cctype>
#include <stdexcept>
#include <ranges>

template <std::ranges::input_range Range>
char get_first_digit(const Range& input){
    for(const auto& c : input)
        if(isdigit(c))
            return c - '0';
    throw std::runtime_error("No digit found");
}

int main(int argc, char **argv) {
    int sum = 0;
    for(std::string line; std::getline(std::cin, line);)
        sum += get_first_digit(line)*10 + get_first_digit(std::ranges::views::reverse(line));
    std::cout << sum << std::endl;
    return 0;
}
