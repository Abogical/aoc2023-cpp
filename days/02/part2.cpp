#include <iostream>
#include <stdexcept>
#include <ranges>
#include <cstdint>
#include <regex>

const std::regex game_regex("Game \\d+: (.*)");
const std::regex draw_regex("(\\d+) (red|green|blue)");

int main(int argc, char**argv){
    uint32_t sum = 0;
    std::smatch match;
    for(std::string line; std::getline(std::cin, line);)
        if(std::regex_match(line, match, game_regex)){
            uint32_t min_red = 0, min_green = 0, min_blue = 0;
            for(const auto& draw : match[1].str() | std::views::split(';')){
                for(auto match_ptr = std::sregex_iterator(draw.begin(), draw.end(), draw_regex);
                    match_ptr != std::sregex_iterator();
                    match_ptr++
                ){
                    const auto match = *match_ptr;
                    const uint32_t number = std::stoi(match[1]);
                    const auto color = match[2].str();

                    if(color == "red")
                        min_red = std::max(min_red, number);
                    else if(color == "green")
                        min_green = std::max(min_green, number);
                    else if(color == "blue")
                        min_blue = std::max(min_blue, number);
                }
            }
            sum += min_red*min_green*min_blue;
        }else
            throw std::runtime_error("Incompatible format");

    std::cout << sum << std::endl;
    return 0;
}